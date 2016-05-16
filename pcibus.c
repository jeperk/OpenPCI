/*
 * $Id: pcibus.c,v 1.18 2003/07/28 18:47:27 titan Exp $    
 * pcibus créé le 13/02/2002 par Benjamin Vernoux
*/

#include <stdlib.h>

#include <proto/expansion.h>

#include "openpcidata.h"
#include "pcibus.h"
#include "pci.h"

#ifdef __SASC
#define __PrometheusWrapper__
#else
#undef __PrometheusWrapper__
#endif

/* Prometheus */
#ifdef __PrometheusWrapper__
#warning Prometheus Wrapper Added
#include "PrometheusOpenPci/PrometheusWrapper.h"
#endif

/* Return the bus type found */
unsigned short pci_bus(void)
{
    return(OpenPciBase->bus);    
}

/*
   Detect the PCI BUS
   Return 0 If Error or no bus detected
*/
unsigned short FindPCIBus(void)
{
    unsigned short pcibus=0;
    
#ifdef __PrometheusWrapper__            
    // Prometheus PCI detection V3.0 mini
    if (PrometheusBase = OpenLibrary ("prometheus.library", PROMETHEUSVERSION))
    {
          OpenPciBase->bus|=PrometheusBus;
          return(OpenPciBase->bus);
    }
#endif
   
   // PciBus found
   OpenPciBase->bus=pcibus;
   return(pcibus);
}


/*
    Ouvre la librairie du bon BusPci détecté
    Return 0 (FALSE) en cas d'échec
    Return 1 (TRUE) si ok

*/

BOOL ASM OpenPCIBus(REG(d0,int pcibus))
{
    OpenPciBase->pcidev=NULL;

    if(pcibus>0)
     {
  
          if (pcibus & MediatorA1200Bus) 
            DEBUG(dprintf("Mediator A1200 Bus detected\n"));
          if (pcibus & MediatorZ4Bus)
           DEBUG(dprintf("Mediator Z4 Bus detected\n")); 
         
         if (pcibus & GrexA1200Bus)
           DEBUG(dprintf("GrexA1200 Bus detected\n")); 
           
         if (pcibus & GrexA4000Bus)
           DEBUG(dprintf("GrexA4000 Bus detected\n")); 

        if (pcibus & PegasosBus)
           DEBUG(dprintf("Pegasos Bus detected\n")); 

#ifdef __PrometheusWrapper__                
        /* Prometheus BUS */
        if (pcibus & PrometheusBus)
        {
            /* We wrap the function with the prometheus function */
            if(PROMETHEUSWrapper()==TRUE)
            {
                /* We fill the pci_dev structure */
                PROMETHEUSpcidev();
                return TRUE;
            }else
                return FALSE;    
        }
#endif

    }
    return FALSE;
}

/* Free pci_dev and each specific bus close function */
void FreePciDevStruct(void)
{
    if (OpenPciBase->root==NULL) return;
    
    OpenPciBase->pcidev=OpenPciBase->root; /* We start at first position of the pci_dev device */
    /* We go to the end pci_dev device */
    while(OpenPciBase->pcidev->next)
    {
        OpenPciBase->pcidev=OpenPciBase->pcidev->next;
    }

	/* Free all memory */
    while(OpenPciBase->pcidev->pred)
    {
        OpenPciBase->pcidev=OpenPciBase->pcidev->pred;
		dprintf("Free Dev %08lx Dev Res %08lx\n",OpenPciBase->pcidev->next,OpenPciBase->pcidev->next->reserved);
		FreeVec(OpenPciBase->pcidev->next);
		FreeVec(OpenPciBase->pcidev->next->reserved);
    }
	dprintf("Free Dev %08lx Dev Res %08lx\n",OpenPciBase->pcidev,OpenPciBase->pcidev->reserved);
	FreeVec(OpenPciBase->pcidev);
	FreeVec(OpenPciBase->pcidev->reserved);

#ifdef __PrometheusWrapper__
    /* Prometheus Bus */
    if (OpenPciBase->bus & PrometheusBus)    PROMETHEUSclose();
    
    if(PrometheusBase)
    {    
			DEBUG(dprintf("Close prometheus.library\n"));
			CloseLibrary( (struct Library*)PrometheusBase );
            PrometheusBase=NULL;
    }
#endif
   
}


