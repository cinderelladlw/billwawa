// avl ���ڵ���Ϣ
template <class T>
class TreeNode
{
    public:
        TreeNode():lson(NULL),rson(NULL),freq(1),hgt(0){}
        T data;//ֵ
        int hgt;//�߶�
        unsigned int freq;//Ƶ��
        TreeNode* lson;//ָ������ӵĵ�ַ
        TreeNode* rson;//ָ���Ҷ��ӵĵ�ַ
};
//AVL��������Ժͷ�������
template<class T>
class AVLTree
{
    private:
        TreeNode<T>* root;//���ڵ�
        void insertpri(TreeNode<T>* &node,T x);//����
        TreeNode<T>* findpri(TreeNode<T>* node,T x);//����
        void insubtree(TreeNode<T>* node);//�������
        void Deletepri(TreeNode<T>* &node,T x);//ɾ��
        int height(TreeNode<T>* node);//�����ĸ߶�
        void SingRotateLeft(TreeNode<T>* &k2);//��������µ���ת
        void SingRotateRight(TreeNode<T>* &k2);//��������µ���ת
        void DoubleRotateLR(TreeNode<T>* &k3);//��������µ���ת
        void DoubleRotateRL(TreeNode<T>* &k3);//��������µ���ת
        int Max(int cmpa,int cmpb);//�����ֵ

