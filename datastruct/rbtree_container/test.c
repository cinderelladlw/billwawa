#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rbtree_container.h"

int compare(void *key1, void *key2)
{
	return *((int*)key1) - *((int*)key2); 
}

int main(void)
{
	rbtree_container tree;
	rbtree_container_node *pc, *tpc;
	int ret, find, erase, replace;
	
	rbtree_container_init(&tree, sizeof(int), compare);
	
	printf("rbtree_container test go ... \n\n");
	
	/*
	 * 插入测试
	 */
	pc = rbtree_container_node_malloc(&tree, 100);
	rbtree_container_node_set_key(pc, int, 1); //*((int*)(pc->key)) = 1;
	strcpy((char*)(pc->data), "hello world 1");
	ret = rbtree_container_insert(&tree, pc);
	printf("insert 1 ret = %d\n", ret);

	pc = rbtree_container_node_malloc(&tree, 100);
	rbtree_container_node_set_key(pc, int, 2);
	strcpy((char*)(pc->data), "hello world 2");
	ret = rbtree_container_insert(&tree, pc);
	printf("insert 2 ret = %d\n", ret);
	
	pc = rbtree_container_node_malloc(&tree, 100);
	rbtree_container_node_set_key(pc, int, 4);
	strcpy((char*)(pc->data), "hello world 4");
	ret = rbtree_container_insert(&tree, pc);
	printf("insert 4 ret = %d\n", ret);
	
	pc = rbtree_container_node_malloc(&tree, 100);
	rbtree_container_node_set_key(pc, int, 3);
	strcpy((char*)(pc->data), "hello world 3");
	ret = rbtree_container_insert(&tree, pc);
	printf("insert 3 ret = %d\n", ret);
	
	ret = rbtree_container_insert(&tree, pc);
	printf("insert 3 ret = %d\n", ret);
	
	printf("\n");
	/********************************************************/
	
	/*
	 * 查找测试
	 */
	find = 6;
	printf("find key %d\n", find);
	pc = rbtree_container_search(&tree, &find);
	if (pc != 0)
		printf("  key %d pc data: %s\n", find, (char*)(pc->data));
	else
		printf("  no find %d\n", find);
	
	find = 3;
	printf("find key %d\n", find);
	pc = rbtree_container_search(&tree, &find);
	if (pc != 0)
		printf("  key %d pc data: %s\n", find, (char*)(pc->data));
	else
		printf("  no find %d\n", find);
		
	printf("\n");
	/********************************************************/
	
	/*
	 * 节点删除测试
	 */
	erase = 3;
	printf("erase key %d\n", erase);
	pc = rbtree_container_delete(&tree, &erase);
	if (pc != 0) {
		printf("  erase key %d data: %s\n", erase, (char*)(pc->data));
		rbtree_container_node_free(pc);
	}
	else
		printf("  no erase %d\n", erase);
	
	find = 3;
	printf("find key %d\n", find);
	pc = rbtree_container_search(&tree, &find);
	if (pc != 0)
		printf("  key %d pc data: %s\n", find, (char*)(pc->data));
	else
		printf("  no find %d\n", find);
	
	printf("\n");
	/********************************************************/
	
	/*
	 * 节点更新替换测试
	 */
	replace = 2;
	printf("replace key %d\n", replace);
	pc = rbtree_container_node_malloc(&tree, 100);
	rbtree_container_node_set_key(pc, int, 2);
	strcpy((char*)(pc->data), "this is replace key 2");
	pc = rbtree_container_replace(&tree, pc);
	if (pc != 0)
	{
		printf("  replace key %d ret = %p, data: %s\n", replace, pc, (char*)(pc->data));
		rbtree_container_node_free(pc);
	}
	else
	{
		printf("  replace key %d failed\n", replace);
	}
	
	find = 2;
	printf("find key %d\n", find);
	pc = rbtree_container_search(&tree, &find);
	if (pc != 0)
		printf("  key %d pc data: %s\n", find, (char*)(pc->data));
	else
		printf("  no find %d\n", find);
		
	replace = 6;
	printf("replace key %d\n", replace);
	pc = rbtree_container_node_malloc(&tree, 100);
	rbtree_container_node_set_key(pc, int, 6);
	strcpy((char*)(pc->data), "this is replace key 6");
	pc = rbtree_container_replace(&tree, pc);
	if (pc != 0)
	{
		printf("  replace key %d ret = %p, data: %s\n", replace, pc, (char*)(pc->data));
		rbtree_container_node_free(pc);
	}
	else
	{
		printf("  replace key %d failed\n", replace);
	}
		
	printf("\n");
	/********************************************************/
	
	/*
	 * 迭代器测试
	 */
	
	pc = rbtree_container_first(&tree);
	while (pc)
	{
		printf("key %d, data: %s\n", *((int*)(pc->key)), (char*)(pc->data));
		pc = rbtree_container_next(pc);
	}
	
	printf("\n");
	
	pc = rbtree_container_last(&tree);
	while (pc)
	{
		printf("key %d, data: %s\n", *((int*)(pc->key)), (char*)(pc->data));
		pc = rbtree_container_prev(pc);
	}
	
	printf("\n");
	/********************************************************/
	
	/*
	 * 迭代器删除测试
	 */
	
	pc = rbtree_container_first(&tree);
	while (pc)
	{
		printf("key %d, data: %s (then delete)\n", *((int*)(pc->key)), (char*)(pc->data));
		tpc = pc;
		pc = rbtree_container_next(pc);
		rbtree_container_erase(&tree, tpc);
		rbtree_container_node_free(tpc);
	}
	
	printf("\n");
	
	find = 1;
	printf("find key %d\n", find);
	pc = rbtree_container_search(&tree, &find);
	if (pc != 0)
		printf("  key %d pc data: %s\n", find, (char*)(pc->data));
	else
		printf("  no find %d\n", find);
		
	find = 2;
	printf("find key %d\n", find);
	pc = rbtree_container_search(&tree, &find);
	if (pc != 0)
		printf("  key %d pc data: %s\n", find, (char*)(pc->data));
	else
		printf("  no find %d\n", find);
		
	find = 4;
	printf("find key %d\n", find);
	pc = rbtree_container_search(&tree, &find);
	if (pc != 0)
		printf("  key %d pc data: %s\n", find, (char*)(pc->data));
	else
		printf("  no find %d\n", find);
		
	printf("\n");
	/********************************************************/
	
	printf("rbtree_container test end.\n");
		
	return 0;
} 
