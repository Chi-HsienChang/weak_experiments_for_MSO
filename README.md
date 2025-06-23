# weak_experiments_for_MSO

## test v1

g++ -std=c++20 main.cpp -o main

valgrind --leak-check=full ./main 3 onemax
./main 3 onemax

## 6/23
make
./main 4 ctrap



