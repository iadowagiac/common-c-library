.PHONY: all clean check
.SUFFIXES: .c .o

include config.mk

LDADD := $(shell pkg-config --libs check)

# Binary Files.
BINS = checkall

# Object Files.
OBJS = ${SRCS:.c=.o}

# Dependencies.
DEPS = ../arrays.h \
       ../tables.h \
       ../stacks.h \
       ../queues.h \

# Source Files.
SRCS = checkall.c \
       ckarrays.c \
       cktables.c \
       ckstacks.c \
       ckqueues.c

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

