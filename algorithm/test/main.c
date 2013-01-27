#include <stdio.h>
#include <string.h>

typedef struct stu {
  int age;
  char name[20];
}stu;

int main()
{
  stu stu1;
  stu1.age = 12;
  strcpy(stu1.name, "bill");
  
  stu stu2 = stu1;
  printf("%d:%s\n", stu2.age, stu2.name);
  return 0;
}
