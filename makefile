# $

#SHELL =  /bin/sh

TARGET	= PPC

CODETYPE	= PPC

VERSION		= 0

G_IPATH		= -I./

WRAPPERS    =

G_DEFINES	= -g -D$(CODETYPE) -D__MORPHOS_DIRECTCALL -DSYSTEM_PRIVATE $(WRAPPERS)
G_OPTFLAGS	= -O2 \
		 -mcpu=604e \
		 -mmultiple \
		 -noixemul \
		 #-fno-builtin \
		 #-fomit-frame-pointer \
		 #-fverbose-asm  \
		 #-mstrict-align \
		 #-mno-prototype \
		 #-mregnames \
		 #-Wformat \
		 #-Wunused \
		 #-Wuninitialized \
		 #-Wconversion \
		 #-Wstrict-prototypes \
		 #-Werror-implicit-function-declaration

APATH	= -iinclude/
AFLAGS	= -M4000
VPATH   :=


#CC_PPC		= ppc-morphos-gcc -idirafter
CC_PPC		= ppc-morphos-gcc
LD_PPC		= ppc-morphos-gcc
LCFLAGS_PPC	= $(DEB) -Wall -O2 -mcpu=604e -mmultiple -fomit-frame-pointer -noixemul -nostdlib
LDFLAGS_PPC	= -noixemul -nostartfiles

OUT = openpci.library.elf

##############################################################################

#nobuild:
#	@echo "I won't build until someone removes all the public includes"

all:  $(OUT)  \
	./ppcinline/lowlevel.h

##############################################################################

.SUFFIXES: .o$(TARGET) .asm

.c.o$(TARGET):
#	 ppc-morphos-gcc $(G_CFLAGS) $(G_OPTFLAGS) $(G_DEBUG) $(G_DEFINES) $(G_IPATH) -S -o $*.s $*.c
#	 ppc-morphos-as -v -o$*.o$(TARGET) $*.s
	 $(CC_PPC) $(G_CFLAGS) $(G_OPTFLAGS) $(G_DEBUG) $(G_DEFINES) $(G_IPATH) -o $*.o$(TARGET) -c $*.c

#.s.o$(TARGET):
#	 ppc-morphos-as -o$*.o$(TARGET) $*.s

.asm.o$(TARGET):
	basm $(AFLAGS) $(APATH) -o$*.o$(TARGET) $*.asm

##############################################################################

LIB		= /gg/lib
#/ade/morphos/lib

SRC		=

# Mediator Source
SRCM		= MediatorOpenPci/

# Grex Source
SRCG		= GrexOpenPci/

# Pegasos PCIX Source
SRCX		= PCIXOpenPci/

# Prometheus Source
SRCP		= PrometheusOpenPci/

# PowerPci Source
SRCA		= PowerPciOpenPci/


DEST	   =

# Mediator Destination
DESTM		= MediatorOpenPci/

# Grex Destination
DESTG		= GrexOpenPci/

# Pegasos PCIX Destination
DESTX		= PCIXOpenPci/

# Prometheus Destination
DESTP		= PrometheusOpenPci/

# PowerPci Destination
DESTA		= PowerPciOpenPci/

GLOBAL	= \
		openpcidata.h

openpci.o$(TARGET):					   $(SRC)openpci.c                 openpci.library_VERSION.h
openpcifunctable.o$(TARGET):        $(SRC)openpcifunctable.c        openpcifunctable.h $(GLOBAL)
pcibus.o$(TARGET):                  $(SRC)pcibus.c                  $(GLOBAL)
pci_find.o$(TARGET):                $(SRC)pci_find.c                $(GLOBAL)
pci_in_out.o$(TARGET):              $(SRC)pci_in_out.c              $(GLOBAL)
pci_interrupt.o$(TARGET):           $(SRC)pci_interrupt.c           $(GLOBAL)
pci_set_master.o$(TARGET):          $(SRC)pci_set_master.c          $(GLOBAL)
pci_readwrite_config.o$(TARGET):    $(SRC)pci_readwrite_config.c    $(GLOBAL)
pci_allocfree_dma_mem.o$(TARGET):   $(SRC)pci_allocfree_dma_mem.c   $(GLOBAL)
pci_logictophysic_addr.o$(TARGET):  $(SRC)pci_logictophysic_addr.c  $(GLOBAL)
pci_obtainrelease_card.o$(TARGET):  $(SRC)pci_obtainrelease_card.c  $(GLOBAL)
debug.o$(TARGET):                   $(SRC)debug.c                   $(GLOBAL)
$(DESTP)PrometheusWrapper.o$(TARGET):       $(SRCP)PrometheusWrapper.c       $(GLOBAL) $(SRCP)PrometheusWrapper.h openpci_protosWrapper.h
$(DESTP)Ppci_readwrite_config.o$(TARGET):   $(SRCP)Ppci_readwrite_config.c   $(GLOBAL)
$(DESTP)Ppci_set_master.o$(TARGET):         $(SRCP)Ppci_set_master.c         $(GLOBAL)
$(DESTP)Ppci_allocfree_dma.o$(TARGET):      $(SRCP)PPci_allocfree_dma.c      $(GLOBAL)
$(DESTP)Ppci_interrupt.o$(TARGET):          $(SRCP)Ppci_interrupt.c          $(GLOBAL)
$(DESTP)Ppci_in_out.o$(TARGET):             $(SRCP)Ppci_in_out.c             $(GLOBAL) InOut.h
$(DESTP)Ppci_logictophysic_addr.o$(TARGET): $(SRCP)Ppci_logictophysic_addr.c $(GLOBAL)
$(DESTP)Ppci_obtainrelease_card.o$(TARGET): $(SRCP)Ppci_obtainrelease_card.c $(GLOBAL)