    public:
        AVLTree():root(NULL){}
        void insert(T x);//����ӿ�
        TreeNode<T>* find(T x);//���ҽӿ�
        void Delete(T x);//ɾ���ӿ�
        void traversal();//�����ӿ�

};
//����ڵ�ĸ߶�
template<class T>
int AVLTree<T>::height(TreeNode<T>* node)
{
    if(node!=NULL)
        return node->hgt;
    return -1;
}
//�����ֵ
template<class T>
int AVLTree<T>::Max(int cmpa,int cmpb)
{
    return cmpa>cmpb?cmpa:cmpb;
}
//��������µ���ת
template<class T>
void AVLTree<T>::SingRotateLeft(TreeNode<T>* &k2)
{
    TreeNode<T>* k1;
    k1=k2->lson;
    k2->lson=k1->rson;
    k1->rson=k2;

    k2->hgt=Max(height(k2->lson),height(k2->rson))+1;
    k1->hgt=Max(height(k1->lson),k2->hgt)+1;
}
//��������µ���ת
template<class T>
void AVLTree<T>::SingRotateRight(TreeNode<T>* &k2)
{
    TreeNode<T>* k1;
    k1=k2->rson;
    k2->rson=k1->lson;
    k1->lson=k2;

    k2->hgt=Max(height(k2->lson),height(k2->rson))+1;
    k1->hgt=Max(height(k1->rson),k2->hgt)+1;
}
//�����������ת
template<class T>
void AVLTree<T>::DoubleRotateLR(TreeNode<T>* &k3)
{
    SingRotateRight(k3->lson);
    SingRotateLeft(k3);
}
//�����������ת
template<class T>
void AVLTree<T>::DoubleRotateRL(TreeNode<T>* &k3)
{
    SingRotateLeft(k3->rson);
    SingRotateRight(k3);
}
//����
template<class T>
void AVLTree<T>::insertpri(TreeNode<T>* &node,T x)
{
    if(node==NULL)//����ڵ�Ϊ��,���ڴ˽ڵ㴦����x��Ϣ
    {
        node=new TreeNode<T>();
        node->data=x;
        return;
    }
    if(node->data>x)//���xС�ڽڵ��ֵ,�ͼ����ڽڵ���������в���x
    {
        insertpri(node->lson,x);
        if(2==height(node->lson)-height(node->rson))
            if(x<node->lson->data)
                SingRotateLeft(node);
            else
                DoubleRotateLR(node);
    }
    else if(node->data<x)//���x���ڽڵ��ֵ,�ͼ����ڽڵ���������в���x
    {
        insertpri(node->rson,x);
        if(2==height(node->rson)-height(node->lson))//����߶�֮��Ϊ2�Ļ���ʧȥ��ƽ��,��Ҫ��ת
            if(x>node->rson->data)
                SingRotateRight(node);
            else
                DoubleRotateRL(node);
    }
    else ++(node->freq);//������,�Ͱ�Ƶ�ʼ�1
    node->hgt=Max(height(node->lson),height(node->rson));
}
//����ӿ�
template<class T>
void AVLTree<T>::insert(T x)
{
    insertpri(root,x);
}
//����
template<class T>
TreeNode<T>* AVLTree<T>::findpri(TreeNode<T>* node,T x)
{
    if(node==NULL)//����ڵ�Ϊ��˵��û�ҵ�,����NULL
    {
        return NULL;
    }
    if(node->data>x)//���xС�ڽڵ��ֵ,�ͼ����ڽڵ���������в���x
    {
        return findpri(node->lson,x);
    }
    else if(node->data<x)//���x���ڽڵ��ֵ,�ͼ����ڽڵ���������в���x
    {
        return findpri(node->rson,x);
    }
    else return node;//������,���ҵ��˴˽ڵ�
}
//���ҽӿ�
template<class T>
TreeNode<T>* AVLTree<T>::find(T x)
{
    return findpri(root,x);
}
//ɾ��
template<class T>
void AVLTree<T>::Deletepri(TreeNode<T>* &node,T x)
{
    if(node==NULL) return ;//û���ҵ�ֵ��x�Ľڵ�
    if(x < node->data)
    {
         Deletepri(node->lson,x);//���xС�ڽڵ��ֵ,�ͼ����ڽڵ����������ɾ��x
         if(2==height(node->rson)-height(node->lson))
            if(node->rson->lson!=NULL&&(height(node->rson->lson)>height(node->rson->rson)) )
                DoubleRotateRL(node);
            else
                SingRotateRight(node);
    }

    else if(x > node->data)
    {
         Deletepri(node->rson,x);//���x���ڽڵ��ֵ,�ͼ����ڽڵ����������ɾ��x
         if(2==height(node->lson)-height(node->rson))
            if(node->lson->rson!=NULL&& (height(node->lson->rson)>height(node->lson->lson) ))
                DoubleRotateLR(node);
            else
                SingRotateLeft(node);
    }

    else//������,�˽ڵ����Ҫɾ���Ľڵ�
    {
        if(node->lson&&node->rson)//�˽ڵ�����������
        {
            TreeNode<T>* temp=node->rson;//tempָ��ڵ���Ҷ���
            while(temp->lson!=NULL) temp=temp->lson;//�ҵ���������ֵ��С�Ľڵ�
            //������������С�ڵ��ֵ��ֵ�����ڵ�
            node->data=temp->data;
            node->freq=temp->freq;
            Deletepri(node->rson,temp->data);//ɾ������������Сֵ�Ľڵ�
            if(2==height(node->lson)-height(node->rson))
            {
                if(node->lson->rson!=NULL&& (height(node->lson->rson)>height(node->lson->lson) ))
                    DoubleRotateLR(node);
                else
                    SingRotateLeft(node);
            }
        }
        else//�˽ڵ���1����0������
        {
            TreeNode<T>* temp=node;
            if(node->lson==NULL)//���Ҷ��ӻ���û�ж���
            node=node->rson;
            else if(node->rson==NULL)//�������
            node=node->lson;
            delete(temp);
            temp=NULL;
        }
    }
    if(node==NULL) return;
    node->hgt=Max(height(node->lson),height(node->rson))+1;
    return;
}
//ɾ���ӿ�
template<class T>
void AVLTree<T>::Delete(T x)
{
    Deletepri(root,x);
}
//�����������
template<class T>
void AVLTree<T>::insubtree(TreeNode<T>* node)
{
    if(node==NULL) return;
    insubtree(node->lson);//�ȱ���������
    cout<<node->data<<" ";//������ڵ�
    insubtree(node->rson);//�ٱ���������
}
//��������ӿ�
template<class T>
void AVLTree<T>::traversal()
{
    insubtree(root);
}
