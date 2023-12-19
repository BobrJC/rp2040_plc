import re
import os
import copy
import csv
class Task:
    def __init__(self, task_id, addresses, period, period_unit, priority):
        self.task_id = task_id
        self.addresses = addresses
        self.period = period
        self.period_unit = period_unit
        self.priority = priority

    def csv_line(self):
        attrs = list(vars(self).items())
        arr_needed = []
        for (i, attr) in enumerate(attrs):            
            attrs[i] = attr[1]

        for address in attrs[1]:
            item = copy.deepcopy(attrs)
            item[1] = address
            arr_needed.append(item)

        csv_lines = [';'.join("%s" % item for item in line) for line in arr_needed]
        print(csv_lines)




def parse_st_file(file_path, task_id=1):
    tasks = []

    with open(file_path, 'r') as file:
        st_code = file.read()

    period_match = re.search(r'INTERVAL\s*:=\s*T#(\d+)(\w*)', st_code)
    if period_match:
        period = str(period_match.group(1))
        period_unit = period_match.group(2).lower() if period_match.group(2) else 'ms'

    priority_match = re.search(r'PRIORITY\s*:=\s*(\d+)', st_code)
    if priority_match:
        priority = int(priority_match.group(1))

    
    var_matches = re.finditer(r'(\w+)\s+AT\s+%(\S+)', st_code)
    addreses = []
    for var_match in var_matches:
        local_var_name = var_match.group(1) # спарсил на всякий, если пригодится
        original_address = var_match.group(2)
        formatted_address = "__" + original_address.replace('.', '_')
        addreses.append(formatted_address)

    
    task = Task(task_id, addreses, period, period_unit, priority)
    tasks.append(task)

    return tasks

st_files = ["plc.st"]
all_tasks = []

for i, st_file in enumerate(st_files):
    tasks_in_file = parse_st_file(st_file, i)
    all_tasks.extend(tasks_in_file)
        #if not os.path.exists(folder_path):
        #    os.makedirs(folder_path)
#
        #file_path = os.path.join(folder_path, file_name)
        #with open(file_path, 'w', newline='') as csv_file:
        #    csv_writer = csv.writer(csv_file, delimiter=';')
        #    csv_writer.writerow(column_names)
        #    for line in csv_lines:
        #        csv_file.write(line)
#
        #print(f"CSV file '{file_name}' with columns {column_names} created successfully in the folder '{folder_path}'.")
for task in all_tasks:
    task.csv_line()
