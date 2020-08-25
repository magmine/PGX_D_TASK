TARGET   := solution
CXX      := g++ -std=c++11
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -Wshadow -Wnon-virtual-dtor
LDLIBS   := -pthread
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
SRC      := \
	$(wildcard Sources/*.cpp) \
	$(wildcard tests/*.cpp)
OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
INCLUDES  := -IHeaders
INPUT_FILES := Input
TESTS    := tests

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c  $< -o $@ $(LDLIBS)

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDLIBS)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

tests: LDLIBS += /home/mmaghous/software/Cpp/libs/googletest/googletest/lib/libgtest.a
tests: INCLUDES += -I/home/mmaghous/software/Cpp/libs/googletest/googletest/include/
tests: all


clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

fclean: clean
	@/bin/rm -f $(TARGET)

.PHONY: all build clean debug release

re: fclean all
