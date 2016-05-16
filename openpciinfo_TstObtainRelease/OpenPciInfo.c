/*
   OpenPciInfo v1.5 TST Obtain/Release coded by Titan Email : bvernoux@wanadoo.fr
   22/05/2005
   - Obtain/Release test code.
   12/03/2005
   - New Pci card header (This header created on Sun Mar  6 09:38:14 PST 2005)
   - New tests
   - Cleaned warning
   26/07/2002
   - Correct an Error in what's enable in the card for the FAST_BACK_TO_BACK
   12/07/2002
   - Add Makefile for GCC MOS and modified some things for GCC MOS
   21/02/2002
   - Modified ClassCode with 0x%06lx
   17/02/2002
   Modified 10/04/2002
   - Added lot of information for developer on each card on the Bus
   26/03/2002
   - use new flags for pci_allocdma_mem
   10/04/2002
   - Support GrexA1200Bus, GrexA4000Bus and PegasosBus flags
   12/04/2002
   - Modify strncpy to stccpy for speed-up Thanks to Zapek
*/

#include <proto/dos.h>
#include <exec/types.h>
#include <exec/memory.h>
#include <libraries/dos.h>
#include <libraries/configvars.h>

#include <clib/exec_protos.h>
#include <clib/expansion_protos.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <proto/openpci.h>
#include <libraries/openpci.h>

#include "PCIBusInfo.h"

#ifdef LATTICE
//int CXBRK(void) { return(0); }  /* Disable Lattice CTRL/C handling */
//int chkabort(void) { return(0); }  /* really */
#endif

struct Library *ExpansionBase = NULL;
struct Library *OpenPciBase = NULL;

void TestObtainRelease(struct pci_dev *dev)
{
	BOOL result;
	printf("\nTestObtainRelease\n");

/* 
	Test1
*/
	result=pci_obtain_card(dev);
	printf("pci_obtain_card(0x%08lx)==%ld\n",dev,result);
	if(result==TRUE)
	{
		pci_release_card(dev);
		printf("pci_release_card(0x%08lx)\n",dev);
	}else
		printf("Error to obtain card\n");

/*
	Test2
*/		
	result=pci_obtain_card(dev);
	printf("pci_obtain_card(0x%08lx)==%ld\n",dev,result);
	if(result==TRUE)
	{
		pci_release_card(dev);
		printf("pci_release_card(0x%08lx)\n",dev);
	}else
		printf("Error to obtain card\n");
}

