
EXEC=PlanarWar
CC=gcc
CCFLAGS=-Wall -g -fPIC

LDFLAGS =-lraylib -lm 
LDDIR =-Llib -Iinclude
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
LIB_DIR=lib

CFILES=$(wildcard $(SRC_DIR)/*.c)
OFILES=$(CFILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)



all: $(EXEC)

run : all 
	cd $(BIN_DIR);\
	ls;\
	export LD_LIBRARY_PATH=../$(LIB_DIR);\
	./$(EXEC)

$(EXEC) : $(OFILES)
	$(CC) $(CCFLAGS) $(LDDIR) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -c $(CCFLAGS) $(LDDIR) $(LDFLAGS) $< -o $@

.PHONY : clean mrproper

clean: 
	$(RM) $(OFILES)
	$(RM) $(DFILES)

mrproper: clean
	$(RM) bin/$(EXEC)
