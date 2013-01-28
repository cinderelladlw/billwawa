#include <stdio.h>

struct stu {
  int id;
  char name[23];
};

int main()
{
  struct stu sb;
  sb.id = 23;
  sb.name = "bill";
  //strcpy(sb.name, "bill");
  printf(":%d\t%s\n", sb.id, sb.name);
  return 0;
}
