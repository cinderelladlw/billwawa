/*
 *
 * Name:	�����ͨ��������linux�ں˷�װ����C��
 * Auther:	chishaxie
 * Date:	2012.7.29
 *
 * Description:	log(n)�Ĳ��롢ɾ������ѯ��������������
 *
 */
#ifndef _RBTREE_CONTAINER_H_
#define _RBTREE_CONTAINER_H_

#include "rbtree.h"

typedef struct
{
	struct rb_node rb_node; //rbtree�ں˽ṹ������Ϊ�׸��ֶΣ�
	size_t dlen; //data�ĳ���
	void *key; //ָ�������������
	unsigned char *data; //ָ��ֵ
} rbtree_container_node; //�ڵ�

/* �ȽϺ��� key1 - key2 Ϊ��С�������� */
typedef int (*key_compare)(void *key1, void *key2);

typedef struct
{
	struct rb_root root; //rbtree�ں˽ṹ
	size_t klen; //key�ĳ��ȣ�����key��
	key_compare compare; //key�ıȽϺ���
} rbtree_container; //����

/* ���ڵ�����key ������Ϊ���ڵ�ָ�룬key��ʵ�����ͣ�ֵ��*/
#define rbtree_container_node_set_key(pnode,type,value) (*((type*)((pnode)->key)) = (value))

/*
 * ��������
 */

/* ��ʼ�� */
void rbtree_container_init(rbtree_container *tree, size_t key_length, key_compare key_compare_function);

/* ���� �����򷵻�NULL�� */
rbtree_container_node* rbtree_container_search(rbtree_container *tree, void *key);

/* ���� ���ɹ�����0�����ظ�����-1�� */
int rbtree_container_insert(rbtree_container *tree, rbtree_container_node *cont);

/* ɾ�� ���ɹ�����ɾ���˵Ľڵ㣬key�����ڷ���NULL�� */
rbtree_container_node *rbtree_container_delete(rbtree_container *tree, void *key);

/* �滻 ���ɹ����ر��滻���Ľڵ㣬cont��key�������򷵻�NULL�� */
rbtree_container_node *rbtree_container_replace(rbtree_container *tree, rbtree_container_node *cont);

/*
 * ������ �����򷵻�NULL��
 */

/* ��ȡ�����Ŀ�ʼ�ڵ� */
rbtree_container_node *rbtree_container_first(rbtree_container *tree);

/* ��ȡ�����Ľ����ڵ� */
rbtree_container_node *rbtree_container_last(rbtree_container *tree);

/* ��ȡ��һ���ڵ㣨��ǰ������ */
rbtree_container_node *rbtree_container_next(rbtree_container_node *cont);

/* ��ȡ��һ���ڵ㣨�������� */
rbtree_container_node *rbtree_container_prev(rbtree_container_node *cont);

/* ֱ��ɾ���ڵ㣨���뱣֤cont��tree���棬�������δ֪���� */
void rbtree_container_erase(rbtree_container *tree, rbtree_container_node *cont);

/*
 * �ڴ����
 */

 /* ���ڵ�����ڴ棨��Ч���ڵ��dlen�Ѹ�ֵ��key��data��λ���Ѿ����غã�ֱ���ü��ɣ� */
rbtree_container_node *rbtree_container_node_malloc(rbtree_container *tree, size_t data_length);

/* ���ڵ���������ڴ棬Ҫ�����ݲ��ֶ�������Ч���ڵ��dlen�Ѹ�ֵ��key��data��λ���Ѿ����غã�ֱ���ü��ɣ� */
rbtree_container_node *rbtree_container_node_array_malloc(rbtree_container *tree,
	size_t data_length, size_t array_length);

/* �ͷŽڵ���ڴ棨�� rbtree_container_node_malloc �� rbtree_container_node_malloc_array ƥ��ʹ�ã� */
void rbtree_container_node_free(rbtree_container_node *tree_node);

#endif
