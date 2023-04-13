#include <iostream>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int length = s.length();
        char buf[length];
        s.copy(buf,length);
        buf[length] = '\0';
        int max = 0;
        char test[length];
        for(int i=0;i<length;i++){
            int j = 0;
            if(i==0){
                test[j] = buf[i];
                max++;
                j++;
            }
            else{
                for(int k=0;k<j;k++){
                    
                }
            }

        }
    }
};



int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
