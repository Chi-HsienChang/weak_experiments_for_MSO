SRCS = main.cpp eg.cpp chromosome.cpp problem.cpp
OBJS = $(SRCS:.cpp=.o)

main: $(OBJS)
	g++ -std=c++20 $(OBJS) -o main

%.o: %.cpp
	g++ -std=c++20 -c $< -o $@

clean:
	rm -f $(OBJS) main
