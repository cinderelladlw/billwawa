/*
 *	AVL Tree Implementation -- Non-recursive
 *
 *	Guanpeng Xu
 *	<leo_virgo@263.net>
 *
 */

#include <stdlib.h>

/*
 * State information stored in each node in AVL tree.
 * AVLL + AVLR must be AVLB.
 * AVLB must be zero, otherwise modify ALLOC_AVL_TNODE.
 */
enum STATE__ {
	AVLL = -1,
	AVLB,
	AVLR,
};

/*
 * Constant for auto-array.
 */
enum MEM__ {
	MGROW = 2,		/* growing scale: must be greater than 1 */
	MINIT = 32,		/* initial amount: must be greater than 0 */
};

/*
 * Node in AVL tree.
 */
struct avl_tnode {
	int val;		/* value stored in a node */
	struct avl_tnode *left;	/* left child */
	struct avl_tnode *right;/* right child */
	signed char balns;	/* balance information */
};

/*
 * Structure for saving root nodes and path
 * information in non-recursive algorighm.
 */
struct avl_rnode {
	struct avl_tnode *p;	/* node in AVL tree */
	signed char lr;		/* is inserted child left or right? */
};

/*
 * Structure for saving information about
 * an AVL tree
 */
struct avl_tree {
	struct avl_tnode *root;	/* root of the AVL tree */
	struct avl_rnode *rnodes;/* root sequence when adding/deleting */
	int n;			/* number of RNODES */
	int max;		/* maximum number of RNODES */
};

/*
 * Allocate a new node that will be inserted into an AVL
 * tree, with value field N.
 * Return the allocated node on success, or NULL if failed.
 */
inline struct avl_tnode *alloc_avl_tnode(int n)
{
	struct avl_tnode *p;

	if ((p = (struct avl_tnode *) calloc(1, sizeof *p)) == NULL)
		return NULL;
	p->val = n;
/* 	p->balns = AVLB; */
	return p;
}

/*
 * Get the next memory location for auto-array *AP.
 * The size of each element in this auto-array is U.
 * This auto-array has *AN elements, and the maximum
 * number of elements is *AMAX.
 * If *AP is NULL, try to allocate new memory for it.
 * If the maximum is reached, grow as needed.
 * Return a pointer to the next element on success,
 * or NULL if failed.
 */
static inline void *aanext(void **ap, size_t u, int *an, int *amax)
{
	void *p;
	int max;

	if (*ap == NULL) {
		*an = 0;
		if ((*ap = malloc(u * MINIT)) == NULL)
			return NULL;
		*amax = MINIT;
	}

	if (*an >= *amax) {
		max = *amax * MGROW;
		if ((p = realloc(*ap, u * max)) == NULL)
			return NULL;
		*ap = p;
		*amax = max;
	}

	return (void *)((char *)*ap + u * (*an)++);
}


static inline struct avl_rnode *avl_rnnext(struct avl_tree *tree)
{
	return (struct avl_rnode *) aanext((void **) &tree->rnodes,
					   sizeof *tree->rnodes,
					   &tree->n, &tree->max);
}

/*
 * Allocate and initialize one structure for a new AVL tree.
 */
inline struct avl_tree *alloc_avl_tree(void)
{
	struct avl_tree *p;

	if ((p = (struct avl_tree *) calloc(1, sizeof *p)) == NULL)
		return NULL;
	return p;
}

static inline void avl_update_root(struct avl_tnode **root,
				   struct avl_tnode *newroot,
				   struct avl_rnode *r,
				   struct avl_rnode *rb)
{
	struct avl_rnode *rr;

	if (r > rb) {
		if ((rr = r-1)->lr == AVLL)
			rr->p->left = newroot;
		else
			rr->p->right = newroot;
	} else
		*root = newroot;
}

static inline void avl_ll(struct avl_tnode *pp,
			  struct avl_tnode *p1,
			  struct avl_tnode **root,
			  struct avl_rnode *r,
			  struct avl_rnode *rb)
{
	struct avl_tnode *p;

	p = p1->right;
	p1->right = pp;
	pp->left = p;
	avl_update_root(root, p1, r, rb);
}

static inline void avl_rr(struct avl_tnode *pp,
			  struct avl_tnode *p1,
			  struct avl_tnode **root,
			  struct avl_rnode *r,
			  struct avl_rnode *rb)
{
	struct avl_tnode *p;

