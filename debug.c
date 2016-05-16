/*
 * $Id: debug.c,v 1.2 2002/08/22 16:07:25 titan Exp $
 */

#include "debug.h"

/*
    To unactivate DEBUG without a full recompile, make change here
*/
void debugfunc(char *ptr)
{
  dprintf(ptr);
}
