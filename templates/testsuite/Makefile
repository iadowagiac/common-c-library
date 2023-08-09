.PHONY: all clean check
.SUFFIXES: .c .o

include config.mk

LDADD := $(shell pkg-config --libs check)

# Binary Files.
BINS = checkall

# Object Files.
OBJS = ${SRCS:.c=.o}

# Dependencies.
DEPS = ../array.c \
       ../table.c \
       ../stack.c \
       ../queue.c

# Source Files.
SRCS = checkall.c \
       ckarray.c \
       cktable.c \
       ckstack.c \
       ckqueue.c

all: ${BINS}

clean:
	rm -f ${BINS} ${OBJS}

check: all
	@for t in ${BINS}; do ./$$t ; done

checkall: ${OBJS}
	${CC} ${LDFLAGS} -o $@ $^ ${LDADD}

${SRCS}: ${DEPS}

.c.o:
	${CC} ${CFLAGS} -c -o $@ $<

