#include <iostream>
#include "BST.h"


int main() {
    BST *tmp1=new BST(9);
    BST *tmp2=new BST(14);
    tmp1=new BST(11,tmp1,tmp2);
    return 0;
}
