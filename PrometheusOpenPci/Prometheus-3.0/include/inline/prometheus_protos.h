#ifndef _VBCCINLINE_PROMETHEUS_H
#define _VBCCINLINE_PROMETHEUS_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

PCIBoard * __Prm_FindBoardTagList(__reg("a6") struct Library *, __reg("a0") PCIBoard * previous, __reg("a1") struct TagItem* taglist)="\tjsr\t-30(a6)";
#define Prm_FindBoardTagList(previous, taglist) __Prm_FindBoardTagList(PrometheusBase, (previous), (taglist))

#if !defined(NO_INLINE_STDARG) && (__STDC__ == 1L) && (__STDC_VERSION__ >= 199901L)
PCIBoard * __Prm_FindBoardTags(__reg("a6") struct Library *, __reg("a0") PCIBoard * previous, Tag taglist, ...)="\tmovea.l\ta7,a1\n\tjsr\t-30(a6)";
#define Prm_FindBoardTags(previous, ...) __Prm_FindBoardTags(PrometheusBase, (previous), __VA_ARGS__)
#endif

ULONG __Prm_GetBoardAttrsTagList(__reg("a6") struct Library *, __reg("a0") PCIBoard * board, __reg("a1") struct TagItem* taglist)="\tjsr\t-36(a6)";
#define Prm_GetBoardAttrsTagList(board, taglist) __Prm_GetBoardAttrsTagList(PrometheusBase, (board), (taglist))

#if !defined(NO_INLINE_STDARG) && (__STDC__ == 1L) && (__STDC_VERSION__ >= 199901L)
ULONG __Prm_GetBoardAttrsTags(__reg("a6") struct Library *, __reg("a0") PCIBoard * board, Tag taglist, ...)="\tmovea.l\ta7,a1\n\tjsr\t-36(a6)";
#define Prm_GetBoardAttrsTags(board, ...) __Prm_GetBoardAttrsTags(PrometheusBase, (board), __VA_ARGS__)
#endif

ULONG __Prm_ReadConfigLong(__reg("a6") struct Library *, __reg("a0") PCIBoard * board, __reg("d0") UBYTE offset)="\tjsr\t-42(a6)";
#define Prm_ReadConfigLong(board, offset) __Prm_ReadConfigLong(PrometheusBase, (board), (offset))

UWORD __Prm_ReadConfigWord(__reg("a6") struct Library *, __reg("a0") PCIBoard * board, __reg("d0") UBYTE offset)="\tjsr\t-48(a6)";
#define Prm_ReadConfigWord(board, offset) __Prm_ReadConfigWord(PrometheusBase, (board), (offset))

UBYTE __Prm_ReadConfigByte(__reg("a6") struct Library *, __reg("a0") PCIBoard * board, __reg("d0") UBYTE offset)="\tjsr\t-54(a6)";
#define Prm_ReadConfigByte(board, offset) __Prm_ReadConfigByte(PrometheusBase, (board), (offset))

VOID __Prm_WriteConfigLong(__reg("a6") struct Library *, __reg("a0") PCIBoard * board, __reg("d0") ULONG data, __reg("d1") UBYTE offset)="\tjsr\t-60(a6)";
#define Prm_WriteConfigLong(board, data, offset) __Prm_WriteConfigLong(PrometheusBase, (board), (data), (offset))

VOID __Prm_WriteConfigWord(__reg("a6") struct Library *, __reg("a0") PCIBoard * board, __reg("d0") UWORD data, __reg("d1") UBYTE offset)="\tjsr\t-66(a6)";
#define Prm_WriteConfigWord(board, data, offset) __Prm_WriteConfigWord(PrometheusBase, (board), (data), (offset))

VOID __Prm_WriteConfigByte(__reg("a6") struct Library *, __reg("a0") PCIBoard * board, __reg("d0") UBYTE data, __reg("d1") UBYTE offset)="\tjsr\t-72(a6)";
#define Prm_WriteConfigByte(board, data, offset) __Prm_WriteConfigByte(PrometheusBase, (board), (data), (offset))

ULONG __Prm_SetBoardAttrsTagList(__reg("a6") struct Library *, __reg("a0") PCIBoard * board, __reg("a1") struct TagItem* taglist)="\tjsr\t-78(a6)";
#define Prm_SetBoardAttrsTagList(board, taglist) __Prm_SetBoardAttrsTagList(PrometheusBase, (board), (taglist))

#if !defined(NO_INLINE_STDARG) && (__STDC__ == 1L) && (__STDC_VERSION__ >= 199901L)
ULONG __Prm_SetBoardAttrsTags(__reg("a6") struct Library *, __reg("a0") PCIBoard * board, Tag taglist, ...)="\tmovea.l\ta7,a1\n\tjsr\t-78(a6)";
#define Prm_SetBoardAttrsTags(board, ...) __Prm_SetBoardAttrsTags(PrometheusBase, (board), __VA_ARGS__)
#endif

BOOL __Prm_AddIntServer(__reg("a6") struct Library *, __reg("a0") PCIBoard * board, __reg("a1") struct Interrupt * intr)="\tjsr\t-84(a6)";
#define Prm_AddIntServer(board, intr) __Prm_AddIntServer(PrometheusBase, (board), (intr))

VOID __Prm_RemIntServer(__reg("a6") struct Library *, __reg("a0") PCIBoard * board, __reg("a1") struct Interrupt * intr)="\tjsr\t-90(a6)";
#define Prm_RemIntServer(board, intr) __Prm_RemIntServer(PrometheusBase, (board), (intr))

APTR __Prm_AllocDMABuffer(__reg("a6") struct Library *, __reg("d0") ULONG size)="\tjsr\t-96(a6)";
#define Prm_AllocDMABuffer(size) __Prm_AllocDMABuffer(PrometheusBase, (size))

VOID __Prm_FreeDMABuffer(__reg("a6") struct Library *, __reg("a0") APTR block, __reg("d0") ULONG size)="\tjsr\t-102(a6)";
#define Prm_FreeDMABuffer(block, size) __Prm_FreeDMABuffer(PrometheusBase, (block), (size))

APTR __Prm_GetPhysicalAddress(__reg("a6") struct Library *, __reg("d0") APTR addr)="\tjsr\t-108(a6)";
#define Prm_GetPhysicalAddress(addr) __Prm_GetPhysicalAddress(PrometheusBase, (addr))

APTR __Prm_GetVirtualAddress(__reg("a6") struct Library *, __reg("d0") APTR addr)="\tjsr\t-114(a6)";
#define Prm_GetVirtualAddress(addr) __Prm_GetVirtualAddress(PrometheusBase, (addr))

#endif /*  _VBCCINLINE_PROMETHEUS_H  */
