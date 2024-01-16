import csv
import sys
from codegen.task import Task
from parse_st import *
from codegen.merge_st import merge_st_files
COLUMN_NAMES = ['TaskId', 
                'Priority',
                'Variable', 
                'Address', 
                'Type', 
                'BoardPins', 
                'Direction']
FILE_NAME = 'board_mapper.csv'
DEFAULT_ST_FILE_PATH = 'plc.st'

def create_csv(tasks: list[Task]):
    csv_lines = []
    for id, task in enumerate(tasks):
        for var in task.vars:
            csv_lines.append(f"{id};{task.priority};{var[0]};{var[1]};;;;\n")

    with open(FILE_NAME, 'w', newline='') as csv_file:
        csv_writer = csv.writer(csv_file, delimiter=';')
        csv_writer.writerow(COLUMN_NAMES)
        for line in csv_lines:
            csv_file.write(line)

    print(
        f"CSV file '{FILE_NAME}' with columns {COLUMN_NAMES} created successfully.")

def main():
    #merge_st_files('plc.st', 'generated_plc.st', 'merged.st')
    st_file_path = DEFAULT_ST_FILE_PATH
    if len(sys.argv) > 1:
        st_file_path = sys.argv[1]
    
    tasks = parse_st_file(st_file_path)
    create_csv(tasks)

if __name__ == "__main__":
    main()