# pull in shared compiler settings
include ../common.mk

# per-example flags
# CXXFLAGS += -pthread

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
