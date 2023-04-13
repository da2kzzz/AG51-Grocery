#include <iostream>
#include <string>

using namespace std;

int in=0;
int In[1000]={};

class BST{
public:
    int data;
    BST  *leftChild;
    BST  *rightChild;
    BST  *parent;

    BST(){leftChild = rightChild = parent = nullptr;}
    BST(const int &d,BST *lChild = nullptr,BST *rChild = nullptr,BST *pt = nullptr ):
            data(d),leftChild(lChild),rightChild(rChild),parent(pt){
        if(leftChild!= nullptr){
            leftChild->parent = this;
        }
        if(rightChild!= nullptr) {
            rightChild->parent = this;
        }
    }
};
//----------------------------------------------------------------------------------------------------

class BinaryTree{
protected:
    BST *root;
    int count=0;
    int height=0;

    void InOrder(BST *r,void (*Visit)(const int &)) const;//inorder traversal
    int getHeight(const BST  *r) const;
    int nbNodes(const BST  *r) const;
    int nbChildrenAtLevel(const BST *r,int h);
    BST  *Parent(BST  *r,const BST *p) const;//get parents of p
    bool isFull(BST *r);
    bool result=true;
    void find(int k,BST *r,BST *&e);
    void insert(int k,BST *r,bool &e);
public:

    BinaryTree();
    BinaryTree(const int &e);
    BST  *GetRoot() const;
    void InOrder(void (*Visit)(const int &)) const;// inorder traversal
    int nbNodes() const;
    BST  *LeftChild(const BST  *p) const;
    BST *RightChild(const BST *p) const;
    void InsertLeftChild(BST *p, const int &e);
    void InsertRightChild(BST *p, const int &e);
    int	getHeight() const;
    int getDeepth(const BST *r);
    int nbChildrenAtLevel(int h);
    bool isBST();
    bool isFull();
    BST *find(int k);
    bool insert(int k);
};

BinaryTree::BinaryTree(){root = nullptr;}

BST *BinaryTree::GetRoot() const{return root;}


void BinaryTree::InOrder(BST *r, void (*Visit)(const int &)) const{
    if (r != nullptr) {
        InOrder(r->leftChild, Visit);
        (*Visit)(r->data);
        In[in]=r->data;
        in++;
        InOrder(r->rightChild, Visit);
    }
}

void BinaryTree::InOrder(void (*Visit)(const int &)) const{InOrder(root, Visit);}

int BinaryTree::getHeight(const BST *r) const{
    if(r == nullptr)  return 0;	// height = 0
    else{
        int lgetHeight, rgetHeight;
        lgetHeight = getHeight(r->leftChild);
        rgetHeight = getHeight(r->rightChild);
        return (lgetHeight > rgetHeight ? lgetHeight : rgetHeight) + 1;
    }
}

int BinaryTree::getHeight() const{return getHeight(root);}

BinaryTree::BinaryTree(const int &e){root = new BST(e);}

int BinaryTree::nbNodes(const BST *r) const{
    if (r ==nullptr) return 0;
    else return nbNodes(r->leftChild) + nbNodes(r->rightChild) + 1;
}

int BinaryTree::nbChildrenAtLevel(const BST *r,int h){
    if(h==0){return 1;}
    else if (r != nullptr){
        int hei=getDeepth(r)+1;
        count=0;
        if(hei==(h)) height++;
        nbChildrenAtLevel(r->leftChild,h);
        nbChildrenAtLevel(r->rightChild,h);
    }
    return height;
}

int BinaryTree::getDeepth(const BST *r) {
    if(r->parent!= nullptr){
        if(r->parent!=root){
            count++;
            getDeepth(r->parent);
        }
    }
    else if(r->parent==root){
        count=0;
    }
    else count=-1;
    return count;
}

int BinaryTree::nbChildrenAtLevel(int h) {
    int i= nbChildrenAtLevel(root,h);
    height=0;
    return i;
}

bool BinaryTree::isBST() {
    int j=0;
    for(int i=0;i<nbNodes()-1;i++){
        if(In[i]<In[i+1]) j=j+0;
        else j++;
    }
    if(j==0) return true;
    else return false;
}

bool BinaryTree::isFull(BST *r) {
    if(r!= nullptr) {
        if(LeftChild(r)!= nullptr&& RightChild(r)!= nullptr){
            result=true;
            isFull(r->leftChild);
            isFull(r->rightChild);
        }
        else if (LeftChild(r)== nullptr&& RightChild(r)== nullptr){
            result=true;
        }else result= false;
    }else return true;
    return result;
}

