#ifndef COMPILER_H
#define COMPILER_H

#ifdef __GNUC__
#ifdef __MORPHOS__
#include <emul/emulinterface.h>
#include <emul/emulregs.h>
#include <ppcinline/exec.h>
#define REG(reg,arg) arg
#define ASM
#ifdef __saveds
#undef __saveds
#endif
#define __saveds
#ifdef __stdargs
#undef __stdargs
#endif
#define __stdargs
#ifdef __aligned
#undef __aligned
#endif
#define __aligned
#else
#define REG(reg,arg) arg __asm(#reg)
#define LIB
#define ASM
#endif
#else
#define REG(reg,arg) register __ ## reg arg
#define LIB __saveds __asm
#define ASM __asm
#endif

#endif
