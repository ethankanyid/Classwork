ASFLAGS = -g -ggdb -O0 -KPIC
CFLAGS = -g -c -ggdb -O0
LDFLAGS = -g

C_SRCS = $(wildcard *.c)
A_SRCS = $(wildcard *.s)

C_OBJS = $(subst .c,.o, $(C_SRCS))
A_OBJS = $(subst .s,.o, $(A_SRCS))

all: $(C_OBJS) $(A_OBJS)
	$(CC) $(LDFLAGS) -o main $? $(LDLIBS)

clean:
	rm -f main $(A_OBJS) $(C_OBJS)

test: test.log

test.log: all
	./main | tee test.log

.PHONY: all clean test
