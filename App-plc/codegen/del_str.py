import os

def del_inc():
    folderpath = '.'

    save = 1
    for filename in os.listdir(folderpath):
        #print(filename)

        if "resource" in filename:
            if save:
                save = 0
                continue
            with open(os.path.join(folderpath, filename), 'r') as file:
                data = file.readlines()
            
            with open(os.path.join(folderpath, filename), 'w') as file:
                for line in data:
                    if not line.strip().startswith('#include "POUS.c"'):
                        file.write(line)