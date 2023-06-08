BLIS_PREFIX = /usr/local
BLIS_LIB = $(BLIS_PREFIX)/lib/libblis.a
BLIS_INC = $(BLIS_PREFIX)/include/blis

OTHER_LIBS  = -L/usr/lib -lm -lpthread

CC = gcc
CFLAGS = -O2 -g -I$(BLIS_INC)
LINKER = $(CC)

OBJS = 00obj_basic.c

all: $(OBJS)
	$(LINKER) $(CFLAGS) $(OBJS) $(BLIS_LIB) $(OTHER_LIBS) -o a.out