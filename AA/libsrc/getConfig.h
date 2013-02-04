#ifndef __get_config__
#define __get_config__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include "xmlStruct.h"

int getConfig(char *xmlFilename, xmlStruct *xmlStructname);

#endif
