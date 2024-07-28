import os

import yaml
import c_generator as c_gen


class Protocol:
    def __init__(self, name: str):
        self.name = name
        self.yaml_files = []
        self.c_codes = {}

    def load_from_yaml(self, path: str):
        self.yaml_files.append(self.__load_yaml(path))

    def generate_c_code(self):
        for yaml_file in self.yaml_files:
            cw = c_gen.CCodeWriter()
            cw.add(c_gen.Include("stdint.h", brackets=True))
            cw.add(c_gen.Include("kalman-status-report-protocol/common.h"))
            for frame in yaml_file['protocol']['frames']:
                struct = c_gen.Struct(frame['name'], typedef=True, packed=True)
                for field in frame['fields']:
                    type_name = field['type']
                    if type_name == 'enum':
                        type_name = frame['name'] + '_' + self.__to_camel_case(field['name']) + "TypeDef"
                        enum = c_gen.Enum(type_name, typedef=True)
                        for entry in field['values']:
                            enum.add_entry(field['name'] + '_' + entry, uppercased=True)
                        cw.add(enum)

                    struct.add_field(c_gen.Field(type_name, field['name']))

                    if 'health_checks' in field:
                        group = c_gen.Group("Health check values for " + field['name'])
                        for entry in field['health_checks']:
                            if entry['type'] == 'exact':
                                group.add(c_gen.Define(field['name'] + '_HEALTH_CHECK_' + entry['result'], entry['value']))
                            elif entry['type'] == 'range':
                                group.add(c_gen.Define(field['name'] + '_HEALTH_CHECK_' + entry['result'] + '_MIN', entry['min']))
                                group.add(c_gen.Define(field['name'] + '_HEALTH_CHECK_' + entry['result'] + '_MAX', entry['max']))
                        cw.add(group)

                        # TODO add health check function getters

                cw.add(struct)

            self.c_codes[yaml_file['protocol']['subsystem'] + "protocol"] = cw

    # def save_to_file(self, path: str):
    #     dump_yaml(self.yaml_description, path)

    def save_c_code(self, path: str):
        os.mkdir(path)
        for name, c_code in self.c_codes.items():
            with open(path + "/" + name + ".h", 'w') as f:
                f.write(str(c_code))

    def __str__(self):
        return f"Protocol({self.name})"

    @staticmethod
    def __load_yaml(path: str):
        with open(path, 'r') as file:
            return yaml.safe_load(file)

    @staticmethod
    def __dump_yaml(self, data, path: str):
        with open(path, 'w') as file:
            yaml.dump(data, file)

    @staticmethod
    def __to_camel_case(snake_str):
        return "".join(x.capitalize() for x in snake_str.lower().split("_"))


# a = load_yaml('protocol_description.yaml')
#

