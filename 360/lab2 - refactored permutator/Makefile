# compiling macros
CC = gcc
CFLAGS = -g -Wall -Wstrict-prototypes
LDFLAGS = -g

# file macros
HEAD = gen_perms.h
OBJ = permute.o gen_perms.o
OBJ2 = perm.o
BIN = permute
BIN2 = perm

ARG = red green blue

#targets to execute with make. all is default.
.PHONY: all run exe clean immaculate

all: $(BIN) $(BIN2) clean

run: all exe immaculate

exe:
	./$(BIN) $(ARG)

clean:
	@rm -f core* *.o *~

immaculate: clean
	@rm -f $(BIN)
	@rm -f $(BIN2)



# compile object files
# This says how to compile any ".c" into a "*.o"
# "$<" means "the first file (or, here, pattern) to the right of the ':'" above.
%.o: %.c $(HEAD)
	@$(CC) -c -o $@ $< $(CFLAGS)

# link into executable
# "$^" means "all of the files to the right of the ':'".
# "$@" means the "target" (what's on the left of the ':'").
# Note that $(CC) is used both for compiling and loading.
$(BIN): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BIN2): $(OBJ2)
	@$(CC) -o $@ $^ $(LDFLAGS)

#@ suppresses commands
