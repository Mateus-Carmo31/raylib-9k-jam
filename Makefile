##
# Raylib 9k Jam
#
# @file
# @version 0.1

PLATFORM ?= PLATFORM_DESKTOP

EXEC_NAME := game
EXEC_EXT := .exe
RAYLIB := ./external/libs/desktop/libraylib.a

SRC_DIR := ./src
OBJ_DIR := ./out
BUILD_DIR := ./out/build
ASSETS_DIR := ./assets
INC_DIRS := $(shell find $(SRC_DIR) -type d) ./external/include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

SRCS := $(shell find $(SRC_DIR) -name '*.cpp' -or -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%=$(OBJ_DIR)/%.o)
LIBS :=

CC = gcc
CXX = g++
OBJ_FLAGS := -g -Wall $(CUSTOM_FLAGS)
EXEC_FLAGS := -g -Wall $(CUSTOM_FLAGS)
LIBS_DIRS := ./external/libs

ifeq ($(PLATFORM),PLATFORM_WEB)
	CC = emcc
	CXX = emcc
	EXEC_FLAGS := $(EXEC_FLAGS) -sUSE_GLFW=3 --shell-file $(SRC_DIR)/custom_shell.html --preload-file $(ASSETS_DIR) --emrun
	EXEC_EXT := .html
	RAYLIB := ./external/libs/web/libraylib.a
else
	LIBS := -lGL -lm -lpthread -ldl -lrt -lX11
endif

LIBS_FLAGS := $(addprefix -L,$(LIBS_DIRS))

# you only need to link the library when putting the .o files together
build: $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CXX) -o $(BUILD_DIR)/$(EXEC_NAME)$(EXEC_EXT) $(OBJS) $(RAYLIB) $(INC_FLAGS) $(LIBS_FLAGS) $(LIBS) -D$(PLATFORM) $(EXEC_FLAGS)

# gotta specify the defines with -D when building the objs tho.
$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(INC_FLAGS) -D$(PLATFORM) $(OBJ_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(INC_FLAGS) -D$(PLATFORM) $(OBJ_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(OBJ_DIR)/*

# end
