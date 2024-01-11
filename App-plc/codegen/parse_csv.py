import csv
from task import Task 

def parse_csv(tasks: list[Task], csv_file_path : str):
    with open(csv_file_path, 'r') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=';')
        data = list(csv_reader)    
    task_i = 0
    var_i = -1
    for i in range(1, len(data)):
        task_index = int(data[i][0])
        if (task_index == task_i):
            var_i += 1
        else:
            task_i += 1
            var_i = 0
        var_type = data[i][4].lower() if data[i][4] != "" else "DEFAULT"
        tasks[task_index].vars[var_i].append(var_type)
        if var_type == 'gpio':
            tasks[task_index].vars[var_i].append(data[i][5].lower())
            tasks[task_index].vars[var_i].append(data[i][6].lower())
