/*
 * $Id: openpcifunctable.c,v 1.1.1.1 2002/05/09 13:35:52 titan Exp $
 */

#include "openpcidata.h"
#include "openpcifunctable.h"

void	LIB_Open(void);
void	LIB_Close(void);
void	LIB_Expunge(void);
void	LIB_Reserved(void);


/*
	LibFuncTable == LibVectors
	6 bytes between each function
*/

ULONG	LibFuncTable[]=
{
#ifdef __MORPHOS__
	FUNCARRAY_32BIT_NATIVE,
#endif
	(ULONG) &LIB_Open,
	(ULONG) &LIB_Close,
	(ULONG) &LIB_Expunge,
	(ULONG) &LIB_Reserved,

	(ULONG) &LIB_pci_bus,
	(ULONG) &LIB_pci_inb,
	(ULONG) &LIB_pci_outb,
	(ULONG) &LIB_pci_inw,
	(ULONG) &LIB_pci_outw,
	(ULONG) &LIB_pci_inl,
	(ULONG) &LIB_pci_outl,	
	(ULONG) &LIB_pci_to_hostcpy,
	(ULONG) &LIB_host_to_pcicpy,
	(ULONG) &LIB_pci_to_pcicpy,	
	(ULONG) &LIB_pci_find_device,
	(ULONG) &LIB_pci_find_class,
	(ULONG) &LIB_pci_find_slot,
	(ULONG) &LIB_pci_read_config_byte,
	(ULONG) &LIB_pci_read_config_word,
	(ULONG) &LIB_pci_read_config_long,
	(ULONG) &LIB_pci_write_config_byte,
	(ULONG) &LIB_pci_write_config_word,
	(ULONG) &LIB_pci_write_config_long,
	(ULONG) &LIB_pci_set_master,
	(ULONG) &LIB_pci_add_intserver,
	(ULONG) &LIB_pci_rem_intserver,
	(ULONG) &LIB_pci_allocdma_mem,
	(ULONG) &LIB_pci_freedma_mem,
	(ULONG) &LIB_pci_logic_to_physic_addr,
	(ULONG) &LIB_pci_physic_to_logic_addr,
	(ULONG) &LIB_pci_obtain_card,
	(ULONG) &LIB_pci_release_card,
	0xffffffff
};


