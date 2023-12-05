import csv
import os 

def create_csv(folder_path, file_name, column_names):

    if not os.path.exists(folder_path):
        os.makedirs(folder_path)

    file_path = os.path.join(folder_path, file_name)
    with open(file_path, 'w', newline='') as csv_file:
        csv_writer = csv.writer(csv_file, delimiter=';')
        csv_writer.writerow(column_names)

    print(f"CSV file '{file_name}' with columns {column_names} created successfully in the folder '{folder_path}'.")

folder_path = 'TESTFOLDER' 
file_name = 'board_mapper.csv'
column_names = ['Task', 'BoardPins', 'Type', 'Adress']

create_csv(folder_path, file_name, column_names)
