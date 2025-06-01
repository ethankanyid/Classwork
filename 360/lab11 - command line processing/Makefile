# compiling macros
CC = gcc
CFLAGS = -g -Wall -Wstrict-prototypes
LDFLAGS = -g -lrt -lm

########## PROGRAM ARGUMENTS ###########
# file macros
HEAD =
OBJ = lander_pt1.o
BIN = lander_pt1
ARG = --max-thrust 40
########################################

OBJ1 = lander_pt2.o
BIN1 = lander_pt2

OBJ2 = lander_pt3.o
BIN2 = lander_pt3

OBJ3 = lander_pt4.o
BIN3 = lander_pt4

OBJ4 = lander_pt5.o
BIN4 = lander_pt5

#targets to execute with make. all is default.
.PHONY: all run exe clean immaculate

all: $(BIN) $(BIN1) $(BIN2) $(BIN3) $(BIN4) clean

run: all exe immaculate

exe:
	./$(BIN4) $(ARG)

clean:
	@rm -f core* *.o *~

immaculate: clean
	@rm -f $(BIN) $(BIN1) $(BIN2) $(BIN3) $(BIN4)

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

$(BIN1): $(OBJ1)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BIN2): $(OBJ2)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BIN3): $(OBJ3)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BIN4): $(OBJ4)
	@$(CC) -o $@ $^ $(LDFLAGS)

#@ suppresses commands
