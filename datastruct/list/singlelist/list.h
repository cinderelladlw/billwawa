#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "node.h"

pNode listInit(pNode l);
int listCreate(pNode l, int len);
int listPrint(pNode l);



#endif



