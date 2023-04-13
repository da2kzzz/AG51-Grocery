#include <iostream>
//#include <iomanip>
#include <fstream>

using namespace std;

int main(){
    //char buffer[256];
    ifstream myfile ("d:\\instal_cost3.txt");
    //ofstream outfile("d:\\test.txt");

    if(!myfile){
        cout << "Unable to open myfile";
        exit(1); // terminate with error

    }
   // if(!outfile){
   //     cout << "Unable to open otfile";
  //      exit(1); // terminate with error

   // }
    int number,number2;
    myfile >> number;
    cout<<number<<endl;
    int data[number][number];
    for(int i =0;i<number;i++){
        for(int j=0;j<number;j++){
            myfile >> data[i][j];
        }
    }
    for(int k=0;k<number;k++){
        for(int l=0;l<number;l++){
            cout<< data[k][l] << " ";
        }
        cout <<endl;
    }
    //myfile >> number2;
    //cout<<number2<<endl;
    //int a[number];
    //int i=0,j=0;

    /*while (! myfile.eof() )
    {
        myfile.getline (buffer,100);  //读入每行
        for (int k = 0; k < number; ++k) {
            sscanf(buffer,"%d ",&a[k]);
            data[i][0]=a[k];
        }
        //cout<<a<<" "<<b<<endl;

        //data[i][1]=b;
        i++;
    }
    myfile.close();
    for(int k=0;k<number;k++){
        for(int l=0;l<number;l++){
            cout<< data[k][l] << " ";
        }
        cout <<endl;
    }

    for(int k=0;k<i;k++)
    {
        outfile<<data[k][0] <<" "<<data[k][1]<<endl;
        cout<<data[k][0] <<" "<<data[k][1]<<endl;
    }

    outfile.close();*/
    return 0;
}