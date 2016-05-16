/*
 * $Id: pci_find.c,v 1.2 2003/05/01 16:06:44 titan Exp $
 */

#include "openpcidata.h"

struct  pci_dev *pci_find_device( unsigned short vendor, unsigned short device, struct pci_dev *pcidev)
{
	//DEBUG(dprintf("OpenPciBase->root = 0x%08lx\n",OpenPciBase->root));
	//DEBUG(dprintf("OpenPciBase = 0x%08lx\n",OpenPciBase));

	DEBUG(dprintf("pci_find_device(vendor,device,pcidev) parameters : vendor=0x%04lx device=0x%04lx pcidev=0x%08lx\n",vendor,device,pcidev));

	/* If pcidev=0 then we start at root else we start at next device */	
	if(pcidev==NULL)
	{
		OpenPciBase->pcidev=OpenPciBase->root;
	}else
		OpenPciBase->pcidev=OpenPciBase->pcidev->next;
	
	/* If the vendor and the device is at 0xffff we give the first founded device */
	if(vendor==0xffff && device==0xffff)
		return(OpenPciBase->pcidev);

	while(OpenPciBase->pcidev)
	{			
		DEBUG(dprintf("While pci_find_device : vendor=0x%04lx device=0x%04lx pcidev=0x%08lx\n",OpenPciBase->pcidev->vendor,OpenPciBase->pcidev->device,OpenPciBase->pcidev));

		if(OpenPciBase->pcidev->vendor==vendor && OpenPciBase->pcidev->device==device)
		{
			return(OpenPciBase->pcidev); 
		}
		OpenPciBase->pcidev=OpenPciBase->pcidev->next;
	}
	
	/* No Pci card found */
	return NULL;

}

struct  pci_dev *pci_find_class( unsigned long class,  struct  pci_dev *pcidev)
{
	
	DEBUG(dprintf("pci_find_class(class,pcidev) parameters : class=0x%08lx pcidev=0x%08lx\n",class,pcidev));

	/* If pcidev=0 then we start at root else we start at next device */	
	if(pcidev==NULL)
	{
		OpenPciBase->pcidev=OpenPciBase->root;
	}else
		OpenPciBase->pcidev=OpenPciBase->pcidev->next;

	
	while(OpenPciBase->pcidev)
	{		
		DEBUG(dprintf("While pci_find_class : devclass=0x%04lx pcidev=0x%08lx\n",OpenPciBase->pcidev->devclass,OpenPciBase->pcidev));

		if(OpenPciBase->pcidev->devclass==class)
		{
			return(OpenPciBase->pcidev); 
		}
		OpenPciBase->pcidev=OpenPciBase->pcidev->next;
	}
	
	/* No Pci card found */
	return NULL;

}

struct  pci_dev *pci_find_slot( unsigned char bus,  unsigned long devfn)
{
	/* We start at the root device */
	OpenPciBase->pcidev=OpenPciBase->root;
	
	while(OpenPciBase->pcidev)
	{
		if(OpenPciBase->pcidev->devfn==devfn)
		{
			return(OpenPciBase->pcidev); 
		}
		OpenPciBase->pcidev=OpenPciBase->pcidev->next;
	}
	
	/* No Pci card found */
	return NULL;
}

