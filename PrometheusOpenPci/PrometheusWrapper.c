/*
 * $Id: PrometheusWrapper.c,v 1.8 2005/29/04 20:00:00 titan Exp $
 */

#include "/openpcidata.h"
#include "/openpci_protosWrapper.h"
#include "PrometheusWrapper.h"

struct Library	*PrometheusBase = NULL;

BOOL PROMETHEUSWrapper(void)
{
	pci_inb=PROMETHEUSpci_inb;
	pci_outb=PROMETHEUSpci_outb;
	pci_inw=PROMETHEUSpci_inw;
	pci_outw=PROMETHEUSpci_outw;
	pci_inl=PROMETHEUSpci_inl;
	pci_outl=PROMETHEUSpci_outl;
		
	pci_to_hostcpy=PROMETHEUSpci_to_hostcpy;
	host_to_pcicpy=PROMETHEUShost_to_pcicpy;
	pci_to_pcicpy=PROMETHEUSpci_to_pcicpy;

	pci_read_config_byte=PROMETHEUSpci_read_config_byte;
	pci_read_config_word=PROMETHEUSpci_read_config_word;
	pci_read_config_long=PROMETHEUSpci_read_config_long;
	pci_write_config_byte=PROMETHEUSpci_write_config_byte;
	pci_write_config_word=PROMETHEUSpci_write_config_word;
	pci_write_config_long=PROMETHEUSpci_write_config_long;
	
	pci_set_master=PROMETHEUSpci_set_master;
	
	pci_add_intserver=PROMETHEUSpci_add_intserver;
	pci_rem_intserver=PROMETHEUSpci_rem_intserver;
	
	pci_allocdma_mem=PROMETHEUSpci_allocdma_mem;
	pci_freedma_mem=PROMETHEUSpci_freedma_mem;
	
	pci_logic_to_physic_addr=PROMETHEUSpci_logic_to_physic_addr;
	pci_physic_to_logic_addr=PROMETHEUSpci_physic_to_logic_addr;

	pci_obtain_card=PROMETHEUSpci_obtain_card;
	pci_release_card=PROMETHEUSpci_release_card;


	return TRUE;
}

void PROMETHEUSclose(void)
{

}

