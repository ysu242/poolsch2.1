#!/bin/bash

# Проверка количества аргументов
if [ $# -ne 1 ]; then
    echo "Usage: $0 <log_file_path>"
    exit 1
fi

LOG_FILE=$1

# Проверка существования файла
if [ ! -f "$LOG_FILE" ]; then
    echo "Error: Log file '$LOG_FILE' not found."
    exit 1
fi

# Общее количество записей
TOTAL_ENTRIES=$(wc -l < "$LOG_FILE" | tr -d ' ')

# Количество уникальных файлов
UNIQUE_FILES=$(awk -F ' — ' '{print $1}' "$LOG_FILE" | sort | uniq | wc -l | tr -d ' ')

# Количество изменений с изменением хэша
PREV_FILE=""
PREV_HASH=""
HASH_CHANGES=0

while IFS=' — ' read -r FILE_PATH FILE_SIZE DATE_TIME SHA_SUM ALGO; do
    if [ "$FILE_PATH" != "$PREV_FILE" ]; then
        PREV_HASH="$SHA_SUM"
    else
        if [ "$SHA_SUM" != "$PREV_HASH" ]; then
            HASH_CHANGES=$((HASH_CHANGES + 1))
        fi
        PREV_HASH="$SHA_SUM"
    fi
    PREV_FILE="$FILE_PATH"
done < "$LOG_FILE"

echo "$TOTAL_ENTRIES $UNIQUE_FILES $HASH_CHANGES"
