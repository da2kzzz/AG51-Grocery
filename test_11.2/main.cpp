#include "assistance.h"
#include "heads.h"


int main(void) {
//  for question 1 part 1 & 2 with different filename------------------------------------------------------

    try{
        cout<<"question 1 "<<endl;
        int infinity = DEFAULT_INFINITY;
        ifstream fil ("d:\\mat3.txt"); // change file name here or use the line after
        //ifstream fil ("d:\\cost3.txt");
        if(!fil){
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        int number;
        fil >> number;
        int data[number][number];
        for(int i =0;i<number;i++){
            for(int j=0;j<number;j++){
                fil >> data[i][j];
                if(data[i][j]==0)
                    data[i][j]=infinity;
            }
        }


        int vexs[] = { 0, 1, 2, 3, 4, 5};
        int n = number;

        AdjListDirNetwork net(vexs, n);

        for (int u = 0; u < n; u++)
            for (int v = n - 1; v >= 0; v--)
                if (data[u][v] != infinity) net.InsertArc(u, v, data[u][v]);

        cout << "the original graph:" << endl;
        net.Display();



        int** dist, ** path;

        dist = new int* [net.GetVexNum()], path = new int* [net.GetVexNum()];
        for (int i = 0; i < net.GetVexNum(); i++) {
            dist[i] = new int[net.GetVexNum()];
            path[i] = new int[net.GetVexNum()];
        }

        ShortestPathFloyd(net, path, dist);	// Floyd
        DisplayPathAndDist(net, path, dist);
        cout  << endl;

        for (int j = 0; j < net.GetVexNum(); j++) {
            delete[]dist[j];
            delete[]path[j];
        }
        delete[]dist; delete[]path;
    }
    catch (Error err){

        err.Show();
    }



// for question  2---------------------------------------------------------------
    try{
        cout<<"question 2 with instal_cost3.txt"<<endl;
        int infinity = DEFAULT_INFINITY;
        ifstream fil ("d:\\instal_cost3.txt");
        if(!fil){
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        int number;
        fil >> number;

        int data[number][number];
        for(int i =0;i<number;i++){
            for(int j=0;j<number;j++){
                fil >> data[i][j];
                if(i==j)
                    data[i][j]=infinity;
            }
        }


        int vexs[] = { 0, 1, 2, 3, 4, 5};
        int n=number;

        AdjMatrixUndirNetwork net(reinterpret_cast<int *>(vexs), n, n, infinity);

        for (int u = 0; u < n; u++)
            for (int v = u+1; v < n; v++)
                if (data[u][v] != infinity && u != v)
                    net.InsertArc(u, v, data[u][v]);
        int u0 = 0;
        cout << "Starting at vertex "<< u0<< ", the minimum spanning tree using 'Prim' is :" << endl;

        int summary =  MiniSpanTreePrim(net, u0);		// Prim
        cout << endl;
        cout<<"the minimum cost is : "<< summary  <<endl<< endl;
    }
    catch (Error err){

        err.Show();
    }
// for question 3 and 4--------------------------------------------------------------
    try{
        cout<<"question 3 "<<endl;
        int infinity = DEFAULT_INFINITY;
        ifstream fil ("d:\\mat3.txt"); //  just change the file name
        //ifstream fil ("d:\\cost3.txt");
        if(!fil){
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        int number;
        fil >> number;
        int data[number][number];
        for(int i =0;i<number;i++){
            for(int j=0;j<number;j++){
                fil >> data[i][j];
                if(data[i][j]==0)
                    data[i][j]=infinity;
            }
        }
        Graph G(number);
        for(int i =0;i<number;i++){
            for(int j=0;j<number;j++){
                if(data[i][j]!=infinity)
                    G.AddLine(i,j);
            }
        }
        cout<< "all the clusters are below : "<<endl;
        vector<vector<int>> SCCs= G.PrintSCC();
       // cout<<"{"<<SCCs[0].at(1)<<"}"<<endl;
       // cout<<SCCs.size()<<" "<<SCCs[0].size()<<endl;
       int AdjClu[SCCs.size()][SCCs.size()];
        for(int i=0;i<SCCs.size();i++){//Array initialization
            for(int j=0;j<SCCs.size();j++){
                AdjClu[i][j]=0;
            }
        }
       for(int i=0;i<SCCs.size();i++){//Determine whether the clusters are related
           for(int j =0;j<SCCs[i].size();j++){
               for(int k=0;k<SCCs.size();k++){
                   for(int l=0;l<SCCs[k].size();l++){
                       int a=SCCs[i].at(j);
                       int b=SCCs[k].at(l);
                       if (data[a][b]!=infinity){
                           AdjClu[i][k]=data[a][b];
                       }
                   }
               }
           }
       }
       for(int i=0;i<SCCs.size();i++){//Eliminate self loop
           AdjClu[i][i]=0;
       }
       cout<<"Adjacency matrix of clusters is:"<<endl;
       for(int i=0;i<SCCs.size();i++){
           for(int j=0;j<SCCs.size();j++){
               cout<<AdjClu[i][j]<<" ";
           }
           cout<<endl;
       }
    }
    catch(Error err){
        err.Show();
    }





    return 0;
}
