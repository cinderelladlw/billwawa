#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*MessageHandler)();

typedef struct Handler {
  MessageHandler start_handle_message;
  MessageHandler end_handle_message;
} Handler;

void parse(char* message, Handler* handlers, int handler_count) 
{
  int i;
  for(i=0; i < handler_count; i++) {
    (handlers+i) -> start_handle_message();
  }
  for(i=0; i < handler_count; i++) {
    (handlers+i) -> end_handle_message();
  }
}

void _start_handle_message()
{
  printf("start_handle_message()..\n");
}

void _end_handle_message()
{
  printf("end_handle_message()..\n");
}

int main()
{
  Handler DataPrinter = {_start_handle_message, _end_handle_message}; 
  Handler DataPrinter2 = {_start_handle_message, _end_handle_message}; 
  Handler handlers[2] = { DataPrinter,DataPrinter2 };
  
  parse(NULL, handlers, sizeof(handlers)/sizeof(handlers[0]));

  return 0;
}



