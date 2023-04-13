//
// Created by uchi on 2020/9/28.
//

#ifndef INC_3_4_1_BST_H
#define INC_3_4_1_BST_H


class BST {
private:
    int key;
    float x,y;
    BST *leftChild,*rightChild,*parent;
public:
    BST(int p_key,BST *p_leftChild= nullptr,BST *p_rightChild= nullptr,BST *p_parent= nullptr):
            key(p_key),leftChild(p_leftChild),rightChild(p_rightChild),parent(p_parent){
        if(!leftChild){//<=>leftChild different to nullptr
            leftChild->parent = this;
        }
        if(!rightChild){
            rightChild->parent = this;
        }
    }
};


#endif //INC_3_4_1_BST_H
