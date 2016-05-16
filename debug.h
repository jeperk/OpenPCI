/*
 * $Id: debug.h,v 1.10 2003/07/28 18:47:27 titan Exp $
 */


//#define MOSDBG /* MorphOS Debug, we can disable it with MOS DebugFlags */
//#define DBG

#ifdef __GNUC__ /* GCC */
#define __FUNC__ __FUNCTION__
#endif

#ifndef __MORPHOS__
#include <clib/debug_protos.h>
	#ifdef DBG
	#define dprintf kprintf
	#else
	#define dprintf
	#endif
#endif

#ifdef __MORPHOS__

	#ifdef MOSDBG
	#define DEBUG_INIT(x) if(SysBase->ex_DebugFlags & EXECDEBUGF_PCI) x
	#define DEBUG_OPEN(x) if(SysBase->ex_DebugFlags & EXECDEBUGF_PCI) x
	#define DEBUG_CLOSE(x) if(SysBase->ex_DebugFlags & EXECDEBUGF_PCI) x
	#define DEBUG_EXPUNGE(x) if(SysBase->ex_DebugFlags & EXECDEBUGF_PCI) x
	#define DEBUG_NULL(x) if(SysBase->ex_DebugFlags & EXECDEBUGF_PCI) x
	#define DEBUG(x) if(SysBase->ex_DebugFlags & EXECDEBUGF_PCI) x
	#define DB(x) if(SysBase->ex_DebugFlags & EXECDEBUGF_PCI) { dprintf(__FILE__ "[%4ld]/" __FUNC__ "() : ",__LINE__); dprintf(x "\n"); }
	#define DBUG(x) if(SysBase->ex_DebugFlags & EXECDEBUGF_PCI) x
	#else
	#define dprintf
	#define DEBUG(x)
	#define DEBUG_INIT(x)
	#define DEBUG_OPEN(x)
	#define DEBUG_CLOSE(x)
	#define DEBUG_EXPUNGE(x)
	#define DEBUG_NULL(x)
	#define DB(x)
	#define DBUG(x)
	#endif

#else

	#ifdef DBG
	#define DEBUG_INIT(x) x
	#define DEBUG_OPEN(x) x
	#define DEBUG_CLOSE(x) x
	#define DEBUG_EXPUNGE(x) x
	#define DEBUG_NULL(x) x
	#define DEBUG(x) x
	#define DB(x) { dprintf(__FILE__ "[%4ld]/" __FUNC__ "() : ",__LINE__); dprintf(x "\n"); }
	#define DBUG(x) x
	#else
	#define dprintf
	#define DEBUG(x)
	#define DEBUG_INIT(x)
	#define DEBUG_OPEN(x)
	#define DEBUG_CLOSE(x)
	#define DEBUG_EXPUNGE(x)
	#define DEBUG_NULL(x)
	#define DB(x)
	#define DBUG(x)
	#endif

#endif


