/*
 * $Id: Ppci_in_out.c,v 1.2 2002/07/06 18:25:05 titan Exp $
 */

#include "openpcidata.h"
#include "PrometheusWrapper.h"

#ifdef __GNUC__
#include "../InOut.h"
#else
#include "InOut.h"
#endif

/* IN/OUT Function for PCI Bus */

unsigned char PROMETHEUSpci_inb(unsigned long address)
{
	return(hinb(address));
}
void PROMETHEUSpci_outb(unsigned char value, unsigned long address)
{
	houtb(value,address);
}

unsigned short PROMETHEUSpci_inw(unsigned long address)
{
	return(hinw(address));
}
void PROMETHEUSpci_outw(unsigned short value, unsigned long address)
{
	houtw(value,address);
}

unsigned long PROMETHEUSpci_inl(unsigned long address)
{
	return(hinl(address));
}

void PROMETHEUSpci_outl(unsigned long value, unsigned long address)
{
	houtl(value,address);
}

/* Write Pci memory -> Amiga memory  */
void PROMETHEUSpci_to_hostcpy(void *pcimemsource, void *memdest, unsigned long packetsize)
{
	memcpyl(pcimemsource,memdest,packetsize);	
}

/* Write Amiga memory -> Pci memory  */
void PROMETHEUShost_to_pcicpy(void *memsrc, void *pcimemdest, unsigned long packetsize)
{
	memcpyl(memsrc,pcimemdest,packetsize);	
}

/* Write Pci memory -> Pci memory  */
void PROMETHEUSpci_to_pcicpy(void *pcimemsrc, void *pcimemdest, unsigned long packetsize)
{
	memcpyl(pcimemsrc,pcimemdest,packetsize);	
}