	p = p1->left;
	p1->left = pp;
	pp->right = p;
	avl_update_root(root, p1, r, rb);
}

static inline void avl_lr(struct avl_tnode *pp,
			  struct avl_tnode *p1,
			  struct avl_tnode *p2,
			  struct avl_tnode **root,
			  struct avl_rnode *r,
			  struct avl_rnode *rb)
{
	struct avl_tnode *p, *q;

	p = p2->left;
	q = p2->right;
	p2->left = p1;
	p2->right = pp;
	p1->right = p;
	pp->left = q;
	avl_update_root(root, p2, r, rb);
}

static inline void avl_rl(struct avl_tnode *pp,
			  struct avl_tnode *p1,
			  struct avl_tnode *p2,
			  struct avl_tnode **root,
			  struct avl_rnode *r,
			  struct avl_rnode *rb)
{
	struct avl_tnode *p, *q;

	p = p2->left;
	q = p2->right;
	p2->left = pp;
	p2->right = p1;
	pp->right = p;
	p1->left = q;
	avl_update_root(root, p2, r, rb);
}

static inline void avl_update_balns(struct avl_rnode *r,
				    struct avl_rnode *re)
{
	for (r++; r < re; r++)
		r->p->balns = r->lr;
}

/*
 * Insert a new node, TN, into AVL tree TREE.
 * Return pointer to the inserted node,
 * or NULL if failed.
 * If the value of TN exists in TREE, TN will
 * NOT be inserted and the pointer to the
 * existing node in the tree is returned.
 */
struct avl_tnode *avl_tree_add(struct avl_tree *tree, struct avl_tnode *tn)
{
	struct avl_rnode *r, *rb, *re, *r1, *r2;
	struct avl_tnode *p, *pp, *p1;

	/*
	 * insert node TN and record root nodes
	 */
	tree->n = 0;
	p = tree->root;
	while (p != NULL) {
		if ((r = avl_rnnext(tree)) == NULL)
			return NULL;
		r->p = p;
		if (p->val > tn->val) {
			r->lr = AVLL;
			p = p->left;
		} else if (p->val < tn->val) {
			r->lr = AVLR;
			p = p->right;
		} else
			return p;
	}

	if (tree->n == 0)
		return tree->root = tn;

	rb = tree->rnodes;
	re = &tree->rnodes[tree->n - 1];
	if (re->lr == AVLL)
		re->p->left = tn;
	else
		re->p->right = tn;

	/*
	 * find the smallest subtree to be rotated
	 */
	for (r = re; r >= rb; r--)
		if (r->p->balns != AVLB)
			break;

	/*
	 * all subtrees are balanced
	 */
	if (r < rb) {
		avl_update_balns(r, re + 1);
		goto finish;
	}

	pp = r->p;

	/*
	 * inserting make unbalanced subtree balanced
	 */
	if (r->lr + pp->balns == AVLB) {
		pp->balns = AVLB;
		avl_update_balns(r, re + 1);
		goto finish;
	}

	r1 = r + 1;

	/*
	 * LL rotation
	 */
	if (r->lr == AVLL && r1->lr == AVLL) {
		avl_ll(pp, r1->p, &tree->root, r, rb);
		pp->balns = AVLB;
		avl_update_balns(r1, re + 1);
		goto finish;
	}

	/*
	 * RR rotation
	 */
	if (r->lr == AVLR && r1->lr == AVLR) {
		avl_rr(pp, r1->p, &tree->root, r, rb);
		pp->balns = AVLB;
		avl_update_balns(r1, re + 1);
		goto finish;
	}

	p1 = r1->p;
	r2 = r + 2;

	/*
	 * special cases for LR/RL rotation
	 */
	if (r2 > re) {
		if (r->lr == AVLL)
			avl_lr(pp, p1, tn, &tree->root, r, rb);
		else
			avl_rl(pp, p1, tn, &tree->root, r, rb);
		pp->balns = p1->balns = AVLB;
		goto finish;
	}

	/*
	 * LR rotation
	 */
	if (r->lr == AVLL) {
		avl_lr(pp, p1, r2->p, &tree->root, r, rb);
		if (r2->lr == AVLL) {
			p1->balns = AVLB;
			pp->balns = AVLR;
		} else {
			p1->balns = AVLL;
			pp->balns = AVLB;
		}
		avl_update_balns(r2, re + 1);
		goto finish;
	}

