# weak_experiments_for_MSO

## test v1

g++ -std=c++20 main.cpp -o main

g++ -std=c++20 -fsanitize=address -g main.cpp -o main
./main 3 onemax