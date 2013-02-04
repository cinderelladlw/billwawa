#ifndef __xml_struct__
#define __xml_struct__

typedef struct xmlstruct xmlStruct;
struct xmlstruct {
  char localip[15 + 1];
  char localport[5 + 1];
  char remoteip[15 + 1];
  char remoteport[5 + 1];
};

#endif
