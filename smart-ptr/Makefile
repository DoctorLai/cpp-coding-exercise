CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -g -I.

TARGET = main
SRCS = main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
