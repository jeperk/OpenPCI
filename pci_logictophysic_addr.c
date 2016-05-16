/*
 * $Id: pci_logictophysic_addr.c,v 1.1.1.1 2002/05/09 13:36:00 titan Exp $
 */

#include "openpcidata.h"

/* Logic<->Physic Addr conversion */
APTR (*pci_logic_to_physic_addr)(APTR PciLogicalAddr, struct pci_dev *pcidev);
APTR (*pci_physic_to_logic_addr)(APTR PciPhysicalAddr, struct pci_dev *pcidev);

