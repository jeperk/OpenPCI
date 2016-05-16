
#ifndef PciBusH
#define PciBusH

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include <exec/types.h>
#include <exec/memory.h>
#include <exec/semaphores.h>
#include <clib/exec_protos.h>
#include <clib/expansion_protos.h>


#include <proto/dos.h>
#include <libraries/dos.h>
#include <libraries/configvars.h>

#include "internlibraries/openpci.h"

#include "compiler.h"

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifdef __GNUC__
extern struct Library   *ExpansionBase;
#endif

extern unsigned short pci_bus(void);
extern unsigned short FindPCIBus(void);
extern BOOL ASM OpenPCIBus(REG(d0,int pcibus));
extern void FreePciDevStruct(void);

#endif /* PCIBusH*/
