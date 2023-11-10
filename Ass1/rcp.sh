#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

file=$1

# 编译
g++ -c "$file.cpp" -o "$file.o"
g++ "$file.o" -o "$file"

# 运行
./"$file"
