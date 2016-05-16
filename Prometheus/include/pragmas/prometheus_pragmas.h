#ifndef _INCLUDE_PRAGMA_PROMETHEUS_LIB_H
#define _INCLUDE_PRAGMA_PROMETHEUS_LIB_H

#ifndef CLIB_PROMETHEUS_PROTOS_H
#include <clib/prometheus_protos.h>
#endif

#if defined(AZTEC_C) || defined(__MAXON__) || defined(__STORM__)
#pragma amicall(PrometheusBase,0x01e,Prm_FindBoardTagList(a0,a1))
#pragma amicall(PrometheusBase,0x024,Prm_GetBoardAttrsTagList(a0,a1))
#pragma amicall(PrometheusBase,0x02a,Prm_ReadConfigLong(a0,d0))
#pragma amicall(PrometheusBase,0x030,Prm_ReadConfigWord(a0,d0))
#pragma amicall(PrometheusBase,0x036,Prm_ReadConfigByte(a0,d0))
#pragma amicall(PrometheusBase,0x03c,Prm_WriteConfigLong(a0,d0,d1))
#pragma amicall(PrometheusBase,0x042,Prm_WriteConfigWord(a0,d0,d1))
#pragma amicall(PrometheusBase,0x048,Prm_WriteConfigByte(a0,d0,d1))
#pragma amicall(PrometheusBase,0x04e,Prm_SetBoardAttrsTagList(a0,a1))
#pragma amicall(PrometheusBase,0x054,Prm_AddIntServer(a0,a1))
#pragma amicall(PrometheusBase,0x05a,Prm_RemIntServer(a0,a1))
#pragma amicall(PrometheusBase,0x060,Prm_AllocDMABuffer(d0))
#pragma amicall(PrometheusBase,0x066,Prm_FreeDMABuffer(a0,d0))
#pragma amicall(PrometheusBase,0x06c,Prm_GetPhysicalAddress(d0))
#endif
#if defined(_DCC) || defined(__SASC)
#pragma  libcall PrometheusBase Prm_FindBoardTagList   01e 9802
#pragma  libcall PrometheusBase Prm_GetBoardAttrsTagList 024 9802
#pragma  libcall PrometheusBase Prm_ReadConfigLong     02a 0802
#pragma  libcall PrometheusBase Prm_ReadConfigWord     030 0802
#pragma  libcall PrometheusBase Prm_ReadConfigByte     036 0802
#pragma  libcall PrometheusBase Prm_WriteConfigLong    03c 10803
#pragma  libcall PrometheusBase Prm_WriteConfigWord    042 10803
#pragma  libcall PrometheusBase Prm_WriteConfigByte    048 10803
#pragma  libcall PrometheusBase Prm_SetBoardAttrsTagList 04e 9802
#pragma  libcall PrometheusBase Prm_AddIntServer       054 9802
#pragma  libcall PrometheusBase Prm_RemIntServer       05a 9802
#pragma  libcall PrometheusBase Prm_AllocDMABuffer     060 001
#pragma  libcall PrometheusBase Prm_FreeDMABuffer      066 0802
#pragma  libcall PrometheusBase Prm_GetPhysicalAddress 06c 001
#endif
#ifdef __STORM__
#pragma tagcall(PrometheusBase,0x01e,Prm_FindBoardTags(a0,a1))
#pragma tagcall(PrometheusBase,0x024,Prm_GetBoardAttrsTags(a0,a1))
#pragma tagcall(PrometheusBase,0x04e,Prm_SetBoardAttrsTags(a0,a1))
#endif
#ifdef __SASC_60
#pragma  tagcall PrometheusBase Prm_FindBoardTags      01e 9802
#pragma  tagcall PrometheusBase Prm_GetBoardAttrsTags  024 9802
#pragma  tagcall PrometheusBase Prm_SetBoardAttrsTags  04e 9802
#endif

#endif	/*  _INCLUDE_PRAGMA_PROMETHEUS_LIB_H  */
