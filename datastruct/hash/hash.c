#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define HASH_TABLE_SIZE 13 // 哈希表的大小应是个质数 
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
  // 初始化哈希表 
  memset (hash_table, 0x0, sizeof (hash_table)); 

  // 将字符串插入哈希表 . 
  hash_offset = RSHash (str) % HASH_TABLE_SIZE; 
  hash_table[hash_offset].key = str; 
  hash_table[hash_offset].data = filename; 

  // 查找 str 是否存在于 hash_table. 
  hash_offset = RSHash (str) % HASH_TABLE_SIZE; 
  if (hash_table[hash_offset].key) 
        printf ("string '%s' exists in the file %s.\n", str, hash_table[hash_offset].data); 
  else 
        printf ("string '%s' does not exist.\n", str);

  return 0;
} 
