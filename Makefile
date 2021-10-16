SRC_DIR  	:= src
BIN_DIR  	:= bin
LIB_DIR  	:= lib
INC_DIR  	:= inc
OBJ_DIR  	:= obj

SRCEXTS  	:= .c .C .cc .cpp .CPP .c++ .cxx .cp
HDREXTS  	:= .h .H .hh .hpp .HPP .h++ .hxx .hp

TARGETS  	:= $(BIN_DIR)/program
SOURCES  	:= $(wildcard $(addprefix $(SRC_DIR)/*,$(SRCEXTS)))
# SOURCES := $(shell find src -name "*.c")
HEADERS  	:= $(sort $(dir $(wildcard $(addprefix $(INC_DIR)/*,$(HDREXTS)))))
# OBJECTS  	:= $(addsuffix .o, $(basename $(SOURCES)))
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# HEADERS := $(shell find inc -name "*.h")
# HEADERDIRS := $(sort $(dir $(HEADERS)))

CXX          = gcc
CXXFLAGS     = -g -Wall

.PHONY: all clean

all: $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CXX) $^ -o $@

INCLUDEFLAGS := $(addprefix -I,$(HEADERS))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $< -c $(INCLUDEFLAGS) -o $@

clean:
	-rm $(OBJECTS) $(TARGETS)

run:
	$(BIN_DIR)/program
