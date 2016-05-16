
#ifndef OPENPCIFUNCTABLE_H
#define OPENPCIFUNCTABLE_H
#include "openpci_protosWrapper.h"


#ifdef __MORPHOS__

#include <emul/emulregs.h>
#ifndef BASE_EXT_DECL
#define BASE_EXT_DECL
#define BASE_EXT_DECL0 extern struct OpenPciLib *OpenPciBase;
#endif /* !BASE_EXT_DECL */
#ifndef BASE_PAR_DECL
#define BASE_PAR_DECL
#define BASE_PAR_DECL0 void
#endif /* !BASE_PAR_DECL */
#ifndef BASE_NAME
#define BASE_NAME OpenPciBase
#endif /* !BASE_NAME */

BASE_EXT_DECL0

/* Return the bus type found */
unsigned short LIB_pci_bus(void)
{
	return(pci_bus());
}

/* IN/OUT Function for PCI Bus */
/* Byte (8bits) Read/Write */
unsigned char ASM LIB_pci_inb(void)
{
	unsigned long address	=(unsigned long) REG_A0;
	return( (*pci_inb)(address));
}
void ASM LIB_pci_outb(void)
{
	unsigned char value = (unsigned char) REG_D0;
	unsigned long address = (unsigned long) REG_A0;
	(*pci_outb)(value,address);	
}
/* Word (16bits) Read/Write */
unsigned short ASM LIB_pci_inw(void)
{
	unsigned long address = (unsigned long) REG_A0;
	return( (*pci_inw)(address));
}
void ASM LIB_pci_outw(void)
{
	unsigned short value = (unsigned short) REG_D0;
	unsigned long address = (unsigned long) REG_A0;
	(*pci_outw)(value,address);	
}

/* Long (32bits) Read/Write  */
unsigned long ASM LIB_pci_inl(void)
{
	unsigned long address = (unsigned long) REG_A0;
	return( (*pci_inl)(address));
}
void ASM LIB_pci_outl(void)
{
	unsigned long value = (unsigned long) REG_D0;
	unsigned long address = (unsigned long) REG_A0;	
	(*pci_outl)(value,address);	
}


/* Amiga Mem and Pci Mem Read/Write (must be a multiple of 16bytes) (it's a very fast mem bloc copy) */
void ASM LIB_pci_to_hostcpy(void)
{
	void *pcimemsrc = (void *) REG_A0;
	void *memdest = (void *) REG_A1;
	unsigned long packetsize = (unsigned long) REG_D0;
	(*pci_to_hostcpy)(pcimemsrc,memdest,packetsize);
}
void ASM LIB_host_to_pcicpy(void)
{
	void *memsrc = (void *) REG_A0;
	void *pcimemdest = (void *) REG_A1;
	unsigned long packetsize = (unsigned long) REG_D0;
	(*host_to_pcicpy)(memsrc,pcimemdest,packetsize);
}
void ASM LIB_pci_to_pcicpy(void)
{
	void *pcimemsrc = (void *) REG_A0;
	void *pcimemdest = (void *) REG_A1;
	unsigned long packetsize = (unsigned long) REG_D0;
	(*pci_to_pcicpy)(pcimemsrc,pcimemdest,packetsize);
}

/* Pci Find Functions */
struct pci_dev * ASM LIB_pci_find_device(void)
{
	unsigned short vendor = (unsigned short) REG_D0;
	unsigned short device = (unsigned short) REG_D1;
	struct pci_dev *pcidev = (struct pci_dev *) REG_A0;
	return(pci_find_device(vendor,device,pcidev));
}

struct pci_dev * ASM LIB_pci_find_class(void)
{
	unsigned long class = (unsigned long) REG_D0;
	struct pci_dev *pcidev = (struct pci_dev *) REG_A0;
	return(pci_find_class(class,pcidev));
}
struct pci_dev * ASM LIB_pci_find_slot(void)
{
	unsigned char bus = (unsigned char) REG_D0;	
	unsigned long devfn = (unsigned long) REG_D1;
	return(pci_find_slot(bus,devfn));
}

