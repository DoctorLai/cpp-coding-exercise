CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -g -I.

TARGET := $(notdir $(CURDIR))
SRCS = main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
