import os
import argparse
from yaml_parser import Parser

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

    parser.generate_c_code(args.templates)
    parser.save_c_code(args.output)

