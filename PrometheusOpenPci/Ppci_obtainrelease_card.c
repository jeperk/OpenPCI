/*
 * $Id: Ppci_obtainrelease_card.c,v 1.2 2005/03/19 11:53:00 titan Exp $
 */

#ifdef __GNUC__
#include "../openpcidata.h"
#else
#include "/openpcidata.h"
#endif

#include "PrometheusWrapper.h"

/* Obtain/Release PCI card */

/* For Prometheus there's no Unlock mechanism !! */
BOOL PROMETHEUSpci_obtain_card(struct pci_dev *pcidev)
{
	if (Prm_SetBoardAttrsTags(pcidev->reserved->board,
			 PRM_BoardOwner, (LONG)OpenPciBase,
			 TAG_END))
	{
		pcidev->reserved->pci_cardlocked=TRUE;
		// proceed with the hardware
		return(TRUE);
	}
	else
	{
		pcidev->reserved->pci_cardlocked=FALSE;
		// somebody already claimed the hadrware
		return(FALSE);
	}

}

void PROMETHEUSpci_release_card(struct pci_dev *pcidev)
{
	Prm_SetBoardAttrsTags(pcidev->reserved->board,
		 PRM_BoardOwner, (LONG)NULL,
		 TAG_END);
	pcidev->reserved->pci_cardlocked=FALSE; /* We release the PCI card */
}

