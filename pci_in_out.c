/*
 * $Id: pci_in_out.c,v 1.1.1.1 2002/05/09 13:35:56 titan Exp $
 */

#include "openpcidata.h"

/* IN/OUT Function for PCI Bus */
/* Byte (8bits) Read/Write */
unsigned char (*pci_inb)(unsigned long address);
void (*pci_outb)(unsigned char value, unsigned long address);

/* Word (16bits) Read/Write */
unsigned short (*pci_inw)(unsigned long address);
void (*pci_outw)(unsigned short value, unsigned long address);

/* Long (32bits) Read/Write  */
unsigned long (*pci_inl)(unsigned long address);
void (*pci_outl)(unsigned long value, unsigned long address);

/* Amiga Mem and Pci Mem Read/Write (must be a multiple of 16bytes) (it's a very fast mem bloc copy) */
void (*pci_to_hostcpy)(void *pcimemsource, void *memdest, unsigned long packetsize);
void (*host_to_pcicpy)(void *memsrc, void *pcimemdest, unsigned long packetsize);
void (*pci_to_pcicpy)(void *pcimemsrc, void *pcimemdest, unsigned long packetsize);