bool BinaryTree::isFull() {return isFull(root);}

int BinaryTree::nbNodes() const{return nbNodes(root);}

BST *BinaryTree::LeftChild(const BST *p) const{return p->leftChild;}

BST *BinaryTree::RightChild(const BST *p) const{return p->rightChild;}

BST * BinaryTree::Parent(BST *r, const BST *p) const{
    if (r == nullptr) return nullptr;
    else if (r->leftChild == p || r->rightChild == p) return r;
    else{
        BST *tmp;
        tmp = Parent(r->leftChild, p);
        if (tmp != nullptr) return tmp;

        tmp = Parent(r->rightChild, p);
        if (tmp != nullptr) return tmp;
        else return nullptr;
    }
}

void BinaryTree::InsertLeftChild(BST *p, const int &e){
    if (p == nullptr) return;
    else {
        BST *child =  new BST(e);
        child->parent = p;
        if (p->leftChild != nullptr)
            child->leftChild = p->leftChild;
        p->leftChild = child;
        return;
    }
}

void BinaryTree::InsertRightChild(BST *p, const int &e){
    if (p == nullptr) return;
    else{
        BST *child =  new BST(e);
        child->parent = p;
        if (p->rightChild != nullptr)
            child->rightChild = p->rightChild;
        p->rightChild = child;
        return;
    }
}

void BinaryTree::find(int k,BST *r,BST *&e) {
    if (r != nullptr ) {
        if(r->data==k) {
            e=r;
        }
        else if(k<r->data){
            if(r->leftChild!= nullptr){
                find(k,r->leftChild,*&e);
            }
            else e=r->parent;
        }
        else if(k>r->data){
            if(r->rightChild!= nullptr){
                find(k,r->rightChild,*&e);
            }
            else e=r->parent;
        }
    }
    else return;
}

BST * BinaryTree::find(int k) {
    BST *e;
    find(k,root,e);
    return e;
}

void BinaryTree::insert(int k, BST *r,bool &e) {
    if (r != nullptr ) {
        if(r->data==k) {
            e= false;
        }
        else if(k<r->data){
            if(r->leftChild!= nullptr){
                insert(k,r->leftChild,e);
            }
            else {
                InsertLeftChild(r,k);
                e= true;
            }
        }
        else if(k>r->data){
            if(r->rightChild!= nullptr){
                insert(k,r->rightChild,e);
            }
            else {
                InsertRightChild(r,k);
                e= true;
            }
        }
    }
    else return;
}

bool BinaryTree::insert(int k) {
    bool e;
    insert(k,root,e);
    return e;
}

void Write(const int &e){cout<<"(" << e << ")"<<endl;}


int main() {
    BST *p;
    BinaryTree bt(16);
    p = bt.GetRoot();// p is '16'
    bt.InsertLeftChild(p,8);//insert '8'
    bt.InsertRightChild(p, 25);//insert '25'
    p = bt.LeftChild(p);// p is '8'
    bt.InsertLeftChild(p, 7);
    bt.InsertRightChild(p, 11);
    p = bt.RightChild(p);// p is '11'
    bt.InsertLeftChild(p, 9);
    bt.InsertRightChild(p, 14);
    p = bt.GetRoot();// p is '16'
    p = bt.RightChild(p);// p is '25'
    bt.InsertLeftChild(p, 21);
    bt.InsertRightChild(p, 31);
    p = bt.RightChild(p);// p is '31'
    bt.InsertRightChild(p, 46);// finish build the tree

    cout << "Console : "<<endl;//inorder traversal
    bt.InOrder(Write);
    cout<<"Number of nodes: "<<bt.nbNodes()<<endl;
    cout<<"Height: "<<bt.getHeight()<<endl;
    for(int i=0;i<bt.getHeight();i++){
        cout<<"Number of nodes at height "<<i<<"= "<<bt.nbChildrenAtLevel(i)<<endl;
    }
    cout<<bt.isBST()<<endl;//true==1;false==0
    cout<<bt.isFull()<<endl;//true==1;false==0
    cout<<bt.find(33)->data<<endl;
    cout<<bt.insert(11);//true==1;false==0
    //bt.InOrder(Write);

}
