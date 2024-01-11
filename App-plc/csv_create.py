import csv
import os 

def find_locals(content: list[str]) -> list[str]:
    result = []
    curr_prog = ''
    for line in content:
        line_splitted = line.split()
        if "AT" in line_splitted:
            result.append(line_splitted[2].replace(".", "_").replace("%", "__"))
    return result

def create_csv(folder_path, file_name, column_names, st_files: list[str]):
    task_plus_local = []
    for (i, file) in enumerate(st_files):
        with open(file) as f:
            content = list(filter(None, f.read().split('\n')))
        for local in find_locals(content):
            task_plus_local.append([i, local]) 

    csv_lines = [f"{task};;;;{local}" for [task, local] in task_plus_local]

    if not os.path.exists(folder_path):
        os.makedirs(folder_path)

    file_path = os.path.join(folder_path, file_name)
    with open(file_path, 'w', newline='') as csv_file:
        csv_writer = csv.writer(csv_file, delimiter=';')
        csv_writer.writerow(column_names)
        for line in csv_lines:
            csv_file.write(line)

    print(f"CSV file '{file_name}' with columns {column_names} created successfully in the folder '{folder_path}'.")
st_files: list[str] = ["all_together.st"]
folder_path = 'TESTFOLDER' 
file_name = 'board_mapper.csv'
column_names = ['Task', 'BoardPins', "Direction",'Type', 'Adress']

create_csv(folder_path, file_name, column_names, st_files)
