
# Compiler and Flags
CC := gcc
CFLAGS := -Wall -Wextra -Iinclude -g
ARFLAGS := rcs

# Directories
SRC_DIR := src
BUILD_DIR := build

# Discover source files automatically 
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o , $(SRCS))

TARGET := $(BUILD_DIR)/libds.a

.PHONY: all
all: $(TARGET)

# Builds the static library archive file using all object files.
$(TARGET): $(OBJS)
	ar $(ARFLAGS) $@ $^

# Creates object files
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensuring Build directories exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# clear
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

