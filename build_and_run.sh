#!/bin/bash

mkdir -p build

# just compile for "dolltor" alias
rm -rf ./dolltor
g++ src/main.cpp -o dolltor -lstdc++fs

# (compile and run)
g++ -o build/dolltor src/main.cpp -lstdc++fs

# Verificar se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running dolltor..."
    ./build/dolltor
else
    echo "Compilation failed."
fi

# Apagar todos os arquivos de build, exceto a pasta build, ao encerrar o programa
find build ! -name 'build' -type f -exec rm -f {} +
rm -rf build/dolltor build/dolltor.o
