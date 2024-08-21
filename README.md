# Kalman Status Report Protocol Generator

## Description

## Requirements
- PyYAML (`pip install pyyaml`)
- Jinja2 (`pip install jinja2`)
- Unidecode (`pip install unidecode`)
- 

## Usage

### Run compiler
```bash
python proto_compiler.py [-h] [-s SOURCE] [-o OUTPUT] [-t TEMPLATES]
```

### Create release 
```bash
git tag v1.x.x
git push origin v1.x.x
```

## Creating protocol definition
To define status report protocol for new submodule you have to create new yaml file in `protocol_source` directory. 

### Yaml schema:
```yaml
protocol:
  subsystem_id: <int> | required
  subsystem: <string> | required
  multiple_devices: <bool> | optional(default: false)

  frames: <array> | required
    - name: <str> | required
      type: <type> | required
      default: <str> | optional
      values: [<str>, ..., <str> : <int>] <array> | required if type = enum
      health_checks: <array> | optional
        - type: {range | exact} | required
          min: <int | float> | required if type = range
          max: <int | float> | required if type = range
          value: <int | float> | required if type = exact
          result: {OK | WARNING | CRITICAL} | required
          description: <str> | optional
          troubleshoot: <str> | optional
        - ...
    - ...
```
#### Fields
- `subsystem_id` - unique identifier number for subsystem. Must be in range 0-255, otherwise value will be wrapped around uint8_t.
- `subsystem` - unique name of the subsystem, should be in snake_case convention. This name will be used as prefix of generated C code refering this submodule
- `multiple_devices` - boolean field used defining devices that are used with multiple instances at the time (i.e motor and arm controllers). If set to `true` there will be addituonal id field added to frame payload for instances distinction
- `frames` - list of frame objects, defining different kinds of status frames that might be sent from the device. Different frames should be grouping status information within common topic. (i.e Can status frame should gather informations about tcan, last can errors, can bus status, etc.)
- `frame.name`
