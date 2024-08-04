import os
import argparse

from pathlib import Path
from jinja2 import Environment, FileSystemLoader
from yaml_parser import Parser, ALLOWED_TYPES
from distutils.dir_util import copy_tree


def generate_devices_protocols(protocols):
    devices_protocols_c_codes = {}
    jinja_env = Environment(loader=FileSystemLoader(args.templates))

    for protocol_name, protocol in protocols.items():

        template = jinja_env.get_template('protocol_file_template.h.jinja2')
        c_code = template.render(protocol=protocol,
                                 clibraries=["stdint.h", "stdbool.h"],
                                 libraries=["kalman-status-report-protocol/frames.h",
                                            "kalman-status-report-protocol/common.h",
                                            "kalman-status-report-protocol/protocols/protocol_common.h"],
                                 allowed_types=ALLOWED_TYPES)
        devices_protocols_c_codes[f"protocols/subsystems/{protocol_name}_protocol.h"] = c_code

    return devices_protocols_c_codes


def generate_common_protocol(protocols):
    jinja_env = Environment(loader=FileSystemLoader(args.templates))
    template = jinja_env.get_template('common_protocol_file_template.h.jinja2')
    c_code = template.render(protocols=protocols,
                             clibraries=["stdint.h", "stdbool.h"],
                             libraries=["kalman-status-report-protocol/frames.h"])
    return {Path("protocols/protocol_common.h"): c_code}


def generate_util_protocol(paths, protocols):
    jinja_env = Environment(loader=FileSystemLoader(args.templates))
    template = jinja_env.get_template('util_protocol_file_template.h.jinja2')
    c_code = template.render(clibraries=["stdint.h", "stdbool.h"],
                             libraries=["kalman-status-report-protocol/" + path for path in paths],
                             protocols=protocols.values())
    return {Path("protocols/protocol_utils.h"): c_code}


def generate_instances(protocols):
    devices_instances_c_codes = {}
    jinja_env = Environment(loader=FileSystemLoader(args.templates))
    template = jinja_env.get_template('instance_file_template.h.jinja2')
    for protocol_name, protocol in protocols.items():
        c_code = template.render(protocol=protocol,
                                clibraries=["stdint.h", "stdbool.h"],
                                 libraries=["kalman-status-report-protocol/frames.h",
                                            "kalman-status-report-protocol/common.h",
                                            "kalman-status-report-protocol/protocols/subsystems/{protocol_name}_protocol.h"])
        devices_instances_c_codes[f"instances/{protocol_name}_instance.h"] = c_code

    return devices_instances_c_codes


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
    devices_protocols_c_codes = generate_devices_protocols(protocols)

    copy_tree('library_source', args.output)

    output_path = os.path.join(args.output, 'kalman-status-report-protocol')
    save_c_codes(devices_protocols_c_codes, output_path)
    save_c_codes(generate_common_protocol(protocols.values()), output_path)
    save_c_codes(generate_util_protocol(devices_protocols_c_codes.keys(), protocols), output_path)
    save_c_codes(generate_instances(protocols), output_path)
