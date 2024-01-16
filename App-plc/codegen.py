import sys

from parse_st import *
from codegen.parse_var_types import parse_var_types
from codegen.parse_csv import parse_csv
from codegen.generate_plc_h import generate_plc_h
from codegen.generate_plc_c import generate_plc_c
from codegen.del_str import del_inc

ST_FILE_PATH = 'example.st'

def main():
    st_file_path = DEFAULT_ST_FILE_PATH
    if len(sys.argv) > 1:
        st_file_path = sys.argv[1]
    
    tasks = parse_st_file(st_file_path)
    vars_types = parse_var_types()
    parse_csv(tasks, "board_mapper.csv")
    generate_plc_h(tasks, vars_types)
    generate_plc_c(tasks)
    del_inc()
    

if __name__ == '__main__':
    main()
