#/* Andre Augusto Giannotti Scota (a2gs)
# * andre.scota@gmail.com
# */


#/* makefile
# *
# *  Who     | When       | What
# *  --------+------------+----------------------------
# *   a2gs   | 13/08/2018 | Creation
# *          |            |
# */


# C flags:
CFLAGS_OPTIMIZATION = -g
#CFLAGS_OPTIMIZATION = -O3
CFLAGS_VERSION = -std=c11
CFLAGS_WARNINGS = -Wall -Wextra -Wno-unused-parameter -Wno-unused-but-set-parameter
CFLAGS_DEFINES = -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -D_POSIX_SOURCE=1 -D_DEFAULT_SOURCE=1 -D_GNU_SOURCE=1
CFLAGS = $(CFLAGS_OPTIMIZATION) $(CFLAGS_VERSION) $(CFLAGS_WARNINGS) $(CFLAGS_DEFINES)

# Specific libraries (project libraries ./libs/):
LIB_RPN = rpn

# Paths normalizes
SOURCEPATH = ./src
BINPATH = ./bin
INCLUDEPATH = ./include

INCLUDEPATH_FLAG = -I$(INCLUDEPATH) -I$(BINPATH)

# System shell utilities
CC = gcc
RM = rm -f
CP = cp
AR = ar
RANLIB = ranlib

all: clean lrpn RPNiface

lrpn:
	@echo "=== lib RPN =============="
	$(CC) -c -o$(BINPATH)/librpn.o $(SOURCEPATH)/librpn.c $(INCLUDEPATH_FLAG) $(CFLAGS) -DRPN_STACK_SIZE=50
	$(AR) rc $(BINPATH)/librpn.a $(BINPATH)/librpn.o
	$(RANLIB) $(BINPATH)/librpn.a
	$(CP) $(INCLUDEPATH)/librpn.h $(BINPATH)
	-$(RM) $(BINPATH)/librpn.o

RPNiface: lrpn
	@echo "=== client =================="
	$(CC) -o $(BINPATH)/ncRPNcalc $(SOURCEPATH)/ncRPNcalc.c -I$(BINPATH) -L$(BINPATH) -lncurses -l$(LIB_RPN) $(CFLAGS) -lm

clean:
	@echo "=== clean ==================="
	-$(RM) $(BINPATH)/*
