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
      frame_id: <int> | required
      fields: <array> | required
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
    - ...
```
#### Fields
- `subsystem_id` - unique identifier number for subsystem. Must be in range 0-255, otherwise value will be wrapped around uint8_t.
- `subsystem` - unique name of the subsystem, should be in snake_case convention. This name will be used as prefix of generated C code refering this submodule
- `multiple_devices` - boolean field used defining devices that are used with multiple instances at the time (i.e motor and arm controllers). If set to `true` there will be addituonal id field added to frame payload for instances distinction
- `frames` - list of frame objects, defining different kinds of status frames that might be sent from the device. Different frames should be grouping status information within common topic. (i.e Can status frame should gather informations about tcan, last can errors, can bus status, etc.)
  - `frame.name` - name of the frame that is part of status of the subsysystem
  - `frame.frame_id` - id number that must be unique without subsystem the frame refers to
  - `frame.fields` - array of the fields that frame consists of
    - `field.name` - name of the field
    - `field.type` - type of the field inside of structure, one of allowed types (see below)
    - `field.values` - list of possible enum values, you can either use raw list \[A, B, C\] or list of mappings \[A: 1, B: 2, C:3\] to change number represented by enum label
    - `field.default` - default value of the field at the struct init, should be passed at string (for enums you can write one of the enum values)
    - `fields.health_checks` - optional list of value validation, that can describe current condition of the component
      - `health_check.type` - type of the validation, either `exact` where value is matched with equals sign or `range` where value is checked whether it fits in given range
      - `health_check.result` - classification label for the data, one of `OK`, `WARNING`, `CRITICAL`
      - `health_check.value` - comparison value when `health_check.type` is `exact`
      - `health_check.min`, `health_check.max` - range for comparison when `health_check.type` is `range`
      - `health_check.troubleshoot` - optional string with common troubleshoot information
      - `health_check.description` - optional string that can describe what is an issue

#### Allowed field types
---------------------------
|   type     |    size    |
|------------|------------|
|  uint8_t   |      1     |
|  uint16_t  |      2     |
|  uint32_t  |      4     |
|  uint64_t  |      8     | 
|  int8_t    |      1     |
|  int16_t   |      2     |
|  int32_t   |      4     |
|  int64_t   |      8     |
|  float     |      4     |
|  double    |      8     |
|  enum      | 1 (unit8_t)| 
|  bool      | 1 (uint8_t)|
---------------------------  
