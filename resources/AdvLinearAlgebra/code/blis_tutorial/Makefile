BLIS_PREFIX = /usr/local
BLIS_LIB = $(BLIS_PREFIX)/lib/libblis.a
BLIS_INC = $(BLIS_PREFIX)/include/blis
TF_LIB = $(BLIS_PREFIX)/lib
TF_INC = $(BLIS_PREFIX)/include/tensorflow

OTHER_LIBS  = -L/usr/lib -L$(TF_LIB) -lm -lpthread -ltensorflow

CC = gcc
CFLAGS = -O2 -g -I$(BLIS_INC) -I$(TF_INC)
LINKER = $(CC)

OBJS_UNUSED = 00obj_basic.c 01obj_attach.c
OBJS = 02obj_ij.c

all: $(OBJS)
	$(LINKER) $(CFLAGS) $(OBJS) $(BLIS_LIB) $(OTHER_LIBS) -o a.out