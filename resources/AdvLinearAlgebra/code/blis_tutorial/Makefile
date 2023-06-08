BLIS_PREFIX = /usr/local
BLIS_LIB = $(BLIS_PREFIX)/lib/libblis.a
BLIS_INC = $(BLIS_PREFIX)/include/blis

CC = gcc
CFLAGS = -O2 -g -I$(BLIS_INC)
LINKER = $(CC)

OBJS = 00obj_basic.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)
	$(LINKER) $(CFLAGS) $(OBJS) $(BLIS_LIB) $(OTHER_LIBS) -o my_program.x