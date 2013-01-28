#include <cstdlib>
#include <iostream>
#include <deque>
#include <algorithm>
 
using namespace std;
 
const int size=10;
typedef struct node                                 //������?????
{
    unsigned key;                           //����?ֵ
    node* lchild;                           //����ָ?
    node* rchild;                           //�Һ���ָ?
}node;
deque<node*> forest;
deque<bool> code;                           //��?Ҳ��ʹ��bitset
node* ptr;                   
int frequency[size]={0};
 
void printCode(deque<bool> ptr);            //���?��������??
 
bool compare( node* a, node* b)
{
return a->key < b->key;
}
int main(int argc, char *argv[])
{
    for (int i=0;i<size;i++)
    {
        cin>>frequency[i];                  //?��10??ֵ
        ptr=new node;
        ptr->key=frequency[i];
        ptr->lchild=NULL;
        ptr->rchild=NULL;
        forest.push_back(ptr);
    }//�γ�ɭ�֣�ɭ���е�ÿһ��?����һ???
 
    //?ɭ��?��������?
    for (int i=0;i<size-1;i++)
    {
                sort(forest.begin(),forest.end(),compare);
                ptr=new node;
                //���´�?ʹ����?����?��Ԫ�أ�����?��Σ?��ʹ��??ע��
                ptr->key=forest[0]->key+forest[1]->key;
                ptr->lchild=forest[0];
                ptr->rchild=forest[1];
                forest.pop_front();
                forest.pop_front();
                forest.push_back(ptr);
        }
    ptr=forest.front();//ptr��һ?ָ�����ָ?
    printCode(code);
    //system("pause");
   
    while (1);
    return EXIT_SUCCESS;
}
 
void printCode(deque<bool> ptr)
{
        //deque<bool>
        for (int i=0;i<ptr.size();i++)
        {
                if(ptr[i])
                        cout<<"1";
                else
                        cout<<"0";
        }
}