int main(int argc, char **argv)
{

 unsigned char bus=0;
 int j;

 unsigned char slotnum;
 unsigned char funcnum;
 // IRQ
 unsigned short irq;
 
 unsigned short vendorid,deviceid;
 
 unsigned long config;
 unsigned long memstart;
 unsigned long memend;
 unsigned long memflags;
 unsigned char mem;
  
 char VendorShort[100];
 char VendorFull[100];
 char DevName[100];
 char DevNameDesc[100];
 
 unsigned long dmamem,dmamem1;
 
 	struct pci_dev *dev=NULL;
 
 	// Version Number
 	printf("%s\n\n",&ver[6]);
 
 
	if(( OpenPciBase=(struct Library *)OpenLibrary("openpci.library",MIN_OPENPCI_VERSION))==NULL)
	{
		printf("Error to open openpci.library v%ld or more\n",(long)MIN_OPENPCI_VERSION);
   		return 10;
	}

	printf("openpci.library v%ld.%ld opened\n",(long)OpenPciBase->lib_Version,(long)OpenPciBase->lib_Revision);

	bus=pci_bus();
	if(bus>0)
	{  
		switch(bus)
		{
			case MediatorA1200Bus:
				printf("Bus Mediator A1200 detected\n");
				break;
			case MediatorZ4Bus:
				printf("Bus Mediator Z4 detected\n");
				break;
			case PrometheusBus:
				printf("Bus Prometheus detected\n");
				break;
			case GrexA1200Bus:
				printf("Bus Grex A1200 detected\n");
				break;
			case GrexA4000Bus:
				printf("Bus Grex A4000 detected\n");
				break;
			case PegasosBus:
				printf("Bus Pegasos detected\n");
				break;
			case PowerPciBus:		
				printf("Amithlon PCI Bus detected\n");
				break;
			default:
				printf("PCI Bus not detected\n");
		}   		
	}		
		
 if(bus)
 {		    	    
	while( (dev=pci_find_device(0xffff,0xffff,dev))!=NULL )
	{
	   printf("\n----------------------------------\n");
	   printf("Internal Configuration Space infos\n");

	   vendorid=pci_read_config_word(PCI_VENDOR_ID,dev);
	   deviceid=pci_read_config_word(PCI_DEVICE_ID,dev);
	   printf("VendorID : $%x \nDeviceID : $%x\n",vendorid,deviceid);
	
           config=pci_read_config_long(PCI_CLASS_REVISION,dev);
	   printf("ClassRevision : $%08lx \n",config);

           config=(long)pci_read_config_byte(PCI_REVISION_ID,dev);
	   printf("PCI_REVISION_ID $%02lx\n",config);

           config=(long)pci_read_config_byte(PCI_HEADER_TYPE,dev);
           printf("Header Type : $%02lx (0=Normal/1=Bridge/2=Cardbus)\n",config);
           if (config==0)
           {
	   	config=(long)pci_read_config_word(PCI_SUBSYSTEM_ID,dev);
	   	printf("PCI_SUBSYSTEM_ID $%04lx\n",config);
           }

	   config=(long)pci_read_config_word(PCI_COMMAND,dev);
	   printf("Command : $%04lx \n",config);

		if(config&PCI_COMMAND_IO)
			printf("I/O space PCI_COMMAND_IO\n");

		if(config&PCI_COMMAND_MEMORY)
			printf("Memory space PCI_COMMAND_MEMORY\n");

		if(config&PCI_COMMAND_MASTER)
			printf("Bus mastering PCI_COMMAND_MASTER\n");

		if(config&PCI_COMMAND_SPECIAL)
			printf("Special cycles PCI_COMMAND_SPECIAL\n");

		if(config&PCI_COMMAND_INVALIDATE)
			printf("Use memory write and invalidate PCI_COMMAND_INVALIDATE\n");

		if(config&PCI_COMMAND_VGA_PALETTE)
			printf("Palette snooping PCI_COMMAND_VGA_PALETTE\n");

		if(config&PCI_COMMAND_PARITY)
			printf("Parity checking PCI_COMMAND_PARITY\n");

		if(config&PCI_COMMAND_WAIT)
			printf("Address/data stepping PCI_COMMAND_WAIT\n");

		if(config&PCI_COMMAND_SERR)
			printf("SERR PCI_COMMAND_SERR\n");

		if(config&PCI_COMMAND_FAST_BACK)
			printf("Fast-back to back writes PCI_COMMAND_FAST_BACK\n");

	/*
	if(pci_set_master(dev))
	{

		printf("Bus MASTER Enable\n");
   	}else
   	{
   		printf("I can't Enable Bus MASTER on this card\n");
   	}
   	*/
   	config=(long)pci_read_config_byte(PCI_LATENCY_TIMER,dev);
	printf("PCI_LATENCY_TIMER : $%02lx\n",config);
	config=pci_read_config_long(0x34,dev);
	config=config&0x000000FF;
	printf("CAP Ptr : $%08lx\n",config);	
	if(config>0)
	{
		config=pci_read_config_long( (unsigned char)config,dev);
		printf("CAP Ptr1 Val : $%08lx\n",config);		
	}
	printf("----------------------------------\n");
	/* End of internal Configuration Space infos */

		TestObtainRelease(dev);

  	// Get The Pci Slot Number (5 device max on a PCI BUS (4 on Mediator1200))
	   slotnum=PCI_SLOT(dev->devfn);
			
	// Get The Pci Function Number (8 function max on each PCI device)
	   funcnum=PCI_FUNC(dev->devfn);
	   	   
	   printf("Pci Device Slot Num : %d, Func Num : %d \n",slotnum,funcnum);
	            
	   // Vendor ID
	   vendorid=dev->vendor;
	   // Device ID
	   deviceid=dev->device;	      
		VendorName(vendorid,VendorShort,VendorFull);
	   DeviceName(vendorid,deviceid,DevName,DevNameDesc);
				
	   printf("Vendor   : %s \nDevice   : %s %s\nVendorID : $%x \nDeviceID : $%x\n",VendorFull,DevName,DevNameDesc,vendorid,deviceid); 
	   printf("ClassCode: 0x%06lx\n",(long)dev->devclass);

	  // IRQ
	   irq=dev->irq;
	   printf("IRQNumber: %d\n",irq);
    
      /* 
       	For BaseAddress0 to BaseAddress5
      */ 
      mem=0;
      for(j=0;j<=5;j++)
      {  
         	       	
         memstart=dev->base_address[j];
         memflags=dev->base_size[j];

         if(memstart) 
         {            	          	
           	if(memflags&1) //IOAddress Bit0 at 1
           	{
            // IOAddr
            		memend=memstart+~(dev->base_size[j]&PCI_BASE_ADDRESS_IO_MASK);
               
             		// Diplay in bytes or kbytes
              		if(memend-memstart+1<=1024)
              		{
              			printf("IOAddr%d  : $%08lx - $%08lx %ld bytes\n",
              			j,
              			memstart,
	      				memend,
              			(unsigned long)(memend-memstart+1) );	

              		}else
              		{
 			    			printf("IOAddr%d  : $%08lx - $%08lx %ld kbytes\n",
              			j,
              			memstart,
	      				memend,
              			(unsigned long)(memend-memstart+1)>>10 );	
              		}
        		}else
            {
            // Mem Address	
            		memend=memstart+~(dev->base_size[j]&PCI_BASE_ADDRESS_MEM_MASK);
            
              		// Diplay in bytes or kbytes
              		if(memend-memstart+1<=1024)
              		{
              			printf("MemAddr%d : $%08lx - $%08lx %ld bytes\n",
              			j,
              			memstart,
              			memend,
              			(unsigned long)(memend-memstart+1) );
              		}else
              		{
							printf("MemAddr%d : $%08lx - $%08lx %ld kbytes\n",
              			j,
              			memstart,
              			memend,
              			(unsigned long)(memend-memstart+1)>>10 );
              		}
           	 	
           	}	
            	              
           		
         }  
          	  
		}			
      if(dev->rom_address && dev->rom_size)
	     	printf(
	     			"RomAddr  : $%08lx - $%08lx\nRomSize\t : %ld bytes %ld kbytes\n",
	     			dev->rom_address,
	        		dev->rom_address+~(dev->rom_size&PCI_ROM_ADDRESS_MASK),
	        		(unsigned long)(~(dev->rom_size&PCI_ROM_ADDRESS_MASK)+1),
	        		(~(dev->rom_size&PCI_ROM_ADDRESS_MASK)+1)/1024
	      );

	   if(dev->master)
	   	printf("Bus Master Capable\n");
	   else
	   {
	   	printf("No Bus Master Capable\n");
	   }

		// Support 66Mhz
		
		// Read PCI_STATUS
		config=pci_read_config_word(PCI_STATUS,dev);
		
		printf("Card PCI_STATUS\n");		
		//printf("Config PCI_STATUS 0x%x\n",config);

		if(config&PCI_STATUS_66MHZ)
			printf("Support 66 Mhz PCI 2.1 bus\n");
		else
		{
			printf("Doesn't support 66 Mhz PCI 2.1 bus\n");	
		}
		
		if(config&PCI_STATUS_FAST_BACK)
			printf("Accept fast-back to back\n");
		else
		{
			printf("Doesn't accept fast-back to back\n");	
		}
		
		// Read PCI_COMMAND
		config=pci_read_config_word(PCI_COMMAND,dev);
		printf("What's Enabled in the Card ?\n");		

		if(config&PCI_COMMAND_IO)
			printf("I/O space PCI_COMMAND_IO\n");
	
		if(config&PCI_COMMAND_MEMORY)
			printf("Memory space PCI_COMMAND_MEMORY\n");
			
		if(config&PCI_COMMAND_MASTER)
			printf("Bus mastering PCI_COMMAND_MASTER\n");

		if(config&PCI_COMMAND_SPECIAL)
			printf("Special cycles PCI_COMMAND_SPECIAL\n");

		if(config&PCI_COMMAND_INVALIDATE)
			printf("Use memory write and invalidate PCI_COMMAND_INVALIDATE\n");

		if(config&PCI_COMMAND_VGA_PALETTE)
			printf("Palette snooping PCI_COMMAND_VGA_PALETTE\n");

		if(config&PCI_COMMAND_PARITY)
			printf("Parity checking PCI_COMMAND_PARITY\n");

		if(config&PCI_COMMAND_WAIT)
			printf("Address/data stepping PCI_COMMAND_WAIT\n");

		if(config&PCI_COMMAND_SERR)
			printf("SERR PCI_COMMAND_SERR\n");

		if(config&PCI_COMMAND_FAST_BACK)
			printf("Fast-back to back writes PCI_COMMAND_FAST_BACK\n");

	   //printf("\n");
	}
	
#if 1
	// Test Lib Functions
	// Find first Pci card
	dev=pci_find_device(0xffff,0xffff,0);
	if(dev)
	{
   		
   		/* DMA Mem Alloc/Free tests */
   		
   		// Alloc DMA Mem
   		dmamem=(unsigned long)pci_allocdma_mem(2048,MEM_PCI);
   		if(dmamem)
			printf("2048bytes MEM_PCI DMA Mem Allocated : %lx\n",dmamem);
			
		// Alloc DMA Mem
   		dmamem1=(unsigned long)pci_allocdma_mem(16384,MEM_PCI);
   		if(dmamem1)
			printf("16384bytes MEM_PCI DMA Mem Allocated : %lx\n",dmamem1);
			
		// Free DMA Mem
		if(dmamem)
		{
			printf("Free Mem 2048\n");
			pci_freedma_mem( (APTR)dmamem,2048);
		}
			
		// Alloc DMA Mem
   		dmamem=(unsigned long)pci_allocdma_mem(2040,MEM_NONCACHEABLE);
   		if(dmamem)
			printf("2040bytes MEM_NONCACHEABLE DMA Mem Allocated : %lx\n",dmamem);
			
		// Free DMA Mem
		if(dmamem)
		{
			printf("Free Mem 2040\n");
			pci_freedma_mem( (APTR)dmamem,2040);
		}

		// Alloc DMA Mem
   		dmamem=(unsigned long)pci_allocdma_mem(4096,MEM_NONCACHEABLE);
   		if(dmamem)
			printf("4096bytes MEM_NONCACHEABLE DMA Mem Allocated : %lx\n",dmamem);
			
		// Free DMA Mem
		if(dmamem)
		{
			printf("Free Mem 4096\n");
			pci_freedma_mem( (APTR)dmamem,4096);			
		}			   		
			
		// Free DMA Mem
		if(dmamem1)
		{
			printf("Free Mem 16384\n");
			pci_freedma_mem( (APTR)dmamem1,16384);	
		}


		// Maximum DMA Mem is 262144 bytes
   		// Alloc DMA Mem
   		dmamem=(unsigned long)pci_allocdma_mem(300000,MEM_NONCACHEABLE);
   		if(dmamem)
			printf("300000 bytes MEM_NONCACHEABLE DMA Mem Allocated : %lx\n",dmamem);			
			
		// Free DMA Mem
		if(dmamem)
		{
			printf("Free Mem 300000\n");
			pci_freedma_mem( (APTR)dmamem,300000);
		}
								
	}
#endif
	
 }
 CloseLibrary( (struct Library*)OpenPciBase ); 
 return 0;
}


