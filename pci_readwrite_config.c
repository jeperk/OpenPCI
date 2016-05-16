/*
 * $Id: pci_readwrite_config.c,v 1.1.1.1 2002/05/09 13:35:56 titan Exp $
 */

#include "openpcidata.h"

/* Read Config */
unsigned char (*pci_read_config_byte)(unsigned char registernum, struct  pci_dev *dev);

unsigned short (*pci_read_config_word)(unsigned char registernum, struct  pci_dev *dev);

unsigned long (*pci_read_config_long)(unsigned char registernum, struct  pci_dev *dev);

/* Write Config */
void (*pci_write_config_byte)(unsigned char registernum, unsigned char val, struct  pci_dev *dev);

void (*pci_write_config_word)(unsigned char registernum, unsigned short val, struct  pci_dev *dev);

void (*pci_write_config_long)(unsigned char registernum, unsigned long val, struct  pci_dev *dev);

