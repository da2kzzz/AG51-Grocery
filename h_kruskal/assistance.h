#ifndef __ASSISTANCE_H__
#define __ASSISTANCE_H__

//the heads
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
using namespace std;

// �Զ�������
enum Status {
    SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR,
    NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED
};

// �궨��
#define DEFAULT_SIZE 1000			// ȱʡԪ�ظ���
#define DEFAULT_INFINITY 1000000	// ȱʡ�����


// ������������

char GetChar(istream& inStream = cin); // ��������inStream�������ո��Ʊ����ȡһ�ַ�


void Swap(int& e1, int& e2);	// ����e1, e2ֵ֮


void Display(int elem[], int n);	// ��ʾ����elem�ĸ�����Ԫ��ֵ


void Write(const int& e);			// ��ʾ����Ԫ��

// ������
class Error;			// ͨ���쳣��

char GetChar(istream& inStream)
// �����������������inStream�������ո��Ʊ����ȡһ�ַ�
{
    char ch;								// ��ʱ����
    while ((ch = (inStream).peek()) != EOF	// �ļ�������(peek()�������������н���1
           // �ַ�,���ĵ�ǰλ�ò���)
        && ((ch = (inStream).get()) == ' '	// �ո�(get()�������������н���1�ַ�,��
            // �ĵ�ǰλ�������1��λ��)
            || ch == '\t'));					// �Ʊ��

    return ch;								// �����ַ�
}


// ͨ���쳣��
#define MAX_ERROR_MESSAGE_LEN 100
class Error
{
private:
    // ���ݳ�Ա
    char message[MAX_ERROR_MESSAGE_LEN];// �쳣��Ϣ

public:
    //  ��������
    Error(const char* mes = "һ�����쳣!");	// ���캯��
    ~Error(void) {};					// ��������
    void Show() const;					// ��ʾ�쳣��Ϣ
};

// ͨ���쳣���ʵ�ֲ���
Error::Error(const char* mes)
// �����������mes����ͨ���쳣����
{
    strcpy(message, mes);				// �����쳣��Ϣ
}

void Error::Show()const
// �����������ʾ�쳣��Ϣ
{
    cout << message << endl;			// ��ʾ�쳣��Ϣ
}



void Swap(int& e1, int& e2)
// �������: ����e1, e2ֵ֮
{
    int temp;		// ��ʱ����
    // ѭ����ֵʵ�ֽ���e1, e2
    temp = e1;	e1 = e2;  e2 = temp;
}


void Display(int elem[], int n)
// �������: ��ʾ����elem�ĸ�����Ԫ��ֵ
{
    for (int i = 0; i < n; i++)
    {	// ��ʾ����elem
        cout << elem[i] << "  ";
    }
    cout << endl;
}


void Write(const int& e)
// �������: ��ʾ����Ԫ��
{
    cout << e << "  ";
}

#endif
