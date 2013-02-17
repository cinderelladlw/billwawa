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
        //此处会出现段错误，“Program received signal SIGSEGV, Segmentation fault.”
        //是因为指针在main函数中未被赋值，传到init_stack中时就会发生段错误。
        //类似于我在算法实验中二维数组传参时所犯的指针错误。
        //可采用SqStack s； init_stack(&s);来消除这一错误。大牛越神一眼看出问题。在此表示感谢
        return 0;
}
