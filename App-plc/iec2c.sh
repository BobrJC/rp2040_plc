!/bin/bash
if [ -z "$MATIEC_FLDR" ]; then
    echo "Ошибка: переменная окружения MATIEC_FLDR не установлена."
    exit 1
fi


# Проверяем, переданы ли аргументы
if [ "$#" -eq 0 ]; then
    echo "Ошибка: не переданы файлы для компиляции."
    exit 1
fi

# Итерируемся по всем переданным файлам
for file in "$@"; do
    # Проверяем, существует ли файл
    if [ ! -f "$file" ]; then
        echo "Ошибка: файл '$file' не найден."
        continue
    fi
    $MATIEC_FLDR/iec2c "$file" -I $MATIEC_FLDR/lib 
done

echo "Компиляция завершена."
