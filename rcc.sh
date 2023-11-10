#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file=$1

# 编译
gcc -c "$file.c" -lm -o "$file.o"
gcc "$file.o" -lm -o "$file"

# 运行
./"$file"
