#include "errors.h"
#include <sqlite3.h>


int main (int argc, char *argv[])
{
  struct timeval tv;
  int seconds;
  char line[128];
  char message[64];
  int  message2;
  int  message3;
   
  while (1) {
    printf ("SQLite> ");
    if (fgets (line, sizeof (line), stdin) == NULL) exit (0);
    if (strlen (line) <= 1) continue;

    if (sscanf (line, "%d %s %d %d",&seconds, message, &message2, &message3) < 4) {
      fprintf (stderr, "Bad command\n");
    } 
    else {
      //sleep (seconds);
      sleep (2);
      printf ("(%d) %s %d %d\n", seconds, message, message2, message3);
    }
  }
}
