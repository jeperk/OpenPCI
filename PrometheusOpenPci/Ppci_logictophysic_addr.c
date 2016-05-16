/*
 * $Id: Ppci_logictophysic_addr.c,v 1.1.1.1 2005/03/19 12:11:00 titan Exp $
 */

#include "/openpcidata.h"
#include "PrometheusWrapper.h"

/* Convert Logical to Physical PCI Memory Address */
APTR PROMETHEUSpci_logic_to_physic_addr(APTR PciLogicalAddr, struct pci_dev *pcidev)
{
	if(pcidev)
	{
		return(Prm_GetPhysicalAddress(PciLogicalAddr));
	}
	else
		return NULL;
}

APTR PROMETHEUSpci_physic_to_logic_addr(APTR PciPhysicalAddr, struct pci_dev *pcidev)
{
	if(pcidev)
	{
		return(Prm_GetVirtualAddress(PciPhysicalAddr)); /* Not supported for the moment */
	}
	else
		return NULL;
}
