CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I./include
LDFLAGS = -lpthread
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Find all .cpp files in src and its subdirectories
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Main target
TARGET = $(BIN_DIR)/netsim

# Phony targets
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Include dependencies
-include $(OBJS:.o=.d)

# Generate dependency files
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -MM -MT '$(@:.d=.o)' $< > $@
