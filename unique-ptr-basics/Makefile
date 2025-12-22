# shared compiler configuration
include ../common.mk

# per-example flags
# CXXFLAGS += -pthread

TARGET := $(notdir $(CURDIR))
SRCS   := $(wildcard *.cpp)
OBJS   := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(OBJS) $(TARGET)

# Delegates to top-level Makefile
check-format:
	$(MAKE) -f ../Makefile check-format DIR=$(CURDIR)

.PHONY: all clean run check-format
