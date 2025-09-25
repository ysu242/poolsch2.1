#!/bin/bash

# Проверка количества аргументов
if [ $# -ne 3 ]; then
    echo "Usage: $0 <file_path> <search_string> <replacement_string>"
    exit 1
fi

FILE_PATH=$1
SEARCH_STRING=$2
REPLACEMENT_STRING=$3

# Проверка существования файла
if [ ! -f "$FILE_PATH" ]; then
    echo "Error: File '$FILE_PATH' not found."
    exit 1
fi

# Замена строки
sed -i '' "s/${SEARCH_STRING}/${REPLACEMENT_STRING}/g" "$FILE_PATH"

# Получение размера файла
FILE_SIZE=$(stat -f%z "$FILE_PATH")

# Получение даты и времени
DATE_TIME=$(date '+%Y-%m-%d %H:%M:%S')

# Вычисление SHA256-хэша
SHA_SUM=$(shasum -a 256 "$FILE_PATH" | awk '{print $1}')

# Запись в журнал
echo "$FILE_PATH — $FILE_SIZE — $DATE_TIME — $SHA_SUM — sha256" >> src/files.log
