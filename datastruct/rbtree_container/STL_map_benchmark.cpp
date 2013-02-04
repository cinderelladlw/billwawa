#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <sys/time.h>

#include <map>

using namespace std;

#define TEST_SIZE 100000

#define SRAND 0x1234
//#define SRAND (time(NULL))

int main(void)
{
	map<int, int> tree;
	pair<map<int, int>::iterator, bool> ret;
	map<int, int>::iterator cur;
	int i, insert_failed, find_failed, tree_size;
	struct timeval begin, end;
	
	printf("STL_map benchmark go ... \n\n");
	
	srand(SRAND);
	
	/*
	 * 初始化
	 */
	
	pair<int, int> kvs[TEST_SIZE];
	
	for(i=0; i<TEST_SIZE; i++)
	{
		kvs[i].first = rand();
	}
	
	/********************************************************/
	
	/*
	 * 插入测试
	 */
	
	printf("random insert %d times...\n", TEST_SIZE);
	
	insert_failed = 0;
	
	gettimeofday(&begin, NULL);
	
	for(i=0; i<TEST_SIZE; i++)
	{
		ret = tree.insert(kvs[i]);
		if (!ret.second)
			insert_failed ++;
	}
	
	gettimeofday(&end, NULL);
	
	printf("  insert_failed: %d\n", insert_failed);
	printf("  time: %ldus\n", 1000000*(end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec));
	
	printf("\n");
	/********************************************************/
	
	/*
	 * 查找测试
	 */
	
	printf("random find %d times...\n", TEST_SIZE);
	 
	find_failed = 0;
	
	gettimeofday(&begin, NULL);
	
	for(i=0; i<TEST_SIZE; i++)
	{
		cur = tree.find(rand());
		if (cur == tree.end())
			find_failed ++;
	}
	
	gettimeofday(&end, NULL);
	
	printf("  find_failed: %d\n", find_failed);
	printf("  time: %ldus\n", 1000000*(end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec));
		
	printf("\n");
	/********************************************************/
	
	/*
	 * 迭代器测试
	 */
	 
	printf("iterator...\n");
	 
	tree_size = 0;
	
	gettimeofday(&begin, NULL);
	
	cur = tree.begin();
	while (cur != tree.end())
	{
		tree_size ++;
		cur ++;
	}
	
	gettimeofday(&end, NULL);
	
	printf("  tree_size: %d\n", tree_size);
	printf("  time: %ldus\n", 1000000*(end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec));
	
	printf("\n");
	/********************************************************/
	
	printf("STL_map benchmark end.\n");
		
	return 0;
} 
