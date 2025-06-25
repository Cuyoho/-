#ifndef __KEY_H
#define __KEY_H

#include "sys.h"  // ?? PCin ???

// ???????
#define KEY_LEFT   PCin(8)   // K3
#define KEY_RIGHT  PCin(9)   // K4

// ?????
#define KEY_NONE        0
#define KEY_LEFT_PRES   2
#define KEY_RIGHT_PRES  3

void KEY_Init(void);
u8 KEY_Scan(void);

#endif
