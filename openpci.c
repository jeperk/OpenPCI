/*
 * $Id: openpci.c,v 1.3 2003/02/23 17:11:14 titan Exp $
 */

#include "openpcidata.h"

#include "openpci.library_VERSION.h"

#include "pcibus.h"

#include "pci.h"

#include "openpci_protosWrapper.h"

/* The lib execute init protection which simply returns
 */

ULONG NoExecute(void)
{
	return(0);
}

struct ExecBase *SysBase;
BPTR SegList;
struct Library *UtilityBase = NULL;
struct DosLibrary  *DOSBase = NULL;
struct Library   *ExpansionBase = NULL;

#ifdef __SASC
	struct LocaleBase *LocaleBase = 0;
	struct Device *TimerBase = 0;
#else
	struct Library *LocaleBase = 0;
	struct Library *TimerBase = 0;
#endif

struct OpenPciLib *OpenPciBase;

extern void  (*LibFuncTable[29])(void);
struct OpenPciLib * __saveds ASM LIB_Init(REG(d0, struct OpenPciLib *), REG(a0, BPTR), REG(a6, struct ExecBase *));

extern   ULONG Dummy;

struct LibInitStruct
{
	ULONG LibSize;
	void  *FuncTable;
	void  *DataTable;
/*
	void  (*InitFunc)(void);
*/
	APTR InitFunc;
};

struct LibInitStruct LibInitStruct=
{
	sizeof(struct OpenPciLib),
	LibFuncTable,
	NULL,
/*
	(void (*)(void)) &LIB_Init
*/
	(APTR) LIB_Init
};


struct Resident __aligned LibResident=
{
	RTC_MATCHWORD,
	&LibResident,
	&LibResident + 1,
#ifdef __MORPHOS__
	RTF_PPC | RTF_AUTOINIT,
#else
	RTF_AUTOINIT,
#endif
	VERSION,
	NT_LIBRARY,
	1,
	"openpci.library",
	VERSTAG,//VSTRING,
	&LibInitStruct
};

/*
 * To tell the loader that this is a new emulppc elf and not
 * one for the ppc.library.
 * ** IMPORTANT **
 */
#ifdef __MORPHOS__
ULONG __abox__=1;
#endif

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

ULONG LIB_Reserved(void);

static void __saveds ASM LibCleanup(REG(a6, struct OpenPciLib *LibBase))
{
	if (UtilityBase)
		CloseLibrary(UtilityBase);

	FreePciDevStruct();

}

/*
 * Resident is a RTF_PPC one...that means it`s called
 * natively with normal PPC SysV4 ABI argument order.
 */
