import yaml
import c_generator as c_gen


def load_yaml(path: str):
    with open(path, 'r') as file:
        return yaml.safe_load(file)


def dump_yaml(data, path: str):
    with open(path, 'w') as file:
        yaml.dump(data, file)


def to_camel_case(snake_str):
    return "".join(x.capitalize() for x in snake_str.lower().split("_"))


a = load_yaml('protocol_description.yaml')

cw = c_gen.CCodeWriter()
cw.add(c_gen.Include("stdint.h", brackets=True))

for frame in a['protocol']:
    print(frame)
    struct = c_gen.Struct(frame['name'], typedef=True, packed=True)
    for field in frame['fields']:
        type_name = field['type']
        if type_name == 'enum':
            type_name = frame['name'] + '_' + to_camel_case(field['name']) + "TypeDef"
            enum = c_gen.Enum(type_name, typedef=True)
            for entry in field['values']:
                enum.add_entry(field['name'] + '_' + entry, uppercased=True)
            cw.add(enum)

        struct.add_field(c_gen.Field(type_name, field['name']))

        if 'health_checks' in field:
            enum = c_gen.Enum(frame['name'] + '_' + to_camel_case(field['name']) + '_HealthCheckTypeDef', typedef=True)
            group = c_gen.Group("Health check values for " + field['name'])
            for entry in field['health_checks']:
                if entry['type'] == 'exact':
                    enum.add_entry(field['name'] + '_HEALTH_CHECK_' + entry['result'],
                                   uppercased=True,
                                   value=entry['value'])
                elif entry['type'] == 'range':
                    group.add(c_gen.Define(field['name'] + '_HEALTH_CHECK_' + entry['result'] + '_MIN', entry['min']))
                    group.add(c_gen.Define(field['name'] + '_HEALTH_CHECK_' + entry['result'] + '_MAX', entry['max']))
                    enum.add_entry(field['name'] + '_HEALTH_CHECK_' + entry['result'], uppercased=True)
            cw.add(group)
            cw.add(enum)

            # TODO add health check function getters

    cw.add(struct)

with open('generated.c', 'w') as f:
    f.write(str(cw))