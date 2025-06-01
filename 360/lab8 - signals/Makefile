# compiling macros
CC = gcc
CFLAGS = -g -Wall -Wstrict-prototypes
LDFLAGS = -g

########## PROGRAM ARGUMENTS ###########
# file macros
HEAD = critical_section.h syscall_check.h eprintf.h
OBJ = killme_pt1.c critical_section.c
BIN = killme_pt1
ARG =

OBJ2 = killme_pt2.c critical_section.c
BIN2 = killme_pt2

OBJ3 = killme_pt3.c critical_section.c
BIN3 = killme_pt3

########################################

#targets to execute with make. all is default.
.PHONY: all run exe clean immaculate

all: $(BIN) $(BIN2) $(BIN3) clean

run: all immaculate

clean:
	@rm -f core* *.o *~

immaculate: clean
	@rm -f $(BIN) $(BIN2) $(BIN3)

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

$(BIN3): $(OBJ3)
	@$(CC) -o $@ $^ $(LDFLAGS)

#@ suppresses commands
