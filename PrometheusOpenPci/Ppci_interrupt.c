/*
 * $Id: Ppci_interrupt.c,v 1.1.1.1 2002/05/09 13:36:42 titan Exp $
 */

#include "/openpcidata.h"
#include "PrometheusWrapper.h"

/*
	Add interrupt server
*/
BOOL PROMETHEUSpci_add_intserver(struct Interrupt *PciInterrupt, struct pci_dev *pcidev)
{
	return(Prm_AddIntServer(pcidev->reserved->board,PciInterrupt));
}

void PROMETHEUSpci_rem_intserver(struct Interrupt *PciInterrupt, struct pci_dev *pcidev)
{
	Prm_RemIntServer(pcidev->reserved->board,PciInterrupt);
}

