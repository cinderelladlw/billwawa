#include <cstdlib>
#include <iostream>
#include <deque>
#include <algorithm>
 
using namespace std;
 
const int size=10;
typedef struct node                                 //霍夫曼?????
{
    unsigned key;                           //保存?值
    node* lchild;                           //左孩子指?
    node* rchild;                           //右孩子指?
}node;
deque<node*> forest;
deque<bool> code;                           //此?也可使用bitset
node* ptr;                   
int frequency[size]={0};
 
void printCode(deque<bool> ptr);            //用於?出霍夫曼??
 
bool compare( node* a, node* b)
{
return a->key < b->key;
}
int main(int argc, char *argv[])
{
    for (int i=0;i<size;i++)
    {
        cin>>frequency[i];                  //?入10??值
        ptr=new node;
        ptr->key=frequency[i];
        ptr->lchild=NULL;
        ptr->rchild=NULL;
        forest.push_back(ptr);
    }//形成森林，森林中的每一棵?都是一???
 
    //?森林?建霍夫曼?
    for (int i=0;i<size-1;i++)
    {
                sort(forest.begin(),forest.end(),compare);
                ptr=new node;
                //以下代?使用下?索引?列元素，具有?在危?，使用??注意
                ptr->key=forest[0]->key+forest[1]->key;
                ptr->lchild=forest[0];
                ptr->rchild=forest[1];
                forest.pop_front();
                forest.pop_front();
                forest.push_back(ptr);
        }
    ptr=forest.front();//ptr是一?指向根的指?
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
