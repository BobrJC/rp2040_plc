import re
import os

VARIABLES_PATH = 'LOCATED_VARIABLES.h'


def parse_var_types():
    assert os.path.exists(
        VARIABLES_PATH), f"there is no {VARIABLES_PATH} file, check the directory"

    result = {}
    with open(VARIABLES_PATH, "r") as file:
        data = file.read()

    pattern = r"__LOCATED_VAR\((\w+),__(\w+).*\)"
    matches = re.findall(pattern, data)

    for match in matches:
        type = match[0]
        var = match[1]
        result[var] = type
    print("LOCATED_VARIABLES parsed successfully.")
    return result
