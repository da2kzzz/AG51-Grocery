#include <iostream>
using namespace std;


void LCS(string s1,string s2){
    int m = s1.size()+1;
    int n = s2.size()+1;

    /*申请二维数组B和C*/
    /*
    C是优化函数值矩阵
    C[i][j]表示s1的前i个元素和s2的前j个元素的最长公共子序列的长度
    */
    int** C = new int* [m];
    for(int i=0;i<m;i++)
        C[i] = new int [n];
    /*
    B是标记函数值矩阵，记录当前优化函数值是从那个方向来的
    B中元素取值解释--0：左，1：上，2：左上
    */
    int** B = new int* [m];
    for(int i=0;i<m;i++)
        B[i] = new int [n];

    /*
    初始化B和C矩阵的第0行与第0列
    C[i][0]表示s1的前i个字符与s2的前0个字符的
    公共子序列的长度，显然其值为0；C[0][j]与C[i][j]相同；
    */
    for(int i=0;i<m;i++){
        C[i][0] = 0;
        B[i][0] = 0;
    }
    for(int j=0;j<n;j++){
        C[0][j] = 0;
        B[0][j] = 0;
    }
    /*
    动态规划过程，逐步填表
    由小到大逐步计算C[i][j]和B[i][j]
    */
    for(int i=1;i<m;i++){
        for(int j=1;j<n;j++){
            if(s1[i-1]==s2[j-1]){
                C[i][j] = C[i-1][j-1]+1;
                B[i][j] = 2;
            }else{
                if(C[i-1][j]>=C[i][j-1]){
                    C[i][j] = C[i-1][j];
                    B[i][j] = 0;
                }else{
                    C[i][j] = C[i][j-1];
                    B[i][j] = 1;
                }
            }
        }
    }
    //return C[m-1][n-1];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout<<C[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(){
    string a="01257";
    string b="11364";
    LCS(a,b);
}