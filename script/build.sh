#! /bin/bash


ROOT="$(dirname "$0")"

echo "Relocating script to '$ROOT'..."
cd "$ROOT"

echo "Cleaning..."
./clean.sh

if [[ "$1" == "web_env" ]]
then 
    echo "Generating the compiler for web environments..."
    emcmake cmake -S .. -B ../bin -D WEB_ENV=ON
    cd ../bin
    emmake make
else
    echo "Building the compiler..."
    cmake -S .. -B ../bin
    cd ../bin
    make
fi

echo "All done."
