# compiling macros
CC = gcc
CFLAGS = -g -Wall -Wstrict-prototypes
LDFLAGS = -g

########## PROGRAM ARGUMENTS ###########
# file macros
HEAD = except.h

OBJ = except_demo.c except.o
BIN = except_demo

OBJ2 = find_file.o except.o
BIN2 = find_file

ARG = -v Makefile
########################################

#targets to execute with make. all is default.
.PHONY: all run exe clean immaculate

all: $(BIN2) $(BIN)

run: all exe immaculate

exe:
	./$(BIN2) $(ARG)

clean:
	@rm -f core* *.o *~
	@rm -rf core* *.dSYM *~

immaculate: clean
	@rm -f $(BIN)
	@rm -f $(BIN2)

# compile object files
# This says how to compile any ".c" into a "*.o"
# "$<" means "the first file (or, here, pattern) to the right of the ":" above.
%.o: %.c $(HEAD)
	@$(CC) -c -o $@ $< $(CFLAGS)

# link into executable
# "$^" means "all of the files to the right of the ":".
# "$@" means the "target" (whats on the left of the ":").
# Note that $(CC) is used both for compiling and loading.
$(BIN): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BIN2): $(OBJ2)
	@$(CC) -o $@ $^ $(LDFLAGS)

#@ suppresses commands
