/*
 * $Id: pci_obtainrelease_card.c,v 1.1.1.1 2002/05/09 13:36:00 titan Exp $
 */

#include "openpcidata.h"

/* Obtain/Release PCI card */
BOOL (*pci_obtain_card)(struct pci_dev *pcidev);
void (*pci_release_card)(struct pci_dev *pcidev);

