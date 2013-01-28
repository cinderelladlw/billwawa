#include <iostream>
#include <cstdlib>

using namespace std;
const int STACK_INIT_SIZE = 100;
const int INCREMENT = 10;

typedef struct BiTree
{
        struct BiTree *left;
        struct BiTree *right;
        int value;
}TreeNode;

typedef struct  Stack
{
        TreeNode *top;
        TreeNode *base;
        int SIZE;
}SqStack;

int init_stack(SqStack *s)
{
        s->base = (TreeNode *)malloc(STACK_INIT_SIZE*sizeof(TreeNode));
        if (s->base == NULL)
                cout<<"malloc memory failed"<<endl;

        s->top = s->base;
        s->SIZE = STACK_INIT_SIZE;

        return 0;
}

int main()
{
        SqStack *s = (SqStack *)malloc(sizeof(SqStack));
        init_stack(s);   
        //SqStack s;
        //init_stack(&s);
        //�˴�����ֶδ��󣬡�Program received signal SIGSEGV, Segmentation fault.��
        //����Ϊָ����main������δ����ֵ������init_stack��ʱ�ͻᷢ���δ���
        //�����������㷨ʵ���ж�ά���鴫��ʱ������ָ�����
        //�ɲ���SqStack s�� init_stack(&s);��������һ���󡣴�ţԽ��һ�ۿ������⡣�ڴ˱�ʾ��л
        return 0;
}