OBJS	= \
   $(SRC)openpci.o$(TARGET)\
	$(SRC)openpcifunctable.o$(TARGET)\
	$(SRC)pcibus.o$(TARGET)\
	$(SRC)pci_find.o$(TARGET)\
	$(SRC)pci_in_out.o$(TARGET)\
	$(SRC)pci_interrupt.o$(TARGET)\
	$(SRC)pci_set_master.o$(TARGET)\
	$(SRC)pci_readwrite_config.o$(TARGET)\
	$(SRC)pci_allocfree_dma_mem.o$(TARGET)\
	$(SRC)pci_logictophysic_addr.o$(TARGET)\
	$(SRC)pci_obtainrelease_card.o$(TARGET)\
	$(SRC)debug.o$(TARGET)\
#   $(DESTP)PrometheusWrapper.o$(TARGET)\
#   $(DESTP)Ppci_readwrite_config.o$(TARGET)\
#   $(DESTP)Ppci_set_master.o$(TARGET)\
#   $(DESTP)Ppci_allocfree_dma.o$(TARGET)\
#   $(DESTP)Ppci_interrupt.o$(TARGET)\
#   $(DESTP)Ppci_in_out.o$(TARGET)\
#   $(DESTP)Ppci_logictophysic_addr.o$(TARGET)\
#   $(DESTP)Ppci_obtainrelease_card.o$(TARGET)\
#   $(DESTA)PowerPciWrapper.o$(TARGET)\

#####################################################################

openpci.library.elf: $(OBJS)
	$(CC_PPC) $(LDFLAGS_PPC) $^ -lsyscall -o $@.db
#	bin:ld -v -L./lib $(OBJS) $(LIB)/libstringio.a $(LIB)/libstring.a $(LIB)/libm.a $(LIB)/libmath.a $(LIB)/libamiga.a $(LIB)/libsyscall.a -o $(OUT).db
	ppc-morphos-strip -o $(OUT) --remove-section=.comment $(OUT).db


BUMP:
   bumprev2 VERSION=$(VERSION) FILE=$(SRC)openpci.library_VERSION TAG=openpci.library ADD="© 2002 by Benjamin Vernoux"


DUMP:
	objdump --section-headers --all-headers --reloc --disassemble-all $(OUT).db >$(OUT).dump

clean:
	-rm -f *.o$(TARGET) PromotheusOpenPci/*.o$(TARGET) $(OUT) *.db *.dump
	
install: openpci.library.elf openpciinfo
	-mkdir -p SYS:MorphOS/C SYS:MorphOS/Libs
	-cp openpci.library.elf mossys:libs/openpci.library
	-cp openpciinfo/OpenPciInfo.elf mossys:c/OpenPciInfo
	-flushlib openpci.library

openpciinfo:
	make -C OpenPciInfo

install-iso: openpci.library.elf openpciinfo
	mkdir -p $(ISOPATH)morphos/C $(ISOPATH)morphos/Libs
	cp openpci.library.elf $(ISOPATH)morphos/Libs/openpci.library
	cp openpciinfo/OpenPciInfo.elf $(ISOPATH)morphos/C/OpenPciInfo


##############################################################################

.PHONY: all BUMP DUMP clean install install-iso openpciinfo