/*
  For know the VendorName Short and Full description
  return -1 if success or 0 if it's  not founded
*/

int VendorName(unsigned short VendID,char *VendorShort,char *VendorFull)
{
  int i;
  for(i=0;i<PCI_VENTABLE_LEN;i++)
  {
    if(PciVenTable[i].VenId==VendID)
    { 
#ifdef __SASC 
     stccpy(VendorShort,PciVenTable[i].VenShort,100);
     stccpy(VendorFull,PciVenTable[i].VenFull,100);
#else
     strncpy(VendorShort,PciVenTable[i].VenShort,100);
     strncpy(VendorFull,PciVenTable[i].VenFull,100);
#endif
     return -1;
    }
  }
  VendorShort[0]=0;
  VendorFull[0]=0;
  return 0;
}


/*
  For know the DeviceName and it's full description
  return -1 if success or 0 if it's  not founded
*/

int DeviceName(unsigned short VendID,unsigned short DevID,char *DevName,char *DevNameDesc)
{
  int i;
  for(i=0;i<PCI_DEVTABLE_LEN;i++)
  {
    if( PciDevTable[i].VenId==VendID && PciDevTable[i].DevId==DevID)
    { 
#ifdef __SASC    
     stccpy(DevName,PciDevTable[i].Chip,100);
     stccpy(DevNameDesc,PciDevTable[i].ChipDesc,100);
#else
     strncpy(DevName,PciDevTable[i].Chip,100);
     strncpy(DevNameDesc,PciDevTable[i].ChipDesc,100);
#endif
     return -1;
    }
  }
  DevName[0]=0;
  DevNameDesc[0]=0;
  return 0;
}

