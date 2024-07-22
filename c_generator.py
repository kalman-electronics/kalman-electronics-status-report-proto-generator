class Construct:
    def __str__(self):
        raise NotImplementedError


class CCodeWriter:
    def __init__(self):
        self.constructs = []

    def add(self, construct: Construct):
        if construct:
            self.constructs.append(construct)

    def write(self, filename):
        with open(filename, 'w') as f:
            for construct in self.constructs:
                f.write(construct + '\n')

    def __str__(self):
        return '\n\n'.join([str(construct) for construct in self.constructs])


class Group(Construct):
    def __init__(self, name):
        self.name = name
        self.constructs = []

    def add(self, construct: Construct):
        self.constructs.append(construct)

    def __str__(self):
        return f'// {self.name}\n' + '\n'.join([str(construct) for construct in self.constructs]) if self.constructs \
            else ''


class Define(Construct):
    def __init__(self, name, value=None):
        self.name = name
        self.value = value

    def __str__(self):
        return f'#define {self.name} {self.value if self.value is not None else ""}'


class Include(Construct):
    def __init__(self, include, brackets=False):
        self.include = include
        self.brackets = brackets

    def __str__(self):
        if self.brackets:
            return f'#include <{self.include}>'
        else:
            return f'#include "{self.include}"'


class Field(Construct):
    def __init__(self, ctype, name):
        self.ctype = ctype
        self.name = name

    def __str__(self):
        return f'{self.ctype} {self.name};'


class Struct(Construct):
    def __init__(self, name, typedef=False, packed=False):
        self.packed = packed
        self.typedef = typedef
        self.name = name
        self.fields = []

    def add_field(self, field: Field):
        self.fields.append(field)

    def __str__(self):
        fields_str = '\n'.join(['\t' + str(field) for field in self.fields])

        if self.typedef:
            if self.packed:
                return f'typedef struct __attribute__((packed)) {{\n{fields_str}\n}} {self.name};'
            else:
                return f'typedef struct {{\n{fields_str}\n}} {self.name};'
        else:
            if self.packed:
                return f'struct {self.name} __attribute__((packed)) {{\n{fields_str}\n}};'
            else:
                return f'struct {self.name} {{\n{fields_str}\n}};'


class Enum(Construct):
    def __init__(self, name, typedef=False):
        self.typedef = typedef
        self.name = name
        self.fields = []

    def add_entry(self, name, uppercased=False, value=None):
        self.fields.append((name.upper() if uppercased else name, value))

    def __str__(self):
        fields_str = ',\n'.join([f'\t{field[0]} = {field[1]}' if field[1] is not None else f'\t{field[0]}'
                                 for field in self.fields])

        if self.typedef:
            return f'typedef enum {{\n{fields_str}\n}} {self.name};'
        else:
            return f'enum {self.name} {{\n{fields_str}\n}};'
