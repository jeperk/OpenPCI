/* Return the bus type found*/
#pragma libcall OpenPciBase pci_bus 1e 0
/* IN/OUT Function for PCI Bus*/
/* Byte (8bits) Read/Write*/
#pragma libcall OpenPciBase pci_inb 24 801
#pragma libcall OpenPciBase pci_outb 2a 8002
/* Word (16bits) Read/Write*/
#pragma libcall OpenPciBase pci_inw 30 801
#pragma libcall OpenPciBase pci_outw 36 8002
/* Long (32bits) Read/Write*/
#pragma libcall OpenPciBase pci_inl 3c 801
#pragma libcall OpenPciBase pci_outl 42 8002
/* Amiga Mem and Pci Mem Read/Write (must be a multiple of 8bytes)*/
#pragma libcall OpenPciBase pci_to_hostcpy 48 09803
#pragma libcall OpenPciBase host_to_pcicpy 4e 09803
#pragma libcall OpenPciBase pci_to_pcicpy 54 09803
/* Pci Find Functions*/
#pragma libcall OpenPciBase pci_find_device 5a 81003
#pragma libcall OpenPciBase pci_find_class 60 8002
#pragma libcall OpenPciBase pci_find_slot 66 1002
/* Pci Bus Read/Write Config functions*/
#pragma libcall OpenPciBase pci_read_config_byte 6c 8002
#pragma libcall OpenPciBase pci_read_config_word 72 8002
#pragma libcall OpenPciBase pci_read_config_long 78 8002
#pragma libcall OpenPciBase pci_write_config_byte 7e 81003
#pragma libcall OpenPciBase pci_write_config_word 84 81003
#pragma libcall OpenPciBase pci_write_config_long 8a 81003
/* Pci Set Bus Master*/
#pragma libcall OpenPciBase pci_set_master 90 801
/* Interrupt functions*/
#pragma libcall OpenPciBase pci_add_intserver 96 9802
#pragma libcall OpenPciBase pci_rem_intserver 9c 9802
/* Pci Alloc/Free DMA memory*/
#pragma libcall OpenPciBase pci_allocdma_mem a2 1002
#pragma libcall OpenPciBase pci_freedma_mem a8 0802
/* Logic<->Physic Addr conversion*/
#pragma libcall OpenPciBase pci_logic_to_physic_addr ae 9802
#pragma libcall OpenPciBase pci_physic_to_logic_addr b4 9802
/* Obtain/Release PCI card*/
#pragma libcall OpenPciBase pci_obtain_card ba 801
#pragma libcall OpenPciBase pci_release_card c0 801