struct OpenPciLib * __saveds ASM LIB_Init(REG(d0, struct OpenPciLib *LibBase),
                                          REG(a0, BPTR               seglist),
                                          REG(a6, struct ExecBase   *sysbase))
{
	
	DEBUG_INIT(dprintf("LibInit: LibBase 0x%lx SegList 0x%lx SBase 0x%lx\n", LibBase, seglist, sysbase));

	SysBase = (struct ExecBase *)sysbase;

	if ((UtilityBase = OpenLibrary("utility.library", 39L)))
	{
		DEBUG(dprintf("utility OK\n"));
		
		SegList = seglist;
		LibBase->Lib.lib_Version     = VERSION;
		LibBase->Lib.lib_Revision    = REVISION;
		LibBase->Lib.lib_Node.ln_Pri = 0;
		
		/* We set all pointer on a Null function */
		
		pci_inb=(unsigned char (* )(unsigned long address))&LIB_Reserved;
		pci_outb=(void (* )(unsigned char value, unsigned long address))&LIB_Reserved;
		pci_inw=(unsigned short (* )(unsigned long address))&LIB_Reserved;
		pci_outw=(void (* )(unsigned short value, unsigned long address))&LIB_Reserved;
		pci_inl=(unsigned long (* )(unsigned long address))&LIB_Reserved;
		pci_outl=(void (* )(unsigned long value, unsigned long address))&LIB_Reserved;
	
		pci_to_hostcpy=(void (* )(void *pcimemsrc, void *memdest, unsigned long packetsize))&LIB_Reserved;
		host_to_pcicpy=(void (* )(void *memsrc, void *pcimemdest, unsigned long packetsize))&LIB_Reserved;
		pci_to_pcicpy=(void (* )(void *pcimemsrc, void *pcimemdest, unsigned long packetsize))&LIB_Reserved;
	
		pci_read_config_byte=(unsigned char (* )(unsigned char registernum,struct pci_dev *pcidev))&LIB_Reserved;
		pci_read_config_word=(unsigned short (* )(unsigned char registernum,struct pci_dev *pcidev))&LIB_Reserved;
		pci_read_config_long=(unsigned long (* )(unsigned char registernum,struct pci_dev *pcidev))&LIB_Reserved;
		pci_write_config_byte=(void (* )(unsigned char registernum, unsigned char val,struct pci_dev *pcidev))&LIB_Reserved;
		pci_write_config_word=(void (* )(unsigned char registernum, unsigned short val,struct pci_dev *pcidev))&LIB_Reserved;
		pci_write_config_long=(void (* )(unsigned char registernum, unsigned long val,struct pci_dev *pcidev))&LIB_Reserved;
		
		pci_set_master=(BOOL (* )(struct pci_dev *pcidev))&LIB_Reserved;
		
		pci_add_intserver=(BOOL (* )(struct Interrupt *PciInterrupt,struct pci_dev *pcidev))&LIB_Reserved;
		pci_rem_intserver=(void (* )(struct Interrupt *PciInterrupt, struct pci_dev *pcidev))&LIB_Reserved;
		
		pci_allocdma_mem=(APTR (* )(unsigned long size, unsigned long flags))&LIB_Reserved;
		pci_freedma_mem=(void (* )(APTR buffer,unsigned long size))&LIB_Reserved;
		
		pci_logic_to_physic_addr=(APTR (* )(APTR PciLogicalAddr, struct pci_dev *pcidev))&LIB_Reserved;
		pci_physic_to_logic_addr=(APTR (* )(APTR PciPhysicalAddr, struct pci_dev *pcidev))&LIB_Reserved;

		pci_obtain_card=(BOOL (* )(struct pci_dev *pcidev))&LIB_Reserved;
		pci_release_card=(void (* )(struct pci_dev *pcidev))&LIB_Reserved;

		OpenPciBase = LibBase;
		
		OpenPciBase->root=NULL;
		
		FindPCIBus();
		
		DEBUG(dprintf("Bus found : 0x%lx\n",OpenPciBase->bus));

		/* 
			68k version doesn't support Pegasos 
			Pegasos users must use openpci.library.elf		
		*/
#ifdef __SASC
		if(OpenPciBase->bus&PegasosBus)
		{
			LibCleanup(LibBase);
			return NULL;
		}	
#endif

		if(OpenPCIBus(OpenPciBase->bus)==NULL)
		{
			LibCleanup(LibBase);
			return NULL;
		}
		return(LibBase);
	} /* if Utility */

	LibCleanup(LibBase);
	return NULL;
}

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

ULONG __saveds ASM LibExpunge(REG(a6, struct OpenPciLib *LibBase))
{
	BPTR  MySegment;

	DEBUG_EXPUNGE(dprintf("LIB_Expunge: LibBase 0x%lx <%s> OpenCount %ld\n",
	              LibBase,
	              LibBase->Lib.lib_Node.ln_Name,
	              LibBase->Lib.lib_OpenCnt));

	MySegment     =         SegList;

	if (LibBase->Lib.lib_OpenCnt)
	{
		DEBUG_EXPUNGE(dprintf("LIB_Expunge: set LIBF_DELEXP\n"));
		LibBase->Lib.lib_Flags |= LIBF_DELEXP;
		return (int)NULL;
	}

	/* We don`t need a forbid() because Expunge and Close
	* are called with a pending forbid.
	* But let`s do it for savety if somebody does it by hand.
	*/
	Forbid();
	DEBUG_EXPUNGE(dprintf("LIB_Expunge: remove the library\n"));
	Remove(&LibBase->Lib.lib_Node);
	Permit();

	LibCleanup(LibBase);

	DEBUG_EXPUNGE(dprintf("LIB_Expunge: free the library\n"));
	FreeMem((APTR)((ULONG)(LibBase) - (ULONG)(LibBase->Lib.lib_NegSize)),
	LibBase->Lib.lib_NegSize + LibBase->Lib.lib_PosSize);

	DEBUG_EXPUNGE(dprintf("LIB_Expunge: return Segment 0x%lx to ramlib\n",
	              MySegment));
	return((ULONG) MySegment);
}