	/*
	 * RL rotation
	 */
	/* if (r->lr == AVLR) */ {
		avl_rl(pp, p1, r2->p, &tree->root, r, rb);
		if (r2->lr == AVLL) {
			pp->balns = AVLB;
			p1->balns = AVLR;
		} else {
			pp->balns = AVLL;
			p1->balns = AVLB;
		}
		avl_update_balns(r2, re + 1);
		/* goto finish; */
	}
finish:
	return tn;
}

/*
 * Delete a node with the value field N from AVL
 * tree TREE. The node will be separated from the
 * tree, and the tree will be adjusted to keep
 * balanced.
 * Return pointer to the node with value field N.
 * If there is no such node in the tree or deleting
 * is failed because of memory allocation, return
 * NULL.
 */
struct avl_tnode *avl_tree_del(struct avl_tree *tree, int n)
{
	struct avl_rnode *r, *rr, *rb;
	struct avl_tnode *p, *q, *pp, *p1, *p2;
	int sn;

	/*
	 * search for the node
	 */
	tree->n = 0;
	p = tree->root;
	while (p != NULL) {
		/* leave a slot when P->VAL == N */
		if ((r = avl_rnnext(tree)) == NULL)
			return NULL;
		if (p->val == n)
			break;
		r->p = p;
		if (p->val > n) {
			r->lr = AVLL;
			p = p->left;
		} else {
			r->lr = AVLR;
			p = p->right;
		}
	}

	if (p == NULL)
		return NULL;

	sn = tree->n;

	/*
	 * bootstrap
	 */

	p1 = p->right;

	/*
	 * the node to be deleted has no right child
	 */
	if (p1 == NULL) {
		avl_update_root(&tree->root, p->left, r, tree->rnodes);
		if (sn == 1)
			goto finish;
		goto rollback;
	}

	/*
	 * the node to be deleted has right child,
	 * but the right child has no left child
	 */
	if (p1->left == NULL) {
		p1->left = p->left;
		if (p->balns == AVLL) {
			/*
			 * Note: The meaning of PP, P1 and P2 within this
			 * "if" is different from the other part in this
			 * program.
			 */
			p2 = p->left;
			if (p2->balns == AVLB && p1->balns == AVLR) {
				avl_ll(p1, p2, &tree->root, r, tree->rnodes);
				p2->balns = AVLR;
				p1->balns = AVLL;
				goto finish;
			} else if (p2->balns == AVLL) {
				avl_ll(p1, p2, &tree->root, r, tree->rnodes);
				p2->balns = p1->balns = AVLB;
				goto rollback;
			} else {
				avl_lr(p1, p2, pp = p2->right, &tree->root, r, tree->rnodes);
				if (pp->balns == AVLB) {
					if (p2->balns == AVLR)
						p1->balns = p2->balns = AVLB;
					else
						p2->balns = pp->balns = AVLL;
				} else if (pp->balns == AVLL)
					p2->balns = pp->balns = AVLB;
				else {
					p2->balns = AVLL;
					p1->balns = pp->balns = AVLB;
				}
				goto rollback;
			}
		}
		avl_update_root(&tree->root, p1, r, tree->rnodes);
		if (p->balns == AVLB) {
			p1->balns = AVLL;
			goto finish;
		} else {
			if (p->left != NULL)
				p1->balns = AVLB;
			goto rollback;
		}
	}

	/*
	 * the node to be deleted has right child,
	 * and the right child has left child
	 */
	q = p1;
	while (q->left != NULL) {
		if ((r = avl_rnnext(tree)) == NULL)
			return NULL;
		r->p = q;
		r->lr = AVLL;
		q = q->left;
	}
	r++->p->left = q->right;
	avl_update_root(&tree->root, q, rr = &tree->rnodes[sn - 1], tree->rnodes);
	rr->p = q;
	rr->lr = AVLR;
	q->left = p->left;
	q->right = p1;
	q->balns = p->balns;
	goto rollback;

