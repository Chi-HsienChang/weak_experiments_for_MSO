# 編譯器與選項變數
CXX := g++
CXXFLAGS := -std=c++20 -Wall -O2

# 目標與來源檔
TARGET := main
SRC := main.cpp

# 編譯目標
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# 清除目標
clean:
	rm -f $(TARGET)
