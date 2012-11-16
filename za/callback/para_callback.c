#include "para_callback.h"

void speak(callback_t func, void *variable)
{
  func(variable);
}
