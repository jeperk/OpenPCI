#ifndef PCIBusH
#define PCIBusH

// VendorName, DeviceName ...etc
#include "pcihdr.h"

char ver[]="$VER: OpenPciInfo 8/16/32bit HexDump PCI config v1.7 03.05.2006 by Titan";

int VendorName(unsigned short VendID,char *VendorShort,char *VendorFull);
int DeviceName(unsigned short VendID,unsigned short DevID,char *DevName,char *DevNameDesc);

#endif /* PCIBusH*/

