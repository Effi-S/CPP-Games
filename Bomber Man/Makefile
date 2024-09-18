# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -O3 -std=c++17
CXXFLAGS += -DMAKELINUX

# SFML include and library paths (install: apt-get install libsfml-dev)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE = /usr/include
SFML_LIB_PATH = /usr/lib

# Directories
SRC_DIR = bomberman
BUILD_DIR = build

# Source files
SRCS = \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/Bomb.cpp \
	$(SRC_DIR)/Edge.cpp \
	$(SRC_DIR)/Map.cpp \
	$(SRC_DIR)/Stone.cpp \
	$(SRC_DIR)/smartGuard.cpp \
	$(SRC_DIR)/Character.cpp \
	$(SRC_DIR)/EmptyCell.cpp \
	$(SRC_DIR)/Placeable.cpp \
	$(SRC_DIR)/UserInterface.cpp \
	$(SRC_DIR)/Controller.cpp \
	$(SRC_DIR)/Guard.cpp \
	$(SRC_DIR)/Present.cpp \
	$(SRC_DIR)/dumbGuard.cpp \
	$(SRC_DIR)/Door.cpp \
	$(SRC_DIR)/LevelLoader.cpp \
	$(SRC_DIR)/Robot.cpp \
# Object files for Release build
OBJS_RELEASE = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executable name for Release
TARGET_RELEASE = $(BUILD_DIR)/project_release

# Default target (Release build)
all: $(TARGET_RELEASE)

# Rule for building the Release target
$(TARGET_RELEASE): $(OBJS_RELEASE)
	$(CXX) $(CXXFLAGS) -o $@ $^ -I$(SFML_INCLUDE) -L$(SFML_LIB_PATH) $(SFML_LIBS)

# Rule for compiling object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(SFML_INCLUDE)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

