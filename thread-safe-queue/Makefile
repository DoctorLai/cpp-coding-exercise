# pull in shared compiler settings
include ../common.mk

# per-example flags
CXXFLAGS += -pthread

TARGET := thread_safe_queue
SRCS   := main.cpp
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

.PHONY: all clean run