	/*
	 * rolling back
	 */
rollback:
	rb = tree->rnodes;
	while (--r >= rb) {
		pp = r->p;
		if (pp->balns == AVLB) {
			if (r->lr == AVLL) {
				pp->balns = AVLR;
				goto finish;
			} else {
				pp->balns = AVLL;
				goto finish;
			}
		} else if (pp->balns == AVLL) {
			if (r->lr == AVLL) {
				pp->balns = AVLB;
				continue;
			} else {
				if ((p1 = pp->left)->balns == AVLR) {
					avl_lr(pp, p1, p2 = p1->right, &tree->root, r, rb);
					if (p2->balns == AVLB) {
						p1->balns = pp->balns = AVLB;
						continue;
					} else if (p2->balns == AVLL) {
						p1->balns = AVLB;
						pp->balns = AVLR;
					} else {
						p1->balns = AVLL;
						pp->balns = AVLB;
					}
					p2->balns = AVLB;
				} else {
					avl_ll(pp, p1, &tree->root, r, rb);
					if (p1->balns == AVLB) {
						p1->balns = AVLR;
						pp->balns = AVLL;
						goto finish;
					} else
						p1->balns = pp->balns = AVLB;
				}
				continue;
			}
		} else {
			if (r->lr == AVLL) {
				if ((p1 = pp->right)->balns == AVLL) {
					avl_rl(pp, p1, p2 = p1->left, &tree->root, r, rb);
					if (p2->balns == AVLB) {
						pp->balns = p1->balns = AVLB;
						continue;
					} else if (p2->balns == AVLL) {
						pp->balns = AVLB;
						p1->balns = AVLR;
					} else {
						pp->balns = AVLL;
						p1->balns = AVLB;
					}
					p2->balns = AVLB;
				} else {
					avl_rr(pp, p1, &tree->root, r, rb);
					if (p1->balns == AVLB) {
						pp->balns = AVLR;
						p1->balns = AVLL;
						goto finish;
					} else
						pp->balns = p1->balns = AVLB;
				}
				continue;
			} else {
				pp->balns = AVLB;
				continue;
			}
		}
	}

finish:
	return p;
}

static void relse_avl(struct avl_tnode *p)
{
	if (p == NULL)
		return;
	relse_avl(p->left);
	relse_avl(p->right);
	free(p);
}

inline void relse_avl_tree(struct avl_tree *tree)
{
	relse_avl(tree->root);
	free(tree->rnodes);
}

#include <stdio.h>
#include <time.h>

void tree_trav(struct avl_tnode *t, int n)
{
	char s[256];

	if (t == NULL)
		return;
	tree_trav(t->left, n+1);
//	printf("%d\n", t->val);
	sprintf(s, "%%%ds%%d----------------------------->", n * 4);
	printf(s, "", t->val);
	if (t->balns == AVLB)
		printf("AVLB");
	else if (t->balns == AVLL)
		printf("AVLL");
	else
		printf("AVLR");
	printf("\n\n");
	tree_trav(t->right, n+1);
}

int main(int argc, char *argv[])
{
/* 	int x; */
/* 	FILE *fp; */
/* 	int op; */
/* 	struct avl_tree *tree; */
/* 	struct avl_tnode *p; */

/* 	setbuf(stdout, NULL); */
/* 	tree = alloc_avl_tree(); */
/* 	while (scanf(" %c", &op) > 0) { */
/* 		scanf(" %d", &x); */
/* 		if ((unsigned char) op == 'i') { */
/* 			if (avl_tree_add(tree, p = alloc_avl_tnode(x)) != p) */
/* 				free(p); */
/* 		} else */
/* 			free(avl_tree_del(tree, x)); */
/* 		if (tree->root != NULL) */
/* 			tree_trav(tree->root, 0); */
/* 	} */

	int x;
	int op;
	struct avl_tree *tree;
	struct avl_tnode *node;
	FILE *fp;
	clock_t before;
	double elapsed;

	if (argc == 2)
		fp = fopen(argv[1], "r");
	else
		fp = stdin;
	tree = alloc_avl_tree();
	before = clock();
	while (fscanf(fp, " %d", &x) > 0) {
//		printf("inserting %d\n", x);
		node = alloc_avl_tnode(x);
		avl_tree_add(tree, node);
/* 		tree_trav(tree->root, 0); */
/* 		if (fp != stdin) */
/* 			getchar(); */
	}
	elapsed = clock() - before;
	fprintf(stderr, "inserting: %.3f seconds\n",
		elapsed / CLOCKS_PER_SEC);
	before = clock();
//	tree_trav(tree->root, 0);
	while (tree->root != NULL) {
		free(avl_tree_del(tree, tree->root->val));
//		tree_trav(tree->root, 0);
	}
	elapsed = clock() - before;
	fprintf(stderr, "deleting: %.3f seconds\n",
		elapsed / CLOCKS_PER_SEC);
//	tree_trav(tree->root, 0);
	return 0;
}
