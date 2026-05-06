CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic -O2
LDFLAGS = 

SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/pc_configurator

SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run