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
       AvlNode* _null;    //   规定的空结点
       AvlNode* root;     //   根结点
       void left_single_rotate( AvlNode*& r );     //  左单旋转
       void left_double_rotate( AvlNode*& r );     //  左双旋转
       void right_single_rotate( AvlNode*& r );    //  右单旋转
       void right_double_rotate( AvlNode*& r );    //  右双旋转
       void erase_rotate_help( AvlNode*& r );      //  删除操作中的旋转
       void insert_help( AvlNode*& r, avlObject avlobj );  //  插入
       void erase_help ( AvlNode*& r, int );               //  删除
   public:
       AVLTree();
       void insert( avlObject avlobj );                 //  插入数据
       void erase ( int oid );                 //  删除数据
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
//   左单旋转实现
void AVLTree::left_single_rotate( AvlNode* &r ){
   AvlNode* tmp= r->rchild;
   r->rchild= tmp->lchild;
   r->height= max( r->lchild->height, r->rchild->height )+ 1;
   tmp->lchild= r;
   r= tmp;
   r->height= max( r->lchild->height, r->rchild->height )+ 1;
}
//  右单旋转实现
void AVLTree::right_single_rotate( AvlNode*& r ){
   AvlNode* tmp= r->lchild;
   r->lchild= tmp->rchild;
   r->height= max( r->lchild->height, r->rchild->height )+ 1;
   tmp->rchild= r;
   r= tmp;
   r->height= max( r->lchild->height, r->rchild->height )+ 1;
}
//  左双旋转实现
void AVLTree::left_double_rotate( AvlNode*& r ){
  right_single_rotate( r->rchild );
  left_single_rotate( r );
}
//  右双旋转实现
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
  //这上面一部分同二叉查找树的代码 ,AVL树只是在其基础上
  //增加了旋转保持平衡的操作
  //调整根结点的高度，因为增加结点后，高度可能增加
  r->height= max( r->lchild->height, r->rchild->height )+ 1;
  //如果右子树不为空
  if( r->rchild!= _null ) {
    // 左子树的高度加上1等于右子树的右子树的高度，则左单旋转
    if( r->lchild->height+ 1== r->rchild->rchild->height )
    left_single_rotate( r );
    // 左子树的高度加上1等于右子树的左子树的高度，则左双旋转
    else if( r->lchild->height+ 1== r->rchild->lchild->height )
    left_double_rotate( r );
  }
  //  如果左子树不为空
  if( r->lchild!= _null ) {
    // 右子树的高度加上1等于左子树的左子树的高度，则右单旋转
    if( r->rchild->height+ 1== r->lchild->lchild->height )
    right_single_rotate( r );
    // 右子树的高度加上1等于左子树的右子树的高度，则右双旋转
    else if( r->rchild->height+ 1== r->lchild->rchild->height )
    right_double_rotate( r );
  }
}
void AVLTree::insert( avlObject avlobj ){
  insert_help( root, avlobj ); 
}
void AVLTree::erase_rotate_help( AvlNode*& r ){
  //  右子树高度比左子树高度大2
  if( r->rchild->height - r->lchild->height== 2 ) {
    // 如果右子树的左子树的高度不大于右子树的右子树的高度则对根左单旋转
    if( r->rchild->lchild->height<= r->rchild->rchild->height )
      left_single_rotate( r );
    // 如果右子树的左子树的高度大于右子树的右子树的高度则对根左双旋转
    else
      left_double_rotate( r );
  }
  //  左子树高度比右子树高度大2
  else if( r->lchild->height- r->rchild->height== 2  ){
    //  如果左子树的右子树的高度不大于左子树的左子树的高度则对根右单旋转
    if( r->lchild->rchild->height<= r->lchild->lchild->height )
      right_single_rotate( r );
    //  如果左子树的右子树的高度大于左子树的左子树的高度则对根右双旋转
    else
    right_double_rotate( r );
  }
}
void AVLTree::erase_help( AvlNode*& r, int oid ){
  if ( r == _null ) 
    return;  //  没有找到要删除的结点则直接退出
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

  //  同样，这上面一部分同二叉查找树的代码 ,AVL树只是在其基础上
  //  增加了旋转保持平衡的操作
  //  调整高度
  r->height= max( r->lchild->height, r->rchild->height )+ 1;
  //  有可能在左子树中把结点删除导致左子树不平衡
  //  故先检测左子树是否已经平衡，否 则调整
  if( r->lchild!= _null )
  {
  erase_rotate_help( r->lchild );
  }
  //  同样右子树中也有可能不平衡，检测右子树并调整
  if( r->rchild!= _null )
  {
      erase_rotate_help( r->rchild );
  }
  //  检测根并调整
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
