/*
 * $Id: Ppci_set_master.c,v 1.4 2005/19/03 12:10:00 titan Exp $
 */

#include "/openpcidata.h"
#include "PrometheusWrapper.h"

BOOL PROMETHEUSpci_set_master(struct  pci_dev *dev)
{
	unsigned short value;

	if(dev->master)
	{
		// Read Bus Master
		value=Prm_ReadConfigWord(dev->reserved->board, PCI_COMMAND );
		DEBUG(dprintf("Prm_ReadConfigWord : 0x%04lx\n",value));
		// We Activate BUS MASTERING
		value|=PCI_COMMAND_MASTER;
		DEBUG(dprintf("Prm_WriteConfigWord(0x%08lx,0x%lx,0x%lx)\n",dev->reserved->board, value, PCI_COMMAND ));
		Prm_WriteConfigWord(dev->reserved->board, value, PCI_COMMAND);

		// Verify if Bus Master capable
		value=Prm_ReadConfigWord(dev->reserved->board, PCI_COMMAND);
		
		DEBUG(dprintf("Prm_ReadConfigWord : 0x%04lx\n",value));
		if(value&PCI_COMMAND_MASTER)	
		{
			return TRUE;
		}else
			return FALSE;
	}else
		return FALSE;

}

