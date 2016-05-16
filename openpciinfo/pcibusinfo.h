#ifndef PCIBusH
#define PCIBusH

// VendorName, DeviceName ...etc
#include "pcihdr.h"

char ver[]="$VER: OpenPciInfo v1.5 12.03.2005 by Titan";

int VendorName(unsigned short VendID,char *VendorShort,char *VendorFull);
int DeviceName(unsigned short VendID,unsigned short DevID,char *DevName,char *DevNameDesc);

#endif /* PCIBusH*/

