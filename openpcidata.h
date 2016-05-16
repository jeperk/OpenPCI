/*
 * $Id: openpcidata.h,v 1.6 2003/07/28 18:47:27 titan Exp $
 */

#ifndef OPENPCIDATA_HEADER
#define OPENPCIDATA_HEADER

#include <exec/execbase.h>
#include <exec/types.h>
#include <exec/tasks.h>
#include <exec/ports.h>
#include <exec/memory.h>
#include <exec/lists.h>
#include <exec/devices.h>
#include <exec/io.h>
#include <exec/semaphores.h>
#include <exec/execbase.h>
#include <exec/alerts.h>
#include <exec/libraries.h>
#include <exec/interrupts.h>
#include <exec/resident.h>
#include <devices/timer.h>

#define __USE_SYSBASE

#include <proto/exec.h>
#include <proto/timer.h>
#include <proto/utility.h>
#include <proto/locale.h>

#ifdef __MORPHOS__

#include <emul/emulinterface.h>
#include <emul/emulregs.h>

/* Inlined Morphos private Quark call and structure */
#include "mosquark_private.h"

#else

#include <clib/alib_protos.h>

#endif

#include "compiler.h"

#include "debug.h"
#include "pcibus.h"
#include "pci.h"

#define MAX_PCI_CARD_NAME 100

#ifdef __MORPHOS__
#pragma pack(2)
#endif

struct OpenPciLib
{
	struct Library        Lib;
	BPTR                    SegList;
	struct ExecBase    *SBase;
	struct pci_dev        *pcidev;
	struct pci_dev        *root;
	unsigned char         bus;
};

/* Internal reserved structure */
struct OpenPciRes
{
	void *board;
	BOOL pci_cardlocked; /* Is this PCI card is software locked ? */
	char pci_cardname[MAX_PCI_CARD_NAME+1];
	void *IntObject; /* Internal PCIX Interrupt object */
	struct  MinList *IntList; /* Internal CybPCI/PCIX Interrupt List */
};

#ifdef __MORPHOS__
#pragma pack()
#endif

extern struct OpenPciLib *OpenPciBase;

#endif /* OPENPCIDATA_HEADER */
