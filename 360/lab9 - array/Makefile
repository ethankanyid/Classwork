# compiling macros
CC = gcc
CFLAGS = -g -Wall -Wstrict-prototypes
LDFLAGS = -g

########## PROGRAM ARGUMENTS ###########
# file macros
HEAD = allocarray.h i2d.h
OBJ = plotz2_pt1.o
BIN = plotz2_pt1

########################################

OBJ2 = plotz2_pt2.o
BIN2 = plotz2_pt2

OBJ3 = plotz2_pt3.o
BIN3 = plotz2_pt3

OBJ4 = plotz2_pt4.o
BIN4 = plotz2_pt4

#targets to execute with make. all is default.
.PHONY: all run clean immaculate

all: $(BIN) $(BIN2) $(BIN3) $(BIN4) clean

run: all exe immaculate

clean:
	@rm -f core* *.o *~

immaculate: clean
	@rm -f $(BIN) $(BIN2) $(BIN3) $(BIN4)

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
	@$(CC) $(LDFLAGS) $^ -lm -o $@

$(BIN2): $(OBJ2)
	@$(CC) $(LDFLAGS) $^ -lm -o $@

$(BIN3): $(OBJ3)
	@$(CC) $(LDFLAGS) $^ -lm -o $@

$(BIN4): $(OBJ4)
	@$(CC) $(LDFLAGS) $^ -lm -o $@

#@ suppresses commands
