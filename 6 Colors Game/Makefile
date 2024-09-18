# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -O3 -std=c++17
CXXFLAGS += -DMAKELINUX

# SFML include and library paths (install: apt-get install libsfml-dev)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE = /usr/include
SFML_LIB_PATH = /usr/lib

# GTK include and library paths (install: apt-get install libgtk-3-dev)
GTK_CFLAGS := $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS := $(shell pkg-config --libs gtk+-3.0)


# Directories
SRC_DIR = 6_colors
BUILD_DIR = build

# Source files
SRCS = $(SRC_DIR)/main.cpp \
	$(SRC_DIR)/Board.cpp \
	$(SRC_DIR)/Controller.cpp \
	$(SRC_DIR)/Person.cpp \
	$(SRC_DIR)/ShapeCell.cpp \
	$(SRC_DIR)/CPU.cpp \
	$(SRC_DIR)/ImageLoader.cpp \
	$(SRC_DIR)/Player.cpp \
	$(SRC_DIR)/ToolBar.cpp \


# Object files for Release build
OBJS_RELEASE = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executable name for Release
TARGET_RELEASE = $(BUILD_DIR)/project_release

# Default target (Release build)
all: $(TARGET_RELEASE)

# Rule for building the Release target
$(TARGET_RELEASE): $(OBJS_RELEASE)
	$(CXX) $(CXXFLAGS) -o $@ $^ -I$(SFML_INCLUDE) -L$(SFML_LIB_PATH) $(SFML_LIBS) $(GTK_LIBS)

# Rule for compiling object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(GTK_CFLAGS) -c $< -o $@ -I$(SFML_INCLUDE)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

