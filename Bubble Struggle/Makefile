# Compiler and flags
CXX = g++
CXXFLAGS = -O3 -std=c++17
CXXFLAGS += -DMAKELINUX
CXXFLAGS += -DMAKEDOCKER

# SFML include and library paths (install: apt-get install libsfml-dev)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE = /usr/include
SFML_LIB_PATH = /usr/lib

# Directories
SRC_DIR = bubble-struggle
BUILD_DIR = build

# Source files
SRCS = $(SRC_DIR)/Main.cpp \
	$(SRC_DIR)/ResourceManager.cpp \
	$(SRC_DIR)/Button.cpp \
	$(SRC_DIR)/LevelLoader.cpp \
	$(SRC_DIR)/GameToolBar.cpp \
	$(SRC_DIR)/Board.cpp \
	$(SRC_DIR)/Background.cpp \
	$(SRC_DIR)/Flame.cpp \
	$(SRC_DIR)/LoadScreen.cpp \
	$(SRC_DIR)/Menu.cpp \
	$(SRC_DIR)/Player.cpp \
	$(SRC_DIR)/PlayerOne.cpp \
	$(SRC_DIR)/PlayerTwo.cpp \
	$(SRC_DIR)/Command.cpp \
	$(SRC_DIR)/BossBall.cpp \
	$(SRC_DIR)/Unmoveable.cpp \
	$(SRC_DIR)/youSure.cpp \
	$(SRC_DIR)/Moveable.cpp \
	$(SRC_DIR)/SimpleArrow.cpp \
	$(SRC_DIR)/Flame.cpp \
	$(SRC_DIR)/Board.cpp \
	$(SRC_DIR)/FrozenArrowItem.cpp \
	$(SRC_DIR)/Spikes.cpp \
	$(SRC_DIR)/Drawable.cpp \
	$(SRC_DIR)/RegisterFunctionTemplates.cpp \
	$(SRC_DIR)/LevelLoader.cpp \
	$(SRC_DIR)/ZeroGravityBall.cpp \
	$(SRC_DIR)/Player.cpp \
	$(SRC_DIR)/LaserItem.cpp \
	$(SRC_DIR)/OneUpItem.cpp \
	$(SRC_DIR)/Menu.cpp \
	$(SRC_DIR)/ResourceManager.cpp \
	$(SRC_DIR)/Sound.cpp \
	$(SRC_DIR)/LivesBar.cpp \
	$(SRC_DIR)/HeldBall.cpp \
	$(SRC_DIR)/Controller.cpp \
	$(SRC_DIR)/Button.cpp \
	$(SRC_DIR)/FrozenWeapon.cpp \
	$(SRC_DIR)/AbsBall.cpp \
	$(SRC_DIR)/PlayerOne.cpp \
	$(SRC_DIR)/Sheild.cpp \
	$(SRC_DIR)/GameToolBar.cpp \
	$(SRC_DIR)/Background.cpp \
	$(SRC_DIR)/AbstractItem.cpp \
	$(SRC_DIR)/PlayerTwo.cpp \
	$(SRC_DIR)/UpDownBall.cpp \
	$(SRC_DIR)/CashItem.cpp \
	$(SRC_DIR)/SimpleArrowItem.cpp \
	$(SRC_DIR)/LoadScreen.cpp \
	$(SRC_DIR)/LaserWeapon.cpp \
	$(SRC_DIR)/Door.cpp \
	$(SRC_DIR)/ProjectileBall.cpp \
	$(SRC_DIR)/TimeItem.cpp \
	$(SRC_DIR)/Ball.cpp \
	$(SRC_DIR)/AbstractWeapon.cpp \
	$(SRC_DIR)/DrawableFactory.cpp \
	$(SRC_DIR)/WindowCONST.cpp \
	$(SRC_DIR)/DirectHitBall.cpp \
	$(SRC_DIR)/Wall.cpp \
	$(SRC_DIR)/SheildItem.cpp \

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

