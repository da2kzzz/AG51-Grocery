#include <iostream>

class Element{
private:
    int data;
    Element *next;
public:
    Element(int c_data):data(c_data){next=nullptr;}
    Element(int c_data,Element *c_next):data(c_data),next(c_next){}
    inline Element *getnext(){return next;}
    inline int getvalue(){return data;}
    inline Element *setnext(Element *new_next){next=new_next;}
};

class stackint{
private:
    Element *top;
public:
    stackint(){top=nullptr;}
    void push(int n){
        auto *newElement=new Element(n,top);
        top=newElement;
    }
    int size(){
        int n=(top==nullptr)?0:1;
        Element *current=top;
        while(current!= nullptr&& current->getnext()!= nullptr){
            n++;
            current=current->getnext();
        }
        return n;
    }
    bool deleteElement(int v){
        auto current=top;
        if(top==nullptr) return false;
        if(top->getnext()== nullptr){
            if(top->getvalue()==v){//that means only one element equals to v
                delete top;
                top= nullptr;
                return true;
            }else return false;
        }
        while(current->getnext()!= nullptr&&current->getnext()->getvalue()!=v){
            current=current->getnext();
        }
        if(current->getnext()!= nullptr){
            auto mem=current->getnext();
            current->setnext(current->getnext()->getnext());
            delete mem;
            return true;
        }
        return false;
    }
    bool insertElement(int v,int prev){
        auto current=top;
        while(current->getnext()!=nullptr && current->getnext()->getvalue()!=prev){
            current=current->getnext();
        }
        if(current->getnext()!= nullptr) {
            current = current->getnext();//current is prev now
            Element *new_elem = new Element(v, current->getnext());
            current->setnext(new_elem);
            return true;
        }
        return false;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
