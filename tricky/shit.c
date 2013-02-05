#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _state {
  unsigned char input[13];
  unsigned char output[13];
  int ining;
  int outing;
  unsigned short bi_buf;
  int bi_valid;
} state;

void send_bits(state *s, unsigned char value, int len)
{
  int rm = 16 - s->bi_valid;
  if(len > rm)
  {
    unsigned short val = value;
    s->bi_buf <<= rm;
    s->bi_buf |=  val>>(8-rm);
    //MSB first
    s->output[s->outing++] = (unsigned char)((s->bi_buf) >> 8);
    s->output[s->outing++] = (unsigned char)((s->bi_buf) & 0xff);
    
    s->bi_buf = val << rm;
    s->bi_valid = len - rm;
  }
  else
  {
    s->bi_buf <<= len;
    s->bi_buf |= value & (1<<len)-1;
    s->bi_valid += len;
  }
  return;
}

void fflush_bits(state *s)
{
  if(s->bi_valid > 8)
  {
    //MSB first
    s->output[s->outing++] = (unsigned char)((s->bi_buf) >> 8);
    s->output[s->outing++] = (unsigned char)((s->bi_buf) & 0xff);
  }
  else
  {
    s->output[s->outing++] = (unsigned char)((s->bi_buf) & ((1<<s->bi_valid) - 1));
  }
  s->bi_buf = 0;
  s->bi_valid = 0;
  return;
}

int main()
{
  state *s;
  s = calloc(1, sizeof(state));

  strcpy(s->input, "123456789abc");

  unsigned char ch;
  
  //删除一天
  ch = s->input[s->ining++];
  send_bits(s, ch, 7); 
  
  while(s->ining < strlen(s->input))
  {
    ch = s->input[s->ining++];
    send_bits(s, ch, 8);
  }
  
  //新增一天, 假设1
  if(1)
  {
    send_bits(s, 0x8, 1);
  }
  else
  {
    send_bits(s, 0x0, 1);
  }
  
  //清空buf
  fflush_bits(s);
  
  int i;
  for(i = 0; i < strlen(s->input); i++)
  {
    printf("%02hhx ", s->output[i]);
  }
  printf("%02hhx\n", s->output[i]);
    
  return(0);
}
