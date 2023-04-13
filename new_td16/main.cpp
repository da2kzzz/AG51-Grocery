#include <istream>

using namespace std;

class BST {
private:
    int key;
    float x, y;
    BST *leftChild, *rightChild, *parent;
public:
    BST(int p_key, BST *P_leftChild = nullptr, BST *P_rightChild = nullptr, BST *P_parent = nullptr) :
            key(p_key), leftChild(P_leftChild), rightChild(P_rightChild), parent(P_parent) {
        if (!leftChild) {//leftChild!=nullptr
            leftChild->parent = this;
        }
        if (!rightChild) {
            rightChild->parent = this;
        }
    }


    ~BST() {
        if (leftChild) delete leftChild;
        if (rightChild) delete rightChild;
    }



};