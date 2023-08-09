.PHONY: all clean check
.SUFFIXES: .c .o

# Object Files.
OBJS = ${SRCS:.c=.o}

# Source Files.
SRCS = array.c \
       table.c \
       stack.c \
       queue.c

all:

clean:
	rm -f ${OBJS}

check: all
	cd testsuite && make check

