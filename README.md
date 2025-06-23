# weak_experiments_for_MSO

## test v1

g++ -std=c++20 main.cpp -o main

valgrind --leak-check=full ./main 3 onemax
./main 3 onemax

## 6/23-1
split to .h .cpp
make
./main 4 ctrap


## 6/23-2
make
./main 3 test_equal_fitness > result.txt (這個測資正確)



