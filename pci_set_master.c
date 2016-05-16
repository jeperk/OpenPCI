/*
 * $Id: pci_set_master.c,v 1.1.1.1 2002/05/09 13:35:56 titan Exp $
 */

#include "openpcidata.h"

BOOL (*pci_set_master)(struct  pci_dev *dev);
