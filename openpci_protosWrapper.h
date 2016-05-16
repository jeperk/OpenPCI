#ifndef  OPENPCI_PROTOSWRAP_H
#define  OPENPCI_PROTOSWRAP_H

#ifndef  EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef  EXEC_INTERRUPTS_H
#include <exec/interrupts.h>
#endif
#ifndef  UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef  DEVICES_TIMER_H
#include <devices/timer.h>
#endif

/* Return the bus type found */
extern unsigned short pci_bus(void);

/* IN/OUT Function for PCI Bus */
/* Byte (8bits) Read/Write */
extern unsigned char (*pci_inb)(unsigned long address);
extern void (*pci_outb)(unsigned char value, unsigned long address);

/* Word (16bits) Read/Write */
extern unsigned short (*pci_inw)(unsigned long address);
extern void (*pci_outw)(unsigned short value, unsigned long address);

/* Long (32bits) Read/Write  */
extern unsigned long (*pci_inl)(unsigned long address);
extern void (*pci_outl)(unsigned long value, unsigned long address);

/* Amiga Mem and Pci Mem Read/Write (must be a multiple of 16bytes) (it's a very fast mem bloc copy) */
extern void (*pci_to_hostcpy)(void *pcimemsrc, void *memdest, unsigned long packetsize);
extern void (*host_to_pcicpy)(void *memsrc, void *pcimemdest, unsigned long packetsize);
extern void (*pci_to_pcicpy)(void *pcimemsrc, void *pcimemdest, unsigned long packetsize);

/* Pci Find Functions */
extern struct  pci_dev *pci_find_device( unsigned short vendor, unsigned short device, struct pci_dev *pcidev);
extern struct  pci_dev *pci_find_class( unsigned long class,  struct  pci_dev *pcidev);
extern struct  pci_dev *pci_find_slot( unsigned char bus,  unsigned long devfn);

/* Pci Bus Read/Write Config functions */
extern unsigned char (*pci_read_config_byte)(unsigned char registernum,struct pci_dev *pcidev);
extern unsigned short (*pci_read_config_word)(unsigned char registernum,struct pci_dev *pcidev);
extern unsigned long (*pci_read_config_long)(unsigned char registernum,struct pci_dev *pcidev);
extern void (*pci_write_config_byte)(unsigned char registernum, unsigned char val,struct pci_dev *pcidev);
extern void (*pci_write_config_word)(unsigned char registernum, unsigned short val,struct pci_dev *pcidev);
extern void (*pci_write_config_long)(unsigned char registernum, unsigned long val,struct pci_dev *pcidev);

/* Pci Set Bus Master */
extern BOOL (*pci_set_master)(struct pci_dev *pcidev);

/* Interrupt functions */
extern BOOL (*pci_add_intserver)(struct Interrupt *PciInterrupt, struct pci_dev *pcidev);
extern void (*pci_rem_intserver)(struct Interrupt *PciInterrupt, struct pci_dev *pcidev);

/* Alloc/Free DMA memory */
extern APTR (*pci_allocdma_mem)(unsigned long size, unsigned long flags);
extern void (*pci_freedma_mem)(APTR buffer,unsigned long size);

/* Logic<->Physic Addr conversion */
extern APTR (*pci_logic_to_physic_addr)(APTR PciLogicalAddr, struct pci_dev *pcidev);
extern APTR (*pci_physic_to_logic_addr)(APTR PciPhysicalAddr,struct pci_dev *pcidev);

/* Obtain/Release PCI card */
extern BOOL (*pci_obtain_card)(struct pci_dev *pcidev);
extern void (*pci_release_card)(struct pci_dev *pcidev);

#endif	/* OPENPCI_PROTOSWRAP_H */ 
