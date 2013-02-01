#include <iostream>
#include <stack>
using namespace std;

#define max(a,b) ((a)>(b)?(a):(b))
struct avlObject {
   int oid;
};
struct AvlNode{
   avlObject avlobj;
   int  height;
   AvlNode* lchild, *rchild;
   AvlNode():height(0),lchild(NULL),rchild(NULL){}
   AvlNode(avlObject k, int h, AvlNode* l, AvlNode* r):avlobj(k), height(h), lchild(l), rchild(r) {}
};
class AVLTree{
   private:
       AvlNode* _null;    //   �涨�Ŀս��
       AvlNode* root;     //   �����
       void left_single_rotate( AvlNode*& r );     //  ����ת
       void left_double_rotate( AvlNode*& r );     //  ��˫��ת
       void right_single_rotate( AvlNode*& r );    //  �ҵ���ת
       void right_double_rotate( AvlNode*& r );    //  ��˫��ת
       void erase_rotate_help( AvlNode*& r );      //  ɾ�������е���ת
       void insert_help( AvlNode*& r, avlObject avlobj );  //  ����
       void erase_help ( AvlNode*& r, int );               //  ɾ��
   public:
       AVLTree();
       void insert( avlObject avlobj );                 //  ��������
       void erase ( int oid );                 //  ɾ������
       void print(AvlNode *t,int layer);
       AvlNode* getroot();

};
AVLTree::AVLTree()
{
  _null = new AvlNode();
  root = _null;
}
AvlNode* AVLTree::getroot()
{
  return root;
}
void AVLTree::print(AvlNode *t,int layer)
{
  if(t == _null) 
    return;
  if(t->rchild) 
    print(t->rchild,layer+1);
  for(int i=0;i<layer;i++) 
    cout<<"   ";
  cout<<t->avlobj.oid<<endl;
  if(t->lchild) 
    print(t->lchild,layer+1);
}
//   ����תʵ��
void AVLTree::left_single_rotate( AvlNode* &r ){
   AvlNode* tmp= r->rchild;
   r->rchild= tmp->lchild;
   r->height= max( r->lchild->height, r->rchild->height )+ 1;
   tmp->lchild= r;
   r= tmp;
   r->height= max( r->lchild->height, r->rchild->height )+ 1;
}
//  �ҵ���תʵ��
void AVLTree::right_single_rotate( AvlNode*& r ){
   AvlNode* tmp= r->lchild;
   r->lchild= tmp->rchild;
   r->height= max( r->lchild->height, r->rchild->height )+ 1;
   tmp->rchild= r;
   r= tmp;
   r->height= max( r->lchild->height, r->rchild->height )+ 1;
}
//  ��˫��תʵ��
void AVLTree::left_double_rotate( AvlNode*& r ){
  right_single_rotate( r->rchild );
  left_single_rotate( r );
}
//  ��˫��תʵ��
void AVLTree::right_double_rotate( AvlNode*& r ){
  left_single_rotate( r->lchild );
  right_single_rotate( r );
}
void AVLTree::insert_help( AvlNode*& r, avlObject avlobj ){
  if( r == _null ) {
    r = new AvlNode( avlobj, 1, _null, _null );
    return;
  }
  if( avlobj.oid< r->avlobj.oid )
    insert_help( r->lchild, avlobj );
  else
    insert_help( r->rchild, avlobj );
  //������һ����ͬ����������Ĵ��� ,AVL��ֻ�����������
  //��������ת����ƽ��Ĳ���
  //���������ĸ߶ȣ���Ϊ���ӽ��󣬸߶ȿ�������
  r->height= max( r->lchild->height, r->rchild->height )+ 1;
  //�����������Ϊ��
  if( r->rchild!= _null ) {
    // �������ĸ߶ȼ���1�������������������ĸ߶ȣ�������ת
    if( r->lchild->height+ 1== r->rchild->rchild->height )
    left_single_rotate( r );
    // �������ĸ߶ȼ���1�������������������ĸ߶ȣ�����˫��ת
    else if( r->lchild->height+ 1== r->rchild->lchild->height )
    left_double_rotate( r );
  }
  //  �����������Ϊ��
  if( r->lchild!= _null ) {
    // �������ĸ߶ȼ���1�������������������ĸ߶ȣ����ҵ���ת
    if( r->rchild->height+ 1== r->lchild->lchild->height )
    right_single_rotate( r );
    // �������ĸ߶ȼ���1�������������������ĸ߶ȣ�����˫��ת
    else if( r->rchild->height+ 1== r->lchild->rchild->height )
    right_double_rotate( r );
  }
}
void AVLTree::insert( avlObject avlobj ){
  insert_help( root, avlobj ); 
}
void AVLTree::erase_rotate_help( AvlNode*& r ){
  //  �������߶ȱ��������߶ȴ�2
  if( r->rchild->height - r->lchild->height== 2 ) {
    // ������������������ĸ߶Ȳ��������������������ĸ߶���Ը�����ת
    if( r->rchild->lchild->height<= r->rchild->rchild->height )
      left_single_rotate( r );
    // ������������������ĸ߶ȴ������������������ĸ߶���Ը���˫��ת
    else
      left_double_rotate( r );
  }
  //  �������߶ȱ��������߶ȴ�2
  else if( r->lchild->height- r->rchild->height== 2  ){
    //  ������������������ĸ߶Ȳ��������������������ĸ߶���Ը��ҵ���ת
    if( r->lchild->rchild->height<= r->lchild->lchild->height )
      right_single_rotate( r );
    //  ������������������ĸ߶ȴ������������������ĸ߶���Ը���˫��ת
    else
    right_double_rotate( r );
  }
}
void AVLTree::erase_help( AvlNode*& r, int oid ){
  if ( r == _null ) 
    return;  //  û���ҵ�Ҫɾ���Ľ����ֱ���˳�
  if ( r->avlobj.oid == oid ) {
    if ( r->rchild == _null ) {
      AvlNode* tmp = r;
      r = r->lchild;
      delete tmp;
    } else {
      AvlNode* tmp= r->rchild;
      while( tmp->lchild!= _null ) {
        tmp= tmp->lchild;
      }
      r->avlobj= tmp->avlobj;
      erase_help( r->rchild, tmp->avlobj.oid );
      r->height= max( r->lchild->height, r->rchild->height )+ 1;
    }
    return ; //??????????????????????????????????????????????
  }
  if( oid < r->avlobj.oid )
    erase_help( r->lchild, oid );
  else
    erase_help( r->rchild, oid );

  //  ͬ����������һ����ͬ����������Ĵ��� ,AVL��ֻ�����������
  //  ��������ת����ƽ��Ĳ���
  //  �����߶�
  r->height= max( r->lchild->height, r->rchild->height )+ 1;
  //  �п������������аѽ��ɾ��������������ƽ��
  //  ���ȼ���������Ƿ��Ѿ�ƽ�⣬�� �����
  if( r->lchild!= _null )
  {
  erase_rotate_help( r->lchild );
  }
  //  ͬ����������Ҳ�п��ܲ�ƽ�⣬���������������
  if( r->rchild!= _null )
  {
      erase_rotate_help( r->rchild );
  }
  //  ����������
  if( r!= _null )
  {
      erase_rotate_help( r );
  }
}

void AVLTree::erase(int oid ) {
  erase_help( root, oid ); 
}

int main()
{
  AVLTree test;
  int del;
  for(int i=1;i<=15;i++) {  
    avlObject p;
    p.oid=i;
    test.insert(p);
  }
  test.print(test.getroot(),0);
  for(int j =1;j<15;j++) {
    cout<<"please enter the number you want to delete: ";
    cin>>del;
    test.erase(del);  // delete node.
    test.print(test.getroot(), 0);
  }
  return 0;
}
