import sys

from parse_st import *
from parse_var_types import parse_var_types
from parse_csv import parse_csv
from generate_plc_h import generate_plc_h
from generate_plc_c import generate_plc_c

ST_FILE_PATH = 'example.st'

def main():
    st_file_path = DEFAULT_ST_FILE_PATH
    if len(sys.argv) > 1:
        st_file_path = sys.argv[1]
    
    tasks = parse_st_file(st_file_path)
    vars_types = parse_var_types()
    parse_csv(tasks, "board_mapper.csv")
    print(tasks)
    generate_plc_h(tasks, vars_types)
    generate_plc_c(tasks)

if __name__ == '__main__':
    main()
