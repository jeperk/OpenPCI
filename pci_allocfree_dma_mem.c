/*
 * $Id: pci_allocfree_dma_mem.c,v 1.1.1.1 2002/05/09 13:35:57 titan Exp $
 */

#include "openpcidata.h"

/* Alloc and Free DMA memory for PCI card */
APTR (*pci_allocdma_mem)(unsigned long size, unsigned long flags);

void (*pci_freedma_mem)(APTR buffer,unsigned long size);



