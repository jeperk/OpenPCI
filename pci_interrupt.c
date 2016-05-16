/*
 * $Id: pci_interrupt.c,v 1.1.1.1 2002/05/09 13:35:56 titan Exp $
 */

#include "openpcidata.h"

/*
	Add interrupt server
*/
BOOL (*pci_add_intserver)(struct Interrupt *PciInterrupt, struct pci_dev *pcidev);

void (*pci_set_int)(struct pci_dev *pcidev);

void (*pci_clear_int)(struct pci_dev *pcidev);

void (*pci_rem_intserver)(struct Interrupt *PciInterrupt, struct pci_dev *pcidev);

