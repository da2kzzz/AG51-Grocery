#ifndef __ASSISTANCE_H__
#define __ASSISTANCE_H__
//the useful heads
#include <cstring>
#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <cstdarg>
#include <cassert>
#include <list>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
enum Status {
    SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR,
    NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED
};
#define DEFAULT_SIZE 1000
#define DEFAULT_INFINITY 1000000
char GetChar(istream& inStream = cin);
void Swap(int& e1, int& e2);
void Display(int elem[], int n);
void Write(const int& e);
class Error;
char GetChar(istream& inStream)
{
    char ch;
    while ((ch = (inStream).peek()) != EOF
        && ((ch = (inStream).get()) == ' '
            || ch == '\t'));
    return ch;
}
#define MAX_ERROR_MESSAGE_LEN 100
class Error
{
private:
    char message[MAX_ERROR_MESSAGE_LEN];
public:
    Error(const char* mes = "General error!");
    ~Error(void) {};
    void Show() const;
};
Error::Error(const char* mes)
{
    strcpy(message, mes);
}
void Error::Show()const
{
    cout << message << endl;
}
void Swap(int& e1, int& e2)
{
    int temp;
    temp = e1;	e1 = e2;  e2 = temp;
}
void Display(int elem[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << elem[i] << "  ";
    }
    cout << endl;
}
void Write(const int& e)
{
    cout << e << "  ";
}
#endif
