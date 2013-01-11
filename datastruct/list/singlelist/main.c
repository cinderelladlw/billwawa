#include "list.h"

int main()
{
  pNode sx;
  sx = listInit(sx);  
  listCreate(sx, 3);
  listPrint(sx);
   
  return 0;
}
