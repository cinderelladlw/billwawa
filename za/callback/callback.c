#include "para_callback.h"
#include <stdio.h>

void speakint(void *variable)
{
  printf("%s%d\n","I am a integer variable: ",*((int *)variable));
}
void speakfloat(void* variable)
{
  printf("%s%f\n","I am a float variable: ",*((float *)variable));
}

int main()
{
  int variable_int = 100;
  float variable_float = 100.9;
  speak(speakint, (void*)&variable_int);
  speak(speakfloat, (void*)&variable_float);
}
