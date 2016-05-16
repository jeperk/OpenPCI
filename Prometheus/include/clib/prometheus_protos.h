#ifndef  CLIB_PROMETHEUS_PROTOS_H
#define  CLIB_PROMETHEUS_PROTOS_H

/*
**	$VER: prometheus_protos.h 2.0 (14.1.2002)
**
**	C prototypes. For use with 32 bit integers only.
**
**	(C) Copyright 2000-2002 Matay.
**	    All Rights Reserved
*/

#ifndef EXEC_INTERRUPTS_H
#include <exec/interrupts.h>
#endif /* EXEC_INTERRUPTS_H */

#ifndef  EXEC_TYPES_H
#include <exec/types.h>
#endif /* EXEC_TYPES_H */

#ifndef  LIBRARIES_PROMETHEUS_H
#include <libraries/prometheus.h>
#endif /* LIBRARIES_PROMETHEUS_H */

#ifndef  UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif /* UTILITY_TAGITEM_H */

/*--- functions in V1 or higher ---*/

PCIBoard *Prm_FindBoardTagList(PCIBoard *previous, struct TagItem* taglist);
PCIBoard *Prm_FindBoardTags(PCIBoard *previous, Tag tag1, ...);
ULONG Prm_GetBoardAttrsTagList(PCIBoard *board, struct TagItem* taglist);
ULONG Prm_GetBoardAttrsTags(PCIBoard *board, Tag tag1, ...);

/*--- functions in V2 or higher ---*/

ULONG Prm_ReadConfigLong(PCIBoard *board, UBYTE offset);
UWORD Prm_ReadConfigWord(PCIBoard *board, UBYTE offset);
UBYTE Prm_ReadConfigByte(PCIBoard *board, UBYTE offset);
VOID Prm_WriteConfigLong(PCIBoard *board, ULONG data, UBYTE offset);
VOID Prm_WriteConfigWord(PCIBoard *board, UWORD data, UBYTE offset);
VOID Prm_WriteConfigByte(PCIBoard *board, UBYTE data, UBYTE offset);
ULONG Prm_SetBoardAttrsTagList(PCIBoard *board, struct TagItem* taglist);
ULONG Prm_SetBoardAttrsTags(PCIBoard *board, Tag tag1, ...);
BOOL Prm_AddIntServer(PCIBoard *board, struct Interrupt *intr);
VOID Prm_RemIntServer(PCIBoard *board, struct Interrupt *intr);
APTR Prm_AllocDMABuffer(ULONG size);
VOID Prm_FreeDMABuffer(APTR buffer, ULONG size);
APTR Prm_GetPhysicalAddress(APTR addr);

#endif	 /* CLIB_PROMETHEUS_PROTOS_H */