/* Pci Bus Read/Write Config functions */
unsigned char ASM LIB_pci_read_config_byte(void)
{
	unsigned char registernum = (unsigned char) REG_D0;
	struct pci_dev *pcidev = (struct pci_dev *) REG_A0;	
	return( (*pci_read_config_byte)(registernum,pcidev));	
}
unsigned short ASM LIB_pci_read_config_word(void)
{
	unsigned char registernum = (unsigned short) REG_D0;
	struct pci_dev *pcidev = (struct pci_dev *) REG_A0;	
	return( (*pci_read_config_word)(registernum,pcidev));	
}
unsigned long ASM LIB_pci_read_config_long(void)
{
	unsigned char registernum = (unsigned long) REG_D0;
	struct pci_dev *pcidev = (struct pci_dev *) REG_A0;
	return( (*pci_read_config_long)(registernum,pcidev));
}
void ASM LIB_pci_write_config_byte(void)
{
	unsigned char registernum = (unsigned char) REG_D0;
	unsigned char val = (unsigned char) REG_D1;
	struct pci_dev *pcidev = (struct pci_dev *) REG_A0;
	(*pci_write_config_byte)(registernum,val,pcidev);
}
void ASM LIB_pci_write_config_word(void)
{
	unsigned char registernum = (unsigned char) REG_D0;
	unsigned short val = (unsigned short) REG_D1;
	struct pci_dev *pcidev = (struct pci_dev *) REG_A0;
	(*pci_write_config_word)(registernum,val,pcidev);
}
void ASM LIB_pci_write_config_long(void)
{
	unsigned char registernum = (unsigned char) REG_D0;
	unsigned long val = (unsigned long) REG_D1;
	struct pci_dev *pcidev = (struct pci_dev *) REG_A0;
	(*pci_write_config_long)(registernum,val,pcidev);
}

/* Pci Set Bus Master */
BOOL ASM LIB_pci_set_master(void)
{
	struct pci_dev *pcidev = (struct pci_dev *) REG_A0;
	return( (*pci_set_master)(pcidev));
}

/* Interrupt functions */
BOOL ASM LIB_pci_add_intserver(void)
{
	struct Interrupt *PciInterrupt = (struct Interrupt *) REG_A0;
	struct pci_dev *pcidev = (struct pci_dev *) REG_A1;
	return( (*pci_add_intserver)(PciInterrupt,pcidev));
}

void ASM LIB_pci_rem_intserver(void)
{
	struct Interrupt *PciInterrupt = (struct Interrupt *) REG_A0;
	struct pci_dev *pcidev = (struct pci_dev *) REG_A1;
	(*pci_rem_intserver)(PciInterrupt,pcidev);
}

/* Alloc and Free DMA memory for PCI card */
APTR ASM LIB_pci_allocdma_mem(void)
{
	unsigned long size = (unsigned long) REG_D0;
	unsigned long flags = (unsigned long) REG_D1;
	return( (*pci_allocdma_mem)(size,flags));
}

void ASM LIB_pci_freedma_mem(void)
{
	APTR buffer = (APTR) REG_A0;
	unsigned long size = (unsigned long) REG_D0;
	(*pci_freedma_mem)(buffer,size);
}

/* Logic<->Physic Addr conversion */
APTR ASM LIB_pci_logic_to_physic_addr(void)
{
	APTR PciLogicalAddr = (APTR) REG_A0;
	struct pci_dev *pcidev = (struct pci_dev *) REG_A1;
	return( (*pci_logic_to_physic_addr)(PciLogicalAddr,pcidev));	
}

/*************** New functions ***********************/
APTR ASM LIB_pci_physic_to_logic_addr(void)
{
	APTR PciPhysicalAddr = (APTR) REG_A0;
	struct pci_dev *pcidev = (struct pci_dev *) REG_A1;
	return( (*pci_physic_to_logic_addr)(PciPhysicalAddr,pcidev));
}

/* Obtain/Release PCI card */
BOOL ASM LIB_pci_obtain_card(void)
{
	struct pci_dev *pcidev = (struct pci_dev *) REG_A0;
	return( (*pci_obtain_card)(pcidev));
}

void ASM LIB_pci_release_card(void)
{
	struct pci_dev *pcidev = (struct pci_dev *) REG_A0;
	(*pci_release_card)(pcidev);
}

#else /* __MORPHOS__ */

/* Return the bus type found */
unsigned short __saveds LIB_pci_bus(void)
{
	return(pci_bus());
}

/* IN/OUT Function for PCI Bus */
/* Byte (8bits) Read/Write */
unsigned char __saveds ASM LIB_pci_inb(REG(a0,unsigned long address))
{
	return( (*pci_inb)(address));
}
void __saveds ASM LIB_pci_outb(REG(d0,unsigned char value), REG(a0,unsigned long address))
{
	(*pci_outb)(value,address);	
}
/* Word (16bits) Read/Write */
unsigned short __saveds ASM LIB_pci_inw(REG(a0,unsigned long address))
{
	return( (*pci_inw)(address));
}
void __saveds ASM LIB_pci_outw(REG(d0,unsigned short value), REG(a0,unsigned long address))
{
	(*pci_outw)(value,address);	
}

/* Long (32bits) Read/Write  */
unsigned long __saveds ASM LIB_pci_inl(REG(a0,unsigned long address))
{
	return( (*pci_inl)(address));
}
void __saveds ASM LIB_pci_outl(REG(d0,unsigned long value), REG(a0,unsigned long address))
{
	(*pci_outl)(value,address);	
}


