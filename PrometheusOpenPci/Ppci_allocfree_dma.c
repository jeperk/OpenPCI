/*
 * $Id: Ppci_allocfree_dma.c,v 1.1.1.1 2002/05/09 13:36:45 titan Exp $
 */

#include "/openpcidata.h"
#include "PrometheusWrapper.h"

/* Alloc and Free DMA memory for PCI card */
APTR PROMETHEUSpci_allocdma_mem(unsigned long size, unsigned long flags)
{
	return(Prm_AllocDMABuffer(size));
}

void PROMETHEUSpci_freedma_mem(APTR buffer, unsigned long size)
{
	Prm_FreeDMABuffer(buffer, size);
}

