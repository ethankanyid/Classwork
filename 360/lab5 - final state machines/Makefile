# compiling macros
CC = gcc
CFLAGS = -g -Wall -Wstrict-prototypes
LDFLAGS = -g

########## PROGRAM ARGUMENTS ###########
# file macros
HEAD =

OBJ1 = codestats_pt1.o
BIN1 = main1
ARG = codestats_pt1.c part6_weird_char_constants.c

OBJ2 = codestats_pt2.o
BIN2 = main2

OBJ3 = codestats_pt3.o
BIN3 = main3

OBJ4 = codestats_pt4.o
BIN4 = main4

OBJ5 = codestats_pt5.o
BIN5 = main5

OBJ6 = codestats_pt6.o
BIN6 = main6

OBJ7 = codestats_pt7.o
BIN7 = main7
########################################

#targets to execute with make. all is default.
.PHONY: all run exe clean immaculate

all: $(BIN1) $(BIN2) $(BIN3) $(BIN4) $(BIN5) $(BIN6) $(BIN7) clean

run: all exe immaculate

exe:
	./$(BIN1) $(ARG)
	./$(BIN2) $(ARG)
	./$(BIN3) $(ARG)
	./$(BIN4) $(ARG)
	./$(BIN5) $(ARG)
	./$(BIN6) $(ARG)
	./$(BIN7) $(ARG)

clean:
	@rm -f core* *.o *~

immaculate: clean
	@rm -f $(BIN1) $(BIN2) $(BIN3) $(BIN4) $(BIN5) $(BIN6) $(BIN7)

# compile object files
# This says how to compile any ".c" into a "*.o"
# "$<" means "the first file (or, here, pattern) to the right of the ":" above.
%.o: %.c $(HEAD)
	@$(CC) -c -o $@ $< $(CFLAGS)

# link into executable
# "$^" means "all of the files to the right of the ":".
# "$@" means the "target" (whats on the left of the ":").
# Note that $(CC) is used both for compiling and loading.
$(BIN1): $(OBJ1)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BIN2): $(OBJ2)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BIN3): $(OBJ3)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BIN4): $(OBJ4)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BIN5): $(OBJ5)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BIN6): $(OBJ6)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(BIN7): $(OBJ7)
	@$(CC) -o $@ $^ $(LDFLAGS)
#@ suppresses commands
