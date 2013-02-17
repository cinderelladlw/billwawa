#ifndef _PLUGIN_H_
#define _PLUGIN_H_

typedef struct{
    char name[64];
    char path[256];
    char entry[128];
    int version;
}Plugin;

#endif
