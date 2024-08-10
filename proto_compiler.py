import os
import argparse

from pathlib import Path
from jinja2 import Environment, FileSystemLoader
from yaml_parser import Parser, ALLOWED_TYPES
from distutils.dir_util import copy_tree


def generate_specific_files(protocols):
    SPECIFIC_FILES = [
        ('protocol_file_template.h.jinja2', 'include/ksrp/protocols/subsystems/{protocol_name}_protocol.h', {
            'clibraries': ["stdint.h", "stdbool.h"],
            'libraries': ["ksrp/frames.h", "ksrp/common.h"],
            'protocols': protocols.values()}),
        ('protocol_file_template.c.jinja2', 'src/ksrp/protocols/subsystems/{protocol_name}_protocol.c', {
            'libraries': ["ksrp/protocols/subsystems/{protocol_name}_protocol.h"],
            'protocols': protocols.values()}),
        ('instance_file_template.h.jinja2', 'include/ksrp/instances/{protocol_name}_instance.h', {
            'clibraries': ["stdint.h", "stdbool.h"],
            'libraries': ["ksrp/frames.h", "ksrp/common.h",
                          "ksrp/protocols/subsystems/{protocol_name}_protocol.h"],
            'protocols': protocols.values()}),
        ('instance_file_template.c.jinja2', 'src/ksrp/instances/{protocol_name}_instance.c', {
            'libraries': ["ksrp/instances/{protocol_name}_instance.h"],
            'protocols': protocols.values()})
    ]

    devices_protocols_c_codes = {}
    jinja_env = Environment(loader=FileSystemLoader(args.templates))

    for template_file, output_file, context in SPECIFIC_FILES:
        template = jinja_env.get_template(template_file)
        for protocol_name, protocol in protocols.items():
            context['libraries'] = [lib.format(protocol_name=protocol_name) for lib in context['libraries']]

            c_code = template.render(protocol=protocol, protocol_name=protocol_name, **context)
            devices_protocols_c_codes[output_file.format(protocol_name=protocol_name)] = c_code

    return devices_protocols_c_codes


def generate_common_files(protocols):
    COMMON_FILES = [
        ('common_protocol_file_template.h.jinja2', 'include/ksrp/protocols/protocol_common.h', {
            'clibraries': ["stdint.h", "stdbool.h"],
            'libraries': ["ksrp/frames.h", "ksrp/common.h"],
            'protocols': protocols.values()}),
        ('util_protocol_file_template.h.jinja2', 'include/ksrp/protocols/protocol_utils.h', {
            'clibraries': ["stdint.h", "stdbool.h"],
            'libraries': ["ksrp/frames.h", "ksrp/common.h"] + [f"ksrp/protocols/subsystems/{protocol_name}_protocol.h" for protocol_name in protocols.keys()],
            'protocols': protocols.values()}),
        ('util_protocol_file_template.c.jinja2', 'src/ksrp/protocols/protocol_utils.c', {
            'libraries': ["ksrp/protocols/protocol_utils.h"],
            'protocols': protocols.values()})
    ]

    devices_protocols_c_codes = {}
    jinja_env = Environment(loader=FileSystemLoader(args.templates))

    for template_file, output_file, context in COMMON_FILES:
        template = jinja_env.get_template(template_file)
        c_code = template.render(**context)
        devices_protocols_c_codes[output_file] = c_code

    return devices_protocols_c_codes


def save_c_codes(c_codes, path):
    for file_path, code in c_codes.items():
        final_path = Path(str(os.path.join(path, file_path)))
        final_path.parent.mkdir(parents=True, exist_ok=True)

        with open(final_path, 'w') as f:
            f.write(str(code))


if __name__ == '__main__':
    argument_parser = argparse.ArgumentParser(description='Generate C code from protocol description')
    argument_parser.add_help = True

    argument_parser.add_argument('-s', '--source', type=str,
                                 help='Path to the directory containing the protocol description files (yaml)')
    argument_parser.add_argument('-o', '--output', type=str, help='Path to the output directory')
    argument_parser.add_argument('-t', '--templates', type=str, help='Path to the templates directory', default='templates',
                                 required=False)

    args = argument_parser.parse_args()

    parser = Parser()

    for file in os.listdir(args.source):
        parser.load_from_yaml(os.path.join(args.source, file))

    protocols = parser.get_protocols()

    copy_tree('library_source', args.output)

    save_c_codes(generate_specific_files(protocols), args.output)
    save_c_codes(generate_common_files(protocols), args.output)
