
#ifndef PROMETHEUSWRAPPER_H
#define PROMETHEUSWRAPPER_H

// Prometheus
#include "Prometheus-3.0/include/libraries/prometheus.h"
#include "Prometheus-3.0/include/clib/prometheus_protos.h"

#ifdef __GNUC__
#include "../libraries/openpci.h"
#include "Prometheus-3.0/include/inline/prometheus_protos.h"
#else
#include "/libraries/openpci.h"
#include "Prometheus-3.0/include/pragmas/prometheus_pragmas.h"
#endif

extern struct Library   *PrometheusBase;

extern BOOL PROMETHEUSWrapper(void);
extern void PROMETHEUSclose(void);
extern void PROMETHEUSpcidev(void);

extern unsigned char PROMETHEUSpci_inb(unsigned long address);
extern void PROMETHEUSpci_outb(unsigned char value, unsigned long address);

/* Word (16bits) Read/Write */
extern unsigned short PROMETHEUSpci_inw(unsigned long address);
extern void PROMETHEUSpci_outw(unsigned short value, unsigned long address);

/* Long (32bits) Read/Write  */
extern unsigned long PROMETHEUSpci_inl(unsigned long address);
extern void PROMETHEUSpci_outl(unsigned long value, unsigned long address);

/* Amiga Mem and Pci Mem Read/Write (must be a multiple of 16bytes) (it's a very fast mem bloc copy) */
extern void PROMETHEUSpci_to_hostcpy(void *pcimemsrc, void *memdest, unsigned long packetsize);
extern void PROMETHEUShost_to_pcicpy(void *memsrc, void *pcimemdest, unsigned long packetsize);
extern void PROMETHEUSpci_to_pcicpy(void *pcimemsrc, void *pcimemdest, unsigned long packetsize);

/* Pci Bus Read/Write Config functions */
extern unsigned char PROMETHEUSpci_read_config_byte(unsigned char registernum, struct pci_dev *dev);
extern unsigned short PROMETHEUSpci_read_config_word(unsigned char registernum, struct pci_dev *dev);
extern unsigned long PROMETHEUSpci_read_config_long(unsigned char registernum, struct pci_dev *dev);
extern void PROMETHEUSpci_write_config_byte(unsigned char registernum, unsigned char val, struct pci_dev *dev);
extern void PROMETHEUSpci_write_config_word(unsigned char registernum, unsigned short val, struct pci_dev *dev);
extern void PROMETHEUSpci_write_config_long(unsigned char registernum, unsigned long val, struct pci_dev *dev);

/* Pci Set Bus Master */
extern BOOL PROMETHEUSpci_set_master(struct pci_dev *dev);

/* Interrupt functions */
extern BOOL PROMETHEUSpci_add_intserver(struct Interrupt *PciInterrupt, struct pci_dev *pcidev);
extern void PROMETHEUSpci_rem_intserver(struct Interrupt *PciInterrupt, struct pci_dev *pcidev);

/* Alloc/Free DMA memory */
extern APTR PROMETHEUSpci_allocdma_mem(unsigned long size, unsigned long flags);
extern void PROMETHEUSpci_freedma_mem(APTR buffer, unsigned long size);

/* Logic<->Physic Addr conversion */
extern APTR PROMETHEUSpci_logic_to_physic_addr(APTR PciLogicalAddr, struct pci_dev *pcidev);
extern APTR PROMETHEUSpci_physic_to_logic_addr(APTR PciPhysicalAddr, struct pci_dev *pcidev);

/* Obtain/Release PCI card */
extern BOOL PROMETHEUSpci_obtain_card(struct pci_dev *pcidev);
extern void PROMETHEUSpci_release_card(struct pci_dev *pcidev);

#endif /* PROMETHEUSWRAPPER_H */
