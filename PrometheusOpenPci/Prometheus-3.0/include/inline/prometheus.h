/* Automatically generated header! Do not edit! */

#ifndef _INLINE_PROMETHEUS_H
#define _INLINE_PROMETHEUS_H

#ifndef __INLINE_MACROS_H
#include <inline/macros.h>
#endif /* !__INLINE_MACROS_H */

#ifndef PROMETHEUS_BASE_NAME
#define PROMETHEUS_BASE_NAME PrometheusBase
#endif /* !PROMETHEUS_BASE_NAME */

#define Prm_AddIntServer(board, intr) \
	LP2(0x54, BOOL, Prm_AddIntServer, PCIBoard *, board, a0, struct Interrupt *, intr, a1, \
	, PROMETHEUS_BASE_NAME)

#define Prm_AllocDMABuffer(size) \
	LP1(0x60, APTR, Prm_AllocDMABuffer, ULONG, size, d0, \
	, PROMETHEUS_BASE_NAME)

#define Prm_FindBoardTagList(previous, taglist) \
	LP2(0x1e, PCIBoard *, Prm_FindBoardTagList, PCIBoard *, previous, a0, struct TagItem*, taglist, a1, \
	, PROMETHEUS_BASE_NAME)

#ifndef NO_INLINE_STDARG
#define Prm_FindBoardTags(a0, tags...) \
	({ULONG _tags[] = { tags }; Prm_FindBoardTagList((a0), (struct TagItem*)_tags);})
#endif /* !NO_INLINE_STDARG */

#define Prm_FreeDMABuffer(block, size) \
	LP2NR(0x66, Prm_FreeDMABuffer, APTR, block, a0, ULONG, size, d0, \
	, PROMETHEUS_BASE_NAME)

#define Prm_GetBoardAttrsTagList(board, taglist) \
	LP2(0x24, ULONG, Prm_GetBoardAttrsTagList, PCIBoard *, board, a0, struct TagItem*, taglist, a1, \
	, PROMETHEUS_BASE_NAME)

#ifndef NO_INLINE_STDARG
#define Prm_GetBoardAttrsTags(a0, tags...) \
	({ULONG _tags[] = { tags }; Prm_GetBoardAttrsTagList((a0), (struct TagItem*)_tags);})
#endif /* !NO_INLINE_STDARG */

#define Prm_GetPhysicalAddress(addr) \
	LP1(0x6c, APTR, Prm_GetPhysicalAddress, APTR, addr, d0, \
	, PROMETHEUS_BASE_NAME)

#define Prm_GetVirtualAddress(addr) \
	LP1(0x72, APTR, Prm_GetVirtualAddress, APTR, addr, d0, \
	, PROMETHEUS_BASE_NAME)

#define Prm_ReadConfigByte(board, offset) \
	LP2(0x36, UBYTE, Prm_ReadConfigByte, PCIBoard *, board, a0, UBYTE, offset, d0, \
	, PROMETHEUS_BASE_NAME)

#define Prm_ReadConfigLong(board, offset) \
	LP2(0x2a, ULONG, Prm_ReadConfigLong, PCIBoard *, board, a0, UBYTE, offset, d0, \
	, PROMETHEUS_BASE_NAME)

#define Prm_ReadConfigWord(board, offset) \
	LP2(0x30, UWORD, Prm_ReadConfigWord, PCIBoard *, board, a0, UBYTE, offset, d0, \
	, PROMETHEUS_BASE_NAME)

#define Prm_RemIntServer(board, intr) \
	LP2NR(0x5a, Prm_RemIntServer, PCIBoard *, board, a0, struct Interrupt *, intr, a1, \
	, PROMETHEUS_BASE_NAME)

#define Prm_SetBoardAttrsTagList(board, taglist) \
	LP2(0x4e, ULONG, Prm_SetBoardAttrsTagList, PCIBoard *, board, a0, struct TagItem*, taglist, a1, \
	, PROMETHEUS_BASE_NAME)

#ifndef NO_INLINE_STDARG
#define Prm_SetBoardAttrsTags(a0, tags...) \
	({ULONG _tags[] = { tags }; Prm_SetBoardAttrsTagList((a0), (struct TagItem*)_tags);})
#endif /* !NO_INLINE_STDARG */

#define Prm_WriteConfigByte(board, data, offset) \
	LP3NR(0x48, Prm_WriteConfigByte, PCIBoard *, board, a0, UBYTE, data, d0, UBYTE, offset, d1, \
	, PROMETHEUS_BASE_NAME)

#define Prm_WriteConfigLong(board, data, offset) \
	LP3NR(0x3c, Prm_WriteConfigLong, PCIBoard *, board, a0, ULONG, data, d0, UBYTE, offset, d1, \
	, PROMETHEUS_BASE_NAME)

#define Prm_WriteConfigWord(board, data, offset) \
	LP3NR(0x42, Prm_WriteConfigWord, PCIBoard *, board, a0, UWORD, data, d0, UBYTE, offset, d1, \
	, PROMETHEUS_BASE_NAME)

#endif /* !_INLINE_PROMETHEUS_H */
