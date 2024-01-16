def merge_st_files(file1_path, file2_path, output_path):
    try:

        with open(file1_path, 'r') as file1:
            content1 = file1.read()
        with open(file2_path, 'r') as file2:
            content2 = file2.read()

        merged_content = content1 + '\n' + content2

        with open(output_path, 'w') as output_file:
            output_file.write(merged_content)
        print(f'Файлы успешно объединены в {output_path}')
    except Exception as e:
        print(f'Произошла ошибка: {e}')
