#include <iostream>
#include <stdlib.h>
#include <time.h>


int tab[20];

/*void onStart(){
    srand((unsigned int)(time(NULL)));
    for(int i=0;i<20;i++){
        tab[i]=(std::rand()%99)+1;
    }
}*/

void initTab(){
    for(int i=0;i<20;i++){
        int j,k;
        srand((unsigned int)(time(NULL)));
        do{
            j=(std::rand()%99)+1;
            k=0;
            while(k<i&&tab[k]!=j) k++;
        }while(k<i);
        tab[i]=j;
    }
}

void onDraw(){

}

int main() {
    //onStart();
    initTab();
    for(int i=0;i<20;i++){
        std::cout<<tab[i]<<std::endl;
    }
    return 0;
}
