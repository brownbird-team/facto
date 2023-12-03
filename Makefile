# Filename for program executable
TARGET_EXEC := facto
# Build directory name
BUILD_DIR := build
# Directory where .c source files are stored
SRC_DIR := src
# Directory where header .h files are stored
INC_DIRS := include

ifdef OS

# Use this command to delete directories
RM := rmdir /s /q
# Create directory if it doesn't exist
MKDIR = if not exist $1 mkdir $1
# Replace slash with backslash in paths
FixPath = $(subst /,\,$(1))
# Convert backslashes to slashes
ToLinuxSlashes = $(subst \,/,$(1))
# Set shell to CMD
SHELL=C:\Windows\system32\cmd.exe
# Find all files inside SRC_DIR directory
SRCS := $(call ToLinuxSlashes, $(shell for /f %%A in ('forfiles /p $(SRC_DIR) /s /m *.cpp /c "cmd /c echo @relpath"') do echo $(SRC_DIR)\%%~A))

else

ifeq ($(shell uname), Linux)
# Use this command to delete directories
RM := rm -rf
# Create directory if it doesn't exist
MKDIR = mkdir -p $1
# Nothing to do with slashes
FixPath = $(1)
# Find all files inside SRC_DIR directory
SRCS := $(shell find $(SRC_DIR) -name '*.cpp' -or -name '*.c')
endif

endif

# Kreiraj listu objektnih datoteka
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Set flags for include directories
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Set general flags
CFLAGS := $(INC_FLAGS)

# Set linker flags
LDFLAGS := -lm
# Set compiler
CC := gcc

# Link all object files
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile all source files
$(BUILD_DIR)/%.c.o: %.c Makefile
	$(call FixPath, $(call MKDIR, $(dir $@)))
	$(CC) $(CFLAGS) -c $< -o $@

# Remove all compiled stuff
clean:
	$(RM) $(BUILD_DIR)