/* We Fill the pci_dev structure */
void PROMETHEUSpcidev(void)
{

 int i,j;

 unsigned char devfunc;
 unsigned char slotnum;
 unsigned char funcnum;

 unsigned long prm_funcnum,prm_slotnum,prm_vendor,prm_device;

 unsigned short oldvalue,value;
 
 /* PROMETHEUS */
 APTR board = NULL;

 unsigned long memaddr;
 unsigned long memsize;
 unsigned long memattr;

 struct pci_dev *pred;

 OpenPciBase->pcidev=(struct pci_dev *)AllocVec(sizeof(struct pci_dev),0L);
 DEBUG(dprintf("Alloc PciDev 0x%08lx\n",OpenPciBase->pcidev));

 OpenPciBase->pcidev->reserved=(struct OpenPciRes *)AllocVec(sizeof(struct OpenPciRes),0L);
 DEBUG(dprintf("Alloc PciDev reserved 0x%08lx\n",OpenPciBase->pcidev->reserved));
 
 OpenPciBase->root=OpenPciBase->pcidev;
 DEBUG(dprintf("OpenPciBase->root = 0x%08lx\n",OpenPciBase->root));

 OpenPciBase->pcidev->device=0;
 OpenPciBase->pcidev->bus=NULL;
 OpenPciBase->pcidev->next=NULL;
 OpenPciBase->pcidev->pred=NULL;   
 
 i=0;


    while (board = Prm_FindBoardTags (board, TAG_END))
    {
      	   		 
				if(board)
				{
					if(i)
					{
						OpenPciBase->pcidev->next=(struct pci_dev *)AllocVec(sizeof(struct pci_dev),0L);
						DEBUG(dprintf("Alloc PciDev next 0x%08lx\n",OpenPciBase->pcidev->next));
						OpenPciBase->pcidev->next->reserved=(struct OpenPciRes *)AllocVec(sizeof(struct OpenPciRes),0L);
						DEBUG(dprintf("Alloc PciDev next reserved 0x%08lx\n",OpenPciBase->pcidev->next->reserved));
						pred=OpenPciBase->pcidev;
						OpenPciBase->pcidev=OpenPciBase->pcidev->next;
						OpenPciBase->pcidev->pred=pred;
						OpenPciBase->pcidev->bus=NULL;
						OpenPciBase->pcidev->next=NULL;
					}
					
					i=1;
					
			      Prm_GetBoardAttrsTags(board,
			       PRM_Vendor, (ULONG)&prm_vendor,
			       PRM_Device, (ULONG)&prm_device,
			       PRM_SlotNumber, (ULONG)&prm_slotnum,
			       PRM_FunctionNumber, (ULONG)&prm_funcnum,      
			       TAG_END);

					OpenPciBase->pcidev->vendor=(unsigned short)prm_vendor;
					OpenPciBase->pcidev->device=(unsigned short)prm_device;
		         
		         // PCI_CLASS_REVISION
					OpenPciBase->pcidev->devclass=Prm_ReadConfigLong(board,PCI_CLASS_REVISION);
					OpenPciBase->pcidev->devclass>>=8;
		         
					slotnum=(unsigned char)prm_slotnum;
					funcnum=(unsigned char)prm_funcnum;		
					
					devfunc=PCI_DEVFN(slotnum,funcnum);
					
					DEBUG(dprintf("Dev %ld Func %ld DevFunc %ld\n",slotnum,funcnum,devfunc));
					
					// DEVFN
					OpenPciBase->pcidev->devfn=devfunc;

				/* OpenPci reserved fields */

					// PCI card unlocked at start
					OpenPciBase->pcidev->reserved->pci_cardlocked=FALSE;

					// PCI card unique name with Vendor, Device, Devfn
					sprintf(OpenPciBase->pcidev->reserved->pci_cardname,"OpenPCI-%04lx-%04lx-%02lx\0",OpenPciBase->pcidev->vendor,OpenPciBase->pcidev->device,OpenPciBase->pcidev->devfn);

					// Private Board Pointer
					OpenPciBase->pcidev->reserved->board=board;


	          	/* Is Master capable */

					/* Read Bus Mastering */
					oldvalue=Prm_ReadConfigWord(board, PCI_COMMAND );
					
					/* Is the Bus Master Activated ? */
					
	  				if(oldvalue&PCI_COMMAND_MASTER)
	  				{
						OpenPciBase->pcidev->master=1;
					}else
					{
						/*
						value=oldvalue;

						// We Activate BUS MASTERING
						value|=PCI_COMMAND_MASTER;
						Prm_WriteConfigWord(board, value, ((PCI_COMMAND^1)<<1) );

						// Verify if Bus Master capable
						// Read Bus Mastering
					if(Prm_ReadConfigWord(board, PCI_COMMAND ) & PCI_COMMAND_MASTER)
						{
							OpenPciBase->pcidev->master=1;
						}else
							OpenPciBase->pcidev->master=0;
						
						// Restore oldvalue 
						Prm_WriteConfigWord(board, oldvalue, ((PCI_COMMAND^1)<<1) );
						*/
						OpenPciBase->pcidev->master=0;
					}					
					
					/* hdr_type */
					OpenPciBase->pcidev->hdr_type=0;
						
					/* IRQ num */
					OpenPciBase->pcidev->irq=Prm_ReadConfigByte(board, PCI_INTERRUPT_LINE );

          		/* 
             		For BaseAddress0 to BaseAddress5
          		*/          
                for (j = 0; j <= 5; j++)
			       {
			        Prm_GetBoardAttrsTags (board,
			         PRM_MemoryAddr0 + j, (ULONG)&memaddr,
			         PRM_MemorySize0 + j, (ULONG)&memsize,
			         TAG_END);
						memattr=Prm_ReadConfigLong( board,(PCI_BASE_ADDRESS_0+(j*4)) );	
						DEBUG(dprintf("memattr(%ld) 0x%08lx\n",(ULONG)j, memattr));
						memsize-=1;
			        	if (memaddr)
			        	{
              			OpenPciBase->pcidev->base_address[j]=memaddr;
              			/* IO Addr Bit0 at 1 */
              			if(memattr&1)
              			{
              				OpenPciBase->pcidev->base_size[j]=~(memsize&PCI_BASE_ADDRESS_IO_MASK)|1;

              			}else
              			{
              				/* Mem Addr */
								OpenPciBase->pcidev->base_size[j]=~(memsize&PCI_BASE_ADDRESS_MEM_MASK)&PCI_BASE_ADDRESS_MEM_MASK;
              			}

              		}else
              		{
              			OpenPciBase->pcidev->base_address[j]=NULL;
              			OpenPciBase->pcidev->base_size[j]=NULL;
              		}
			       }
                      	
            	/* RomAddress */
            	Prm_GetBoardAttrsTags(board,
			        PRM_ROM_Address, (ULONG)&memaddr,
			        PRM_ROM_Size, (ULONG)&memsize,
			        TAG_END);

					memsize-=1;
            	if(memaddr && memsize)
            	{
            		OpenPciBase->pcidev->rom_address=memaddr;
            		OpenPciBase->pcidev->rom_size=~(memsize&PCI_ROM_ADDRESS_MASK)&PCI_ROM_ADDRESS_MASK;
            	}else
            	{
            		OpenPciBase->pcidev->rom_address=NULL;
            		OpenPciBase->pcidev->rom_size=NULL;
            	}
            }  		
		 }

}

