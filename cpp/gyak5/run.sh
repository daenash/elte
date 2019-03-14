# For compiling and running the main.cpp

clang++ -std=c++17 -o main.out main.cpp
if [ -f ./main.out ]; then
    ./main.out
    rm main.out
fi