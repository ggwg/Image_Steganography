# Directories
SRC_DIR = src/
LIB_DIR = lib/
INC_DIR = inc/
OBJ_DIR = obj/
DBG_DIR = debug/
TST_DIR = test/

# C Compiler options
CC 	   = gcc
CFLAGS = -Wall -g 
IFLAGS = -I$(INC_DIR)
LFLAGS = -L$(LIB_DIR)

# Files to use in compilation
OBJCTS = bmp.o decode.o encode.o main.o utils.o encrypt.o encrypt_utils.o
# Testing files
TST_OBJCTS = encrypt.o encrypt_utils.o
# Target output
TARGET = extension
UNITTEST = tests 

all: $(TARGET)

clean:
	rm -rf $(OBJ_DIR)/*.o $(TST_DIR)/*.o $(TARGET) $(UNITTEST)

$(UNITTEST): $(TST_DIR)tests.o $(addprefix $(OBJ_DIR), $(TST_OBJCTS))
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $@ $^

test-clean: 
	rm -rf $(DBG_DIR)/*.out $(DBG_DIR)/*.txt

# Final output requires no changes
$(TARGET) : $(addprefix $(OBJ_DIR), $(OBJCTS))
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $@ $^

# Compiles all src files into objects
obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) -c $^ -o $@ 

.PHONY: test
