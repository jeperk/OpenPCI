#
# OpenPciInfo gcc makefile
#

DEB =
#DEB = -DDEBUG

# -fomit-frame-pointer is evil on m68k gcc!
CC_68K		= gcc
LD_68K		= gcc
LCFLAGS_68K	= $(DEB) -Wall -O2 -m68020-60 -mregparm=3 -noixemul -nostdlib
LDFLAGS_68K	= -noixemul -nostdlib
LIBS_68K	= -lamiga

CC_PPC		= ppc-morphos-gcc
LD_PPC		= ppc-morphos-gcc
LCFLAGS_PPC	= $(DEB) -Wall -O2 -mcpu=604e -mmultiple -fomit-frame-pointer -noixemul
LDFLAGS_PPC	= -noixemul
LIBS_PPC	= -labox -lsyscall


##############################################################################
# object files

OBJS_68K	= OpenPciInfo.o68k
OBJS_PPC	= OpenPciInfo.oPPC
HEADERS	= PciBusInfo.h debug.h

##############################################################################
# standard targets

.PHONY:	all install clean


all: OpenPciInfo.elf

install:
	copy clone OpenPciInfo.elf c:

clean:
	$(RM) $(OBJS_68K) $(OBJS_PPC)

##############################################################################
# dependencies

OpenPciInfo.oPPC:	PciBusInfo.h

##############################################################################

.SUFFIXES:
.SUFFIXES: .c .oPPC .o68K

%.o68K:	%.c
	$(CC_68K) $(LCFLAGS_68K) -c $< -o $@

%.oPPC:	%.c
	$(CC_PPC) $(LCFLAGS_PPC) -c $< -o $@

OpenPciInfo:     $(OBJS_68K)
	$(LD_68K) $(LDFLAGS_68K) $^ -o $@ $(LIBS_68K)

OpenPciInfo.elf: $(OBJS_PPC)
	$(LD_PPC) $(LDFLAGS_PPC) $^ -o $@.db $(LIBS_PPC)
	ppc-morphos-strip -o $@ --remove-section=.comment $@.db
	@protect >nil: $@ +e
	@#ppc-morphos-objdump --syms $@ | grep *UND*

#cnet.device: cnet.o
#	$(CC) $< $(LFLAGS) -o $@
#
#cnet.o: cnet.c $(HEADERS)
#	$(CC) $(CFLAGS) -c $< -o $@
#
#cnet.device.elf: cnet_mos.o
#	$(CC_MOS) $< $(LFLAGS_MOS) -o $@
#
#cnet_mos.o: cnet.c $(HEADERS)
#	$(CC_MOS) $(CFLAGS_MOS) -c $< -o $@
