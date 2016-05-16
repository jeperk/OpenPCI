/*
 * $Id: Ppci_readwrite_config.c,v 1.1.1.1 2005/03/19 11:43:00 titan Exp $
 */

#include "/openpcidata.h"
#include "PrometheusWrapper.h"

/* Read Config */
unsigned char PROMETHEUSpci_read_config_byte(unsigned char registernum, struct  pci_dev *dev)
{
	return( Prm_ReadConfigByte(dev->reserved->board, registernum) );
}

unsigned short PROMETHEUSpci_read_config_word(unsigned char registernum, struct  pci_dev *dev)
{
	return( Prm_ReadConfigWord(dev->reserved->board, registernum) );
}

unsigned long PROMETHEUSpci_read_config_long(unsigned char registernum, struct  pci_dev *dev)
{
	return( Prm_ReadConfigLong(dev->reserved->board, registernum) );
}

/* Write Config */

void PROMETHEUSpci_write_config_byte(unsigned char registernum, unsigned char val, struct  pci_dev *dev)
{
	Prm_WriteConfigByte(dev->reserved->board, val, registernum );
}

void PROMETHEUSpci_write_config_word(unsigned char registernum, unsigned short val, struct  pci_dev *dev)
{
	Prm_WriteConfigWord(dev->reserved->board, val, registernum );
}

void PROMETHEUSpci_write_config_long(unsigned char registernum, unsigned long val, struct  pci_dev *dev)
{
	Prm_WriteConfigLong(dev->reserved->board, val, registernum );
}
