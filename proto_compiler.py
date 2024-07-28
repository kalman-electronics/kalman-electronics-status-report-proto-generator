import os
import argparse
from yaml_parser import Protocol

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate C code from protocol description')
    parser.add_help = True
    parser.add_argument('source', type=str, help='Path to the directory containing the protocol description files ('
                                                 'yaml)')
    parser.add_argument('output', type=str, help='Path to the output directory')
    args = parser.parse_args()

    proto = Protocol('Kalman Status Report')

    for file in os.listdir(args.source):
        proto.load_from_yaml(args.source + "/" + file)

    proto.generate_c_code()

    proto.save_c_code(args.output)

