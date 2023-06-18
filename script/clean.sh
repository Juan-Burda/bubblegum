#! /bin/bash

ROOT="$(dirname "$0")"

cd "$ROOT"

rm -rf ../bin 
rm ../src/frontend/lexical-analysis/flex-scanner.c
rm ../src/frontend/syntactic-analysis/bison-parser.c
rm ../src/frontend/syntactic-analysis/bison-parser.h

echo "All clean."