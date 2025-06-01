# compiling macros
CC = g++
CFLAGS = -g
LDFLAGS = -g

########## PROGRAM ARGUMENTS ###########
# file macros
HEAD =
OBJ = philosopher.o
BIN = philosopher
ARG =
########################################

OBJ2 = philosopher_coinflip.o
BIN2 = philosopher_coinflip

#targets to execute with make. all is default.
.PHONY: all run exe clean immaculate

all: $(BIN) $(BIN2) clean

run: all exe immaculate

exe:
	./$(BIN) $(ARG)

clean:
	@rm -f core* *.o *~

immaculate: clean
	@rm -f $(BIN) $(BIN2)

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
