#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define HASH_TABLE_SIZE 13 // ��ϣ��Ĵ�СӦ�Ǹ����� 
struct mapping 
{ 
  void *key; 
  void *data; 
} hash_table[HASH_TABLE_SIZE]; 

unsigned int RSHash (char *str) 
{ 
  unsigned int b = 378551; 
  unsigned int a = 63689; 
  unsigned int hash =      0  ; 

  while (*str) 
    { 
      hash = hash * a + (*str++); 
      a *= b; 
    } 
  return (hash & 0x7FFFFFFF); 
} 

int main () 
{ 
  char *str = "we are the world!"; 
  char *filename = "myfile.txt"; 
  unsigned int hash_offset; 
  // ��ʼ����ϣ�� 
  memset (hash_table, 0x0, sizeof (hash_table)); 

  // ���ַ��������ϣ�� . 
  hash_offset = RSHash (str) % HASH_TABLE_SIZE; 
  hash_table[hash_offset].key = str; 
  hash_table[hash_offset].data = filename; 

  // ���� str �Ƿ������ hash_table. 
  hash_offset = RSHash (str) % HASH_TABLE_SIZE; 
  if (hash_table[hash_offset].key) 
        printf ("string '%s' exists in the file %s.\n", str, hash_table[hash_offset].data); 
  else 
        printf ("string '%s' does not exist.\n", str);

  return 0;
} 