/* Amiga Mem and Pci Mem Read/Write (must be a multiple of 16bytes) (it's a very fast mem bloc copy) */
void __saveds ASM LIB_pci_to_hostcpy(REG(a0,void *pcimemsrc), REG(a1,void *memdest), REG(d0,unsigned long packetsize))
{
	(*pci_to_hostcpy)(pcimemsrc,memdest,packetsize);
}
void __saveds ASM LIB_host_to_pcicpy(REG(a0,void *memsrc), REG(a1,void *pcimemdest), REG(d0,unsigned long packetsize))
{
	(*host_to_pcicpy)(memsrc,pcimemdest,packetsize);
}
void __saveds ASM LIB_pci_to_pcicpy(REG(a0,void *pcimemsrc), REG(a1,void *pcimemdest), REG(d0,unsigned long packetsize))
{
	(*pci_to_pcicpy)(pcimemsrc,pcimemdest,packetsize);
}

/* Pci Find Functions */
struct  pci_dev * __saveds ASM LIB_pci_find_device(REG(d0,unsigned short vendor), REG(d1,unsigned short device), REG(a0,struct pci_dev *pcidev))
{
	return(pci_find_device(vendor,device,pcidev));
}
struct  pci_dev * __saveds ASM LIB_pci_find_class(REG(d0,unsigned long class), REG(a0,struct pci_dev *pcidev))
{
	return(pci_find_class(class,pcidev));
}
struct  pci_dev * __saveds ASM LIB_pci_find_slot(REG(d0,unsigned char bus), REG(d1,unsigned long devfn))
{
	return(pci_find_slot(bus,devfn));
}

/* Pci Bus Read/Write Config functions */
unsigned char __saveds ASM LIB_pci_read_config_byte(REG(d0,unsigned char registernum),REG(a0,struct  pci_dev *pcidev))
{
	return( (*pci_read_config_byte)(registernum,pcidev));	
}
unsigned short __saveds ASM LIB_pci_read_config_word(REG(d0,unsigned char registernum),REG(a0,struct  pci_dev *pcidev))
{
	return( (*pci_read_config_word)(registernum,pcidev));	
}
unsigned long __saveds ASM LIB_pci_read_config_long(REG(d0,unsigned char registernum),REG(a0,struct  pci_dev *pcidev))
{
	return( (*pci_read_config_long)(registernum,pcidev));
}
void __saveds ASM LIB_pci_write_config_byte(REG(d0,unsigned char registernum), REG(d1,unsigned char val), REG(a0,struct pci_dev *pcidev))
{
	(*pci_write_config_byte)(registernum,val,pcidev);
}
void __saveds ASM LIB_pci_write_config_word(REG(d0,unsigned char registernum), REG(d1,unsigned short val), REG(a0,struct pci_dev *pcidev))
{
	(*pci_write_config_word)(registernum,val,pcidev);
}
void __saveds ASM LIB_pci_write_config_long(REG(d0,unsigned char registernum), REG(d1,unsigned long val), REG(a0,struct pci_dev *pcidev))
{
	(*pci_write_config_long)(registernum,val,pcidev);
}

/* Pci Set Bus Master */
BOOL __saveds ASM LIB_pci_set_master(REG(a0,struct pci_dev *pcidev))
{
	return( (*pci_set_master)(pcidev));
}

/* Interrupt functions */
BOOL __saveds ASM LIB_pci_add_intserver(REG(a0,struct Interrupt *PciInterrupt),REG(a1,struct pci_dev *pcidev))
{
	return( (*pci_add_intserver)(PciInterrupt,pcidev));
}

void __saveds ASM LIB_pci_rem_intserver(REG(a0,struct Interrupt *PciInterrupt),REG(a1,struct pci_dev *pcidev))
{
	(*pci_rem_intserver)(PciInterrupt,pcidev);
}

/* Alloc and Free DMA memory for PCI card */
APTR __saveds ASM LIB_pci_allocdma_mem(REG(d0,unsigned long size), REG(d1,unsigned long flags))
{
	return( (*pci_allocdma_mem)(size,flags));
}

void __saveds ASM LIB_pci_freedma_mem(REG(a0,APTR buffer),REG(d0,unsigned long size))
{
	(*pci_freedma_mem)(buffer,size);
}

/* Logic<->Physic Addr conversion */
APTR __saveds ASM LIB_pci_logic_to_physic_addr(REG(a0,APTR PciLogicalAddr),REG(a1,struct pci_dev *pcidev))
{
	return( (*pci_logic_to_physic_addr)(PciLogicalAddr,pcidev));	
}

/*************** New functions ***********************/

APTR __saveds ASM LIB_pci_physic_to_logic_addr(REG(a0,APTR PciPhysicalAddr),REG(a1,struct pci_dev *pcidev))
{
	return( (*pci_physic_to_logic_addr)(PciPhysicalAddr,pcidev));
}

/* Obtain/Release PCI card */

BOOL __saveds ASM LIB_pci_obtain_card(REG(a0,struct pci_dev *pcidev))
{
	return( (*pci_obtain_card)(pcidev));
}

void __saveds ASM LIB_pci_release_card(REG(a0,struct pci_dev *pcidev))
{
	(*pci_release_card)(pcidev);
}

#endif

#endif /* OPENPCIFUNCTABLE_H */
