import os

import yaml
from jinja2 import Environment, FileSystemLoader


ALLOWED_TYPES = {
    'uint8_t': 1,
    'uint16_t': 2,
    'uint32_t': 4,
    'uint64_t': 8,
    'int8_t': 1,
    'int16_t': 2,
    'int32_t': 4,
    'int64_t': 8,
    'float': 4,
    'double': 8,
    'enum': 1,  # TODO: Decide if we want 1 byte enums encoding
    'bool': 1,
}


class Protocol:
    def __init__(self):
        self.subsystem = None
        self.subsystem_id = None
        self.frames = []


class Frame:
    def __init__(self):
        self.name = None
        self.id = None
        self.fields = []


class Field:
    def __init__(self):
        self.name = None
        self.type = None
        self.cast_type = None

        self.values = []
        self.health_checks = []

        self.is_enum = False
        self.is_health_check = False
        self.is_type_cast = False

        self.offset = 0
        self.actual_size = None


class HealthCheck:
    def __init__(self):
        self.type = None
        self.value = None
        self.min = None
        self.max = None
        self.result = None
        self.troubleshoot = None
        self.description = None


class Parser:
    def __init__(self):
        self.__protocols = {}

    def load_from_yaml(self, path: str):
        yaml_file = self.__load_yaml(path)
        protocol = Protocol()
        protocol.subsystem = yaml_file['protocol']['subsystem']
        protocol.subsystem_id = yaml_file['protocol']['subsystem_id']

        for frame in yaml_file['protocol']['frames']:
            frame_obj = Frame()
            frame_obj.name = frame['name']
            frame_obj.id = frame['frame_id']

            current_offset = 0

            for field in frame['fields']:
                field_obj = Field()
                field_obj.name = field['name']
                field_obj.type = field['type']
                field_obj.offset = current_offset
                if field_obj.type not in ALLOWED_TYPES:
                    raise ValueError(f"Invalid type {field_obj.type} for field {field}")

                if field_obj.type == 'bool':
                    field_obj.cast_type = 'uint8_t'
                    field_obj.is_type_cast = True

                if field_obj.type == 'enum':
                    field_obj.type = (f'KSRP_{self.__to_camel_case(protocol.subsystem)}_'
                                      f'{self.__to_camel_case(frame_obj.name)}_'
                                      f'{self.__to_camel_case(field_obj.name)}')
                    field_obj.values = field['values']
                    field_obj.cast_type = 'uint8_t'
                    field_obj.is_enum = True
                    field_obj.is_type_cast = True

                if field_obj.is_type_cast:
                    current_offset += ALLOWED_TYPES[field_obj.cast_type]
                    field_obj.actual_size = ALLOWED_TYPES[field_obj.cast_type]
                else:
                    current_offset += ALLOWED_TYPES[field_obj.type]
                    field_obj.actual_size = ALLOWED_TYPES[field_obj.type]

                if 'health_checks' in field:
                    field_obj.is_health_check = True
                    for health_check in field['health_checks']:
                        health_check_obj = HealthCheck()
                        health_check_obj.type = health_check['type']

                        if health_check_obj.type == 'exact':
                            health_check_obj.value = health_check['value']
                        elif health_check_obj.type == 'range':
                            health_check_obj.min = health_check['min']
                            health_check_obj.max = health_check['max']

                        if 'result' in health_check:
                            health_check_obj.result = health_check['result']
                        if 'troubleshoot' in health_check:
                            health_check_obj.troubleshoot = health_check['troubleshoot']
                        if 'description' in health_check:
                            health_check_obj.description = health_check['description']

                        field_obj.health_checks.append(health_check_obj)

                frame_obj.fields.append(field_obj)

            protocol.frames.append(frame_obj)

        self.__protocols[protocol.subsystem] = protocol

    def get_protocols(self):
        return self.__protocols

    # def save_to_file(self, path: str):
    #     dump_yaml(self.yaml_description, path)

    @staticmethod
    def __load_yaml(path: str):
        with open(path, 'r') as file:
            return yaml.safe_load(file)

    @staticmethod
    def __dump_yaml(data, path: str):
        with open(path, 'w') as file:
            yaml.dump(data, file)

    @staticmethod
    def __to_camel_case(snake_str):
        return "".join(x.capitalize() for x in snake_str.lower().split("_"))
