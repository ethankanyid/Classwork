# compiling macros
CC = g++
CFLAGS = -g
LDFLAGS = -g

# file macros
HEAD = TM.h errorlog.h
OBJ = TM.o commands.o errorlog.o tmdef.o tmstrdef.o tminit.o
BIN = TM

ARG = anbn

#targets to execute with make. all is default.
.PHONY: all run exe clean immaculate

all: $(BIN) clean

run: all exe immaculate

exe:
	./$(BIN) $(ARG)

clean:
	@rm -f core* *.o *~

immaculate: clean
	@rm -f $(BIN)


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

#@ suppresses commands