#ifdef __MORPHOS__
ULONG LIB_Expunge(void)
{
	struct OpenPciLib *LibBase = (struct OpenPciLib *) REG_A6;
#else
ULONG ASM LIB_Expunge(REG(a6, struct OpenPciLib *LibBase))
{
#endif
	DEBUG_EXPUNGE(dprintf("LIB_Expunge:\n"));
	return(LibExpunge(LibBase));
}

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

#ifdef __MORPHOS__
struct OpenPciLib *LIB_Open(void)
{
	struct OpenPciLib *LibBase = (struct OpenPciLib *) REG_A6;
#else
struct OpenPciLib * ASM LIB_Open(REG(a6, struct OpenPciLib *LibBase))
{
#endif
	DEBUG_OPEN(dprintf("LIB_Open: 0x%lx <%s> OpenCount %ld\n",
	           LibBase,
	           LibBase->Lib.lib_Node.ln_Name,
	           LibBase->Lib.lib_OpenCnt));

	LibBase->Lib.lib_Flags      &=      ~LIBF_DELEXP;
	LibBase->Lib.lib_OpenCnt++;

	return(LibBase);
}

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

#ifdef __MORPHOS__
ULONG LIB_Close(void)
{
	struct OpenPciLib *LibBase = (struct OpenPciLib *) REG_A6;
#else
ULONG ASM LIB_Close(REG(a6, struct OpenPciLib *LibBase))
{
#endif
	DEBUG_CLOSE(dprintf("LIB_Close: 0x%lx <%s> OpenCount %ld\n",
	            LibBase,
	            LibBase->Lib.lib_Node.ln_Name,
	            LibBase->Lib.lib_OpenCnt));

	if ((--LibBase->Lib.lib_OpenCnt) > 0)
	{
		DEBUG_CLOSE(dprintf("LIB_Close: done\n"));
	}
	else
	{
		if (LibBase->Lib.lib_Flags & LIBF_DELEXP)
		{
			DEBUG_CLOSE(dprintf("LIB_Close: LIBF_DELEXP set\n"));
			return(LibExpunge(LibBase));
		}
	}
	return(0);
}

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

ULONG LIB_Reserved(void)
{
	DEBUG_NULL(dprintf("LIB_Reserved:\n"));

	return(0);
}

/* ----------------------------------------------------------------------------------------
   ! __SASC stuff:
   !
   ! This is only for SAS/C - its intention is to turn off internal CTRL-C handling
   ! for standard C functions and to avoid calls to exit() et al.
   ---------------------------------------------------------------------------------------- */

#ifdef __SASC

//ULONG XCEXIT       = NULL; /* These symbols may be referenced by    */
//ULONG _XCEXIT      = NULL; /* some functions of sc.lib, but should  */
ULONG ONBREAK      = NULL; /* never be used inside a shared library */
ULONG _ONBREAK     = NULL;
ULONG base         = NULL; /* Note, that XCEXIT/ONBREAK actually    */
ULONG _base        = NULL; /* should have been defined as functions */
ULONG ProgramName  = NULL; /* and not as ULONGs...                  */
ULONG _ProgramName = NULL;
ULONG StackPtr     = NULL;
ULONG _StackPtr    = NULL;
ULONG oserr        = NULL;
ULONG _oserr       = NULL;
ULONG OSERR        = NULL;
ULONG _OSERR       = NULL;

void __regargs __chkabort(void) { }  /* a shared library cannot be    */
void __regargs _CXBRK(void)     { }  /* CTRL-C aborted when doing I/O */

#endif /* __SASC */
