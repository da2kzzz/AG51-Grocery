#include <iostream>
#include <array>
#include <fstream>
#define hash_size 20

using namespace std;

//int hash_size=20;
class Student{
private:
    //string name, surname, group;
    //unsigned int hash_value;
    //int hash_value;
public:
    string name, surname, group;
    unsigned int hash_value;
    Student(){
        name="";
        surname="";
        group="";
        hash_value=0;
    }
    Student(string Name, string Surname, string Group):name(Name),surname(Surname),group(Group){
        int s=size(surname);
        int sum=0;
        for (int i=0;i<s;i++){sum=sum+surname[i];}
        hash_value=sum%hash_size;
    }
    Student operator=(const Student&){
        Student stu;
        stu.name=this->name;
        stu.surname=this->surname;
        stu.group=this->group;
        stu.hash_value=this->hash_value;
        return stu;
    }
    operator int() const{     //use later 'int xxx= int(*s);'---* a is the value of the address a
        return hash_value;    //--------------------------------& a is the address of a
    }                         //--------------------------------*(& a) is the value of address(&a)

    /*--------------------------------------------copied from class
      operator int() const{
         int hash=0;
         for(char a:surname){ hash+=(int)a;}
         return hash%hash_size;
         }
    ---------------------------------------------*/


    int getvalue(){return hash_value;}
};

template<class T> class List{
public:
    T *t;
    List *next;
    List(){
        t= nullptr;
        next= nullptr;
    }
    List(T *c_t,List *c_next):t(c_t),next(c_next){}
};

template<class T> class MyFactory {
private:
    array<T *, hash_size> hash_table = {};
public:
    MyFactory(){}
    //MyFactory(){
        /*ifstream fil("list_students.csv");
        string line;
        while (getline (fil, line)) {
            int pos1=line.string::find(";",0);//correct
            string Nom=line.string::substr(0,pos1);//correct
            int pos2=line.string::find(";",pos1+1);//correct
            string Prenom=line.string::substr(pos1+1,pos2-pos1-1);//correct
            string chambre=line.string::substr(pos2+1,2);//correct
            //List<Student> newlist(new Student(Prenom,Nom,chambre), nullptr);
            //insert(new List<Student>(new Student(Prenom,Nom,chambre), nullptr));
            Student st(Prenom,Nom,chambre);
            new List<Student>(*st, nullptr);
        }*/

    bool insert(T *s) {
        int index = s->t->hash_value;//test
        //cout<<"["<<s<<"]"<<endl;//test
        if (hash_table.at(index) == nullptr) {
            hash_table.at(index) = s;
            //cout<<"{"<<hash_table.at(index)<<"}"<<endl;//test
            return true;
        }
        else if(hash_table.at(index)!= nullptr){
            T *p = hash_table.at(index);
            while (p->next != nullptr) {
                p = p->next;
            }
            p->next = s;
            return true;
    }else return false;
}
    /*void print(){//not a good way
        for(int i=0;i<hash_size;i++){
            cout<<"["<<i<<"]"<<":";
            T *p=hash_table.at(i);
            if(p!= nullptr && p->next== nullptr){
                cout<<"("<<p->t->name<<" "<<p->t->surname<<" "<<p->t->group<<"("<<i<<")"<<")"<<endl;
            }
            else if(p!= nullptr&& p->next!= nullptr){
                do{
                    cout<<"("<<p->t->name<<" "<<p->t->surname<<" "<<p->t->group<<"("<<i<<")"<<")"<<",";
                    p=p->next;
                }while(p!= nullptr);
                cout<<endl;
            }
            else{cout<<"empty"<<endl;}
        }
    }*/
    void print(){
        for (int i = 0; i < hash_size; i++) {
            cout << "[" << i << "]" << ":";
            if (hash_table.at(i) == nullptr) {
                cout << "empty" << endl;
            }
            else if (hash_table.at(i) != nullptr) {
                T* p = hash_table.at(i);
                while (p->next != nullptr) {
                    cout << "(" << p->t->name << " " << p->t->surname << " " << p->t->group << "(" << i << ")" << ")," ;
                    p = p->next;
                }
                cout << "(" << p->t->name << " " << p->t->surname << " " << p->t->group << "(" << i << ")" << ")" << endl;
            }
        }
    }

    /*void getfromfile(){
        /*std::fstream fil;
        fil.open ("list_students.csv", std::fstream::in);
        //ifstream fil("D\\C++\\td15\\list_students.csv");
        string line;
        while (getline (fil, line)) {
            int pos1=line.string::find(";",0);
            string Nom=line.string::substr(0,pos1);
            int pos2=line.string::find(";",pos1+1);
            string Prenom=line.string::substr(pos1+1,pos2-pos1-1);
            string Chambre=line.string::substr(pos2+1,2);
            //List<Student> newlist(new Student(Prenom,Nom,chambre), nullptr);
            MyFactory::insert(new List<Student>(new Student(Prenom,Nom,Chambre), nullptr));
            cout<<"["<<Prenom<<" "<<Nom<<" "<<Chambre<<"]"<<endl;
        }
        filebuf fb;
        string filename = "list_students.csv";
        if(fb.open(filename.c_str(),ios::in) == NULL)
        {
            cout << "error" << endl;
        }
        istream is(&fb);
        string input;
        while(getline(is,input,'\n'))
        {
            int pos1 = string::npos;
            pos1 = input.find("\t");
            if(pos1 != string::npos)
            {
                cout << input.substr(pos1+1) << endl;
            }
            else
            {
                cout << "eror";
                break;
            }
        }
        fb.close();
      }*/

};

int main() {
    MyFactory<List<Student>> MF;
    MF.insert(new List<Student>(new Student("Benoit","PIRANDA","PhD."), nullptr));
    MF.insert(new List<Student>(new Student("Philippe","CANALDA","PhD."), nullptr));
    MF.insert(new List<Student>(new Student("Abdallah","MAKHOUL","PhD."), nullptr));
    MF.insert(new List<Student>(new Student("Oumaya","BAALA","PhD."), nullptr));
    MF.insert(new List<Student>(new Student("Frederic","LASSABE","PhD."), nullptr));
    MF.insert(new List<Student>(new Student("Francois","SPIES","PhD."), nullptr));
    MF.insert(new List<Student>(new Student("Julien","BOURGEOIS","PhD."), nullptr));
    //MF.insert(new List<Student>(new Student("Frederic","LASSABE","PhD."), nullptr));//for testing
    //MF.getfromfile();
    MF.print();

    //Student ST("A","B","C");//test 1
    //Student *ST=new Student("A","B","C");//test 2
    //cout<<ST->getvalue()<<endl;
    //cout<<(int)ST<<endl;
    //int i_2=(int)*ST;
    //cout<<i_2<<endl;



    return 0;
}