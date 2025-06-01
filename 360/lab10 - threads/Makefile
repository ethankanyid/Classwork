# compiling macros
CC = gcc
CFLAGS = -g -Wall -Wstrict-prototypes
LDFLAGS = -g -lrt -lm

########## PROGRAM ARGUMENTS ###########
# file macros
HEAD = a2d.h tspec_diff.h mat_mul_pt1.h eprintf.h mat_mul_pt2.h
ARG = -n 750 -m 750 -p 750
########################################

OBJ = tspec_diff.o mat_mul_pt1.o experiment_tmm_pt1.o
BIN = experiment_tmm_pt1

OBJ2 = tspec_diff.o mat_mul_pt2.o experiment_tmm_pt2.o
BIN2 = experiment_tmm_pt2

#targets to execute with make. all is default.
.PHONY: all run exe clean immaculate

all: $(BIN) $(BIN2) clean

run: all exe immaculate

exe:
	./$(BIN2) $(ARG)

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
