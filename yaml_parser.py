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
    'enum': 4,
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

        self.values = []
        self.health_checks = []

        self.is_enum = False
        self.is_health_check = False


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
        self.protocols = {}
        self.c_codes = {}

    def load_from_yaml(self, path: str):
        yaml_file = self.__load_yaml(path)
        protocol = Protocol()
        protocol.subsystem = yaml_file['protocol']['subsystem']
        protocol.subsystem_id = yaml_file['protocol']['subsystem_id']

        for frame in yaml_file['protocol']['frames']:
            frame_obj = Frame()
            frame_obj.name = frame['name']
            frame_obj.id = frame['frame_id']
            for field in frame['fields']:
                field_obj = Field()
                field_obj.name = field['name']
                field_obj.type = field['type']
                if field_obj.type == 'enum':
                    field_obj.type = self.__to_camel_case(field_obj.name) + '_TypeDef'
                    field_obj.values = field['values']
                    field_obj.is_enum = True

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

        self.protocols[protocol.subsystem + "_protocol"] = protocol

    def generate_c_code(self, path: str):
        for protocol_name, protocol in self.protocols.items():
            jinja_env = Environment(loader=FileSystemLoader(path))
            template = jinja_env.get_template('protocol_file_template.h.jinja2')
            c_code = template.render(protocol=protocol,
                                     clibraries=["stdint.h", "stdbool.h"],
                                     libraries=["kalman-status-report-protocol/frames.h",
                                                "kalman-status-report-protocol/common.h"])
            self.c_codes[protocol_name] = c_code

    # def save_to_file(self, path: str):
    #     dump_yaml(self.yaml_description, path)

    def save_c_code(self, path: str):
        if not os.path.exists(path):
            os.mkdir(path)

        for name, c_code in self.c_codes.items():
            with open(path + "/" + name + ".h", 'w') as f:
                f.write(str(c_code))

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
