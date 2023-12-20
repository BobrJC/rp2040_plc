import csv
import os



def csv_to_header_parse(csv_file_path, header_folder_path, header_file_name):
    
    with open(csv_file_path, 'r') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=';')
        data = list(csv_reader)
    with open("plc.st") as f:
        content = list(filter(None, f.read().split('\n')))
    if not os.path.exists(header_folder_path):
        os.makedirs(header_folder_path)



    header_file_path = os.path.join(header_folder_path, header_file_name)
    with open(header_file_path, 'w') as header_file:

        tasks = []
        w_reqs = []
        r_reqs=[]
        for row_index, column in enumerate(data[1:], start=1): 
            if column[0] not in tasks:
                tasks.append(column[0])
            if column[2] == 'IN':
                r_reqs_n+=1
            elif column[2] == "OUT":
                w_reqs_n+=1
            header_file.write(f'#define {column[2]} {column[0]} {column[1]}\n')

        header_file.write(f'\n#endif ')

    print(f'Header file "{header_file_path}" generated successfully.')

header_folder_path = '.'
header_file_name = 'parsed_data.h'

csv_file_path = 'TESTFOLDER'
csv_file_name = 'board_mapper.csv'
csv_file_path = os.path.join(csv_file_path, csv_file_name)

csv_to_header_parse(csv_file_path, header_folder_path, header_file_name)
