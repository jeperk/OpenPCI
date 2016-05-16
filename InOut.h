
#include <string.h>

#include "debug.h"

#define inline __inline

static inline
unsigned char hinb(unsigned long Addr)
{
/*
		moveq #0,d0
		move.b (a0),d0
		rts
*/
		DEBUG( dprintf("0x%08lx=hinb(0x%08lx)\n",*(unsigned char *)Addr,Addr) );
		return( *(unsigned char *)Addr );
}

static inline		
void houtb(unsigned char value, unsigned long Addr)
{
/*
		move.b d0,(a0)
		rts
*/
		DEBUG( dprintf("houtb(value=0x%08lx,addr=0x%08lx\n",value,Addr) );
		*(unsigned char *)Addr=value;
}

static inline		
unsigned short hinw(unsigned long Addr)
{
/*
		moveq #0,d0
		move.w (a0),d0
		rts
*/
		DEBUG( dprintf("0x%08lx=hinw(0x%08lx)\n",*(unsigned short *)Addr,Addr) );
		return( *(unsigned short *)Addr );
}

static inline		
void houtw(unsigned short value, unsigned long Addr)
{
/*
		move.w d0,(a0)
		rts
*/
		DEBUG( dprintf("houtw(val=0x%08lx,addr=0x%08lx\n",value,Addr) );
		*(unsigned short *)Addr=value;
}

static inline		
unsigned long hinl(unsigned long Addr)
{
/*
		moveq #0,d0
		move.l (a0),d0
		rts
*/
		DEBUG( dprintf("0x%08lx=hinl(0x%08lx)\n",*(unsigned long *)Addr,Addr) );
		return( *(unsigned long *)Addr );
}

static inline		
void houtl(unsigned long value, unsigned long Addr)
{
/*
		move.l d0,(a0)
		rts
*/
		DEBUG( dprintf("houtl(val=0x%08lx,addr=0x%08lx\n",value,Addr) );
		*(unsigned long *)Addr=value;
}

static inline		
void memcpyl(void *source, void *dest, unsigned long taille)
{
/*
		lsr		#2,d0	; On divise d0 par 4
boucle:
		move.l	(a0)+,(a1)+
		dbf		d0,boucle
		rts
*/
/*
		//unsigned long tailleOrig=taille;
		long *destp=dest;
      long *sourcep=source;
      taille>>=2;
		
		do
		{
			*destp++=*sourcep++;
		}while(--taille);
*/
		memcpy(dest,source,taille);		
		//CopyMem(source,dest,taille);
			
}





/* C Version */
/*
//extern	inline unsigned char hinb(unsigned long Addr);
unsigned char ASM hinb(REG(a0,unsigned long Addr));
void ASM houtb(REG(d0,unsigned char value), REG(a0,unsigned long Addr));
unsigned short ASM hinw(REG(a0,unsigned long Addr));
void ASM houtw(REG(d0,unsigned short value), REG(a0,unsigned long Addr));
unsigned long ASM hinl(REG(a0,unsigned long Addr));
void ASM houtl(REG(d0,unsigned long value), REG(a0,unsigned long Addr));
void ASM memcpyl( REG(a0,void *source), REG(a1,void *dest), REG(d0,unsigned long taille));
*/

/*
unsigned char hinb(unsigned long Addr);
void houtb(unsigned char value,unsigned long Addr);
unsigned short hinw(unsigned long Addr);
void houtw(unsigned short value, unsigned long Addr);
unsigned long hinl(unsigned long Addr);
void houtl(unsigned long value, unsigned long Addr);
void memcpyl(void *source, void *dest, unsigned long taille);
*/

/*
#define hinb(Addr) ( *(unsigned char *)Addr)
#define houtb(value, Addr) *(unsigned char *)Addr=value
#define hinw(Addr) ( *(unsigned short *)Addr )
#define houtw(value, Addr) *(unsigned short *)Addr=value
#define hinl(Addr) ( *(unsigned long *)Addr )
#define memcpyl(source, dest, taille) 									 taille>>=2\		
																					 do{\
																					 *dest++=*source++\
																					 }while(--taille)

*/
/* ASM 68k Version */
/*
extern	unsigned char __asm hinb(register __a0 unsigned long Addr);
extern   void __asm houtb(register __d0 unsigned char value, register __a0 unsigned long Addr);
extern	unsigned short __asm hinw(register __a0 unsigned long Addr);
extern	void __asm houtw(register __d0 unsigned short value, register __a0 unsigned long Addr);
extern	unsigned long __asm hinl(register __a0 unsigned long Addr);
extern	void __asm houtl(register __d0 unsigned long value, register __a0 unsigned long Addr);

extern	void __asm memcpyl( register __a0 void *source , register __a1 void *dest, register __d0 unsigned long taille);
*/

// outx(source,destination)