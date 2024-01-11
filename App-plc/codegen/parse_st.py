import re
from task import Task

DEFAULT_ST_FILE_PATH = 'example.st'


def parse_variables(content):
    variables = []  # list of (var, address)

    var_blocks = re.findall(r'VAR(.*?)END_VAR', content, re.DOTALL)
    for var_block in var_blocks:
        variables_in_block = re.finditer(r'(\S+) AT\s+%(\S+)', var_block)
        for var_match in variables_in_block:
            variables.append(
                [var_match.group(1), var_match.group(2).replace('.', '_')])

    return variables


def parse_st_file(file_path):
    with open(file_path, 'r') as file:
        content = file.read()

    task_objects = []
    program_var_dict = {}
    program_matches = re.finditer(
        r'PROGRAM (\w+)(.*?)END_PROGRAM', content, re.DOTALL)

    for program in program_matches:
        program_name = program.group(1)
        program_content = program.group(2)
        program_var_dict[program_name] = parse_variables(program_content)

    resource_matches = re.finditer(
        r'RESOURCE (\w+)(.*?)END_RESOURCE', content, re.DOTALL)

    for resource in resource_matches:
        resource_name = resource.group(1)
        resource_body = resource.group(2)

        task_match = re.search(
            r'TASK (\w+)\(INTERVAL := T#(\d+)(\w+),PRIORITY := (\d+)', resource_body)
        task_name = task_match.group(1) if task_match else None

        interval_value = task_match.group(2) if task_match else None
        interval_unit = task_match.group(3) if task_match else None
        priority_value = task_match.group(4) if task_match else None
        program_name = re.search(
            r'PROGRAM \w+ WITH (\w+) : (\w+)', resource_body).group(2)
        task_obj = Task(''.join(filter(str.isdigit, task_name[::-1]))[
                        ::-1], program_var_dict[program_name], int(interval_value), interval_unit, int(priority_value))
        task_objects.append(task_obj)

    print("ST file parsed successfully.")
    return sorted(task_objects, key=lambda x: x.task_id)


def main():
    print(parse_st_file(DEFAULT_ST_FILE_PATH))


if __name__ == '__main__':
    main()
