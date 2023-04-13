#ifndef __HEADS_H__
#define __HEADS_H__

#include "assistance.h"

// �����

struct Node
{
// ���ݳ�Ա:
    int data;				// ������
    Node *next;		// ָ����

// ���캯��:
    Node();						// �޲����Ĺ��캯��
    Node(int item, Node *link = nullptr);	// ��֪������Ԫ��ֵ��ָ�뽨���ṹ
};

// ������ʵ�ֲ���

Node::Node()
// �������������ָ����Ϊ�յĽ��
{
    next = nullptr;
}

Node::Node(int item, Node *link)
// �������������һ��������Ϊitem��ָ����Ϊlink�Ľ��
{
    data = item;
    next = link;
}

// ��ջ��

class LinkStack
{
protected:
//  ��ջ�����ݳ�Ա:
    Node *top;							// ջ��ָ��

public:
//  ��ջ�ĺ�����Ա:
    LinkStack();									// �޲����Ĺ��캯��
    virtual ~LinkStack();							// ��������
    int GetLength() const;							// ��ջ����
    bool IsEmpty() const;							// �ж�ջ�Ƿ�Ϊ��
    void Clear();									// ��ջ���
    void Traverse(void (*Visit)(const int &)) const ;	// ����ջ
    Status Push(const int e);					// ��ջ
    Status Top(int &e) const;					// ����ջ��Ԫ��
    Status Pop(int &e);						// ��ջ
    LinkStack(const LinkStack &s);		// ���ƹ��캯��
    LinkStack &operator =(const LinkStack &s); // ��ֵ�������
};


// ��ջ���ʵ�ֲ���

LinkStack::LinkStack()
// �������������һ����ջ��
{
    top = nullptr;
}


LinkStack::~LinkStack()
// �������������ջ
{
    Clear();
}


int LinkStack::GetLength() const
// �������������ջԪ�ظ���
{
    int count = 0;		// ������
    Node *p;
    for (p = top; p != nullptr; p = p->next)		// ��p������Ѱÿ��Ԫ��
        count++;		// ͳ����ջ�н����
    return count;
}


bool LinkStack::IsEmpty() const
// �����������ջΪ�գ��򷵻�true�����򷵻�false
{
    return top == nullptr;
}


void LinkStack::Clear()
// ������������ջ
{
    Node *p;
    while (top != nullptr) {
        p = top;
        top = top->next;
        delete p;
    }
}


void LinkStack::Traverse(void (*Visit)(const int &)) const
// �����������ջ����ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���(*visit)����
{
    Node *p;
    for (p = top; p != nullptr; p = p->next)	// ��p������Ѱ��ǰջ��ÿ��Ԫ��
        (*Visit)(p->data);		// ��p��ָ���Ԫ�ص��ú���(*visit)����
}


Status LinkStack::Push(const int e)
// �����������Ԫ��e׷�ӵ�ջ��,��ɹ��򷵼�SUCCESS,�����綯̬�ڴ��Ѻľ�
//	������OVER_FLOW
{
    Node *p = new Node(e, top);
    if (p == nullptr) 	// ϵͳ�ڴ�ľ�
        return OVER_FLOW;
    else	{	// �����ɹ�
        top = p;
        return SUCCESS;
    }
}


Status LinkStack::Top(int &e) const
// �����������ջ�ǿ�,��e����ջ��Ԫ��,��������SUCCESS,����������UNDER_FLOW
{
    if(IsEmpty())	// ջ��
        return UNDER_FLOW;
    else	{	// ջ�ǿ�,�����ɹ�
        e = top->data;				// ��e����ջ��Ԫ��
        return SUCCESS;
    }
}


Status LinkStack::Pop(int &e)
// �����������ջ�ǿ�,ɾ��ջ��Ԫ��,����e����ջ��Ԫ��,��������SUCCESS,����
//	��������UNDER_FLOW
{
    if (IsEmpty())	// ջ��
        return UNDER_FLOW;
    else	{	// �����ɹ�
        Node *p = top;	// ����ԭջ��
        e = top->data;				// ��e����ջ��Ԫ��
        top = top->next;			// �޸�ջ��
        delete p;					// ɾ��ԭջ�����
        return SUCCESS;
    }
}


LinkStack::LinkStack(const LinkStack &s)
// �����������ջs������ջ--���ƹ��캯��
{
    if (s.IsEmpty())	// sΪ��
        top = nullptr;									// ����һ��ջ
    else 	{	                                    // s�ǿ�,����ջ
        top = new Node(s.top->data);	// ���ɵ�ǰջ��
        Node *q = top;			        // ���õ�ǰջ��ָ��
        for (Node *p = s.top->next; p != nullptr; p = p->next){
            q->next = new Node(p->data); // ��ջ��׷��Ԫ��
            q = q->next;					       // �޸�ջ��ָ��
        }
    }
}



LinkStack &LinkStack::operator = (const LinkStack &s)
// �����������ջs��ֵ����ǰջ--��ֵ�������
{
    if (&s != this)	{
        Clear();			// ��յ�ǰջ
        if (!s.IsEmpty())	{	                            // s�ǿ�,����ջ
            top = new Node(s.top->data);       // ���ɵ�ǰջ��
            Node *q = top;			            // ���õ�ǰջ��ָ��
            for (Node *p = s.top->next; p != nullptr; p = p->next){
                q->next = new Node(p->data);      // ��ջ��׷��Ԫ��
                q = q->next;			                    // �޸�ջ��ָ��
            }
        }
    }
    return *this;
}



// �ڽӱ�����������
struct AdjListNetworkArc
{
// ���ݳ�Ա:
    int adjVex;								// ��ͷ�������
    int weight;						// �ߵ�Ȩֵ
    AdjListNetworkArc *nextarc; // ��һ���߽���ָ��
// ���캯��:
    AdjListNetworkArc();					// �޲����Ĺ��캯��
    AdjListNetworkArc(int v, int w, AdjListNetworkArc * next = NULL);
    // �����ڽӵ�Ϊv��ȨΪw���ڽӱ�
};

// �ڽӱ������������ʵ�ֲ���

AdjListNetworkArc::AdjListNetworkArc()
// �������������һ�����ڽӱ�߽��ߡ����޲ι��캯��
{
    adjVex = -1;
}


AdjListNetworkArc::AdjListNetworkArc(int v, int w, AdjListNetworkArc *next)
// ��������������ڽӵ����Ϊv���ߵ�ȨΪw����һ���߽���ָ��Ϊnext���ڽӱ�
{
    adjVex = v;
    weight = w;
    nextarc = next;
}

// �ڽӱ�����������

struct AdjListNetWorkVex
{
// ���ݳ�Ա:
    int data;						// ����Ԫ��ֵ
    AdjListNetworkArc *firstarc;
    // ָ���ڽ�����߽���ָ��

// ���캯��:
    AdjListNetWorkVex();				// �޲����Ĺ��캯��
    AdjListNetWorkVex(int val,
                      AdjListNetworkArc *adj = nullptr);
    // �в����Ĺ��캯��
};

// �ڽӱ������������ʵ�ֲ���

AdjListNetWorkVex::AdjListNetWorkVex()
// �������������һ���ն����㡪���޲ι��캯��
{
    firstarc = nullptr;
}

AdjListNetWorkVex::AdjListNetWorkVex(int  val,
                                     AdjListNetworkArc *adj)
// �����������������Ϊval,��Ϊeg�Ķ���
{
    data = val;
    firstarc = adj;
}



// ���������ڽӱ���
class AdjListDirNetwork
{
protected:
// �ڽӱ�����ݳ�Ա:
    int vexNum, vexMaxNum, arcNum;					// ������Ŀ������Ķ��������Ŀ�ͱ���
    AdjListNetWorkVex *vexTable;	// �����
    mutable Status *tag;					        // ��־����
    int infinity;							// ������ֵ

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
    AdjListDirNetwork(int es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE,
                      int infinit = (int)DEFAULT_INFINITY);
    // ������es[]Ϊ��������,�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,
    // infinit��ʾ�����,����Ϊ0����������
    AdjListDirNetwork(int vertexMaxNum = DEFAULT_SIZE,
                      int infinit = (int)DEFAULT_INFINITY);
    // ��������Ķ��������ĿΪvertexMaxNum,infinit��ʾ�����,����Ϊ0��������
    ~AdjListDirNetwork();						 // ��������
    void Clear();			                     // ���������
    bool IsEmpty();                              // �ж��������Ƿ�Ϊ��
    int GetOrder(int &d) const;             // �󶥵�����
    Status GetElem(int v, int &d) const;    // �󶥵��Ԫ��ֵ
    Status SetElem(int v, const int &d);    // ���ö����Ԫ��ֵ
    int GetInfinity() const;				 // ȡ������ֵ
    int GetVexNum() const;						 // ���������Ķ������
    int GetArcNum() const;						 // ���������ı�������
    int FirstAdjVex(int v) const;				 // ���������ж���v�ĵ�һ���ڽӵ�
    int NextAdjVex(int v1, int v2) const;		 // ���������ж���v1�������v2����һ���ڽӵ�
    void InsertVex(const int &d);			 // ����Ԫ��ֵΪd�Ķ���
    void InsertArc(int v1, int v2, int w);// ����Ӷ���Ϊv1��v2��ȨΪw�ı�
    void DeleteVex(const int &d);			 // ɾ��Ԫ��ֵΪd�Ķ���
    void DeleteArc(int v1, int v2);			     // ɾ���Ӷ���Ϊv1��v2�ı�
    int GetWeight(int v1, int v2) const;	 // ��Ӷ���Ϊv1��v2�ıߵ�Ȩֵ
    void SetWeight(int v1, int v2, int w);// ���ôӶ���Ϊv1��v2�ıߵ�Ȩֵ
    Status GetTag(int v) const;				     // �󶥵�v�ı�־
    void SetTag(int v, Status tag) const;	     // ���ö���v�ı�־Ϊtag
    AdjListDirNetwork(const AdjListDirNetwork &copy);	// ���ƹ��캯��
    AdjListDirNetwork &operator =
            (const AdjListDirNetwork &copy); // ���ظ�ֵ�����
    void Display();	// ��ʾ�������ڽӱ�
};

// ���������ڽӱ����ʵ�ֲ���
AdjListDirNetwork::AdjListDirNetwork(int es[],
                                     int vertexNum, int vertexMaxNum, int infinit)
// ������������춥������Ϊes[],������ΪnumVex,�������ΪvertexNum,infinit��ʾ�����,����Ϊ0��������
{
    if (vertexMaxNum < 0)
        throw Error("the number of allowed nodes cannot be a negative number!");        // �׳��쳣

    if (vertexMaxNum < vertexNum)
        throw Error("number of nodes cannot bigger than allowed!");// �׳��쳣

    vexNum = vertexNum;
    vexMaxNum = vertexMaxNum;
    arcNum = 0;
    infinity = infinit;

    tag = new Status[vexMaxNum];
    vexTable = new AdjListNetWorkVex[vexMaxNum];

    for (int v = 0; v < vexNum; v++)  {
        tag[v] = UNVISITED;
        vexTable[v].data = es[v];
        vexTable[v].firstarc = nullptr;
    }
}


AdjListDirNetwork::AdjListDirNetwork(int vertexMaxNum, int infinit)
// ������������춥�������ĿΪvertexMaxNum,infinit��ʾ�����Ŀ�������
{
    if (vertexMaxNum < 0)
        throw Error("the number of allowed nodes cannot be a negative number!");// �׳��쳣

    vexNum = 0;
    vexMaxNum = vertexMaxNum;
    arcNum = 0;
    infinity = infinit;

    tag = new Status[vexMaxNum];
    vexTable = new AdjListNetWorkVex[vexMaxNum];
}


AdjListDirNetwork::~AdjListDirNetwork()
// ����������ͷ��ڽӱ���������ռ�ÿռ�
{
    Clear();                                // �ͷű߽��
    delete []tag;							// �ͷű�־
    delete []vexTable;						// �ͷ��ڽӱ�
}


void AdjListDirNetwork::Clear()
// ����������ͷ����еı߽�㣬�����������Ķ������ͱ�������Ϊ0.
{
    AdjListNetworkArc *p;
    for (int v = 0; v < vexNum; v++)	{	// �ͷű߽��
        p = vexTable[v].firstarc;
        while (p != nullptr) {
            vexTable[v].firstarc = p->nextarc;
            delete p;
            p = vexTable[v].firstarc;
        }
    }
    vexNum = 0;
    arcNum = 0;
}


bool AdjListDirNetwork::IsEmpty()
// ������������������Ϊ�շ���true,���򷵻�false.
{
    return vexNum == 0;
}


int AdjListDirNetwork::GetOrder(int &d) const
// ����������󶥵�d�����.�������Ŵ�0��ʼ��ͼ�в����ڶ���dʱ����-1.
{
    int v;
    for (v = 0; v < vexNum; v++)
        if (d == vexTable[v].data)
            break;

    if (v < 0 || v >= vexNum)
        return -1;	// ����d������,����-1
    else
        return v;	// ����d������,�����������
}


Status AdjListDirNetwork::GetElem(int v, int &d) const
// ��������������Ϊv�Ķ���ֵ, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
//	ͨ��dȡ�ö���ֵ��������ENTRY_FOUND������������NOT_PRESENT
{
    if (v < 0 || v >= vexNum)
        return NOT_PRESENT;			// Ԫ�ز�����
    else	{
        d = vexTable[v].data;		// ������v��Ԫ��ֵ����d
        return ENTRY_FOUND;			// Ԫ�ش���
    }
}


Status AdjListDirNetwork::SetElem(int v, const int &d)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
    if (v < 0 || v >= vexNum)
        return RANGE_ERROR;			// λ�ô�
    else	{
        vexTable[v].data = d;		// ����Ԫ��
        return SUCCESS;				// �ɹ�
    }
}


int AdjListDirNetwork::GetInfinity() const
// �������������������ֵ
{
    return infinity;
}


int AdjListDirNetwork::GetVexNum() const
// ������������ض������
{
    return vexNum;
}


int AdjListDirNetwork::GetArcNum() const
// ������������ر�������
{
    return arcNum;
}


int AdjListDirNetwork::FirstAdjVex(int v) const
// ������������ض���v�ĵ�һ���ڽӵ�
{
    if (v < 0 || v >= vexNum)
        throw Error("v is illegal!");// �׳��쳣

    if (vexTable[v].firstarc == nullptr)
        return -1;              // �������ڽӵ�
    else
        return vexTable[v].firstarc->adjVex;
}


int AdjListDirNetwork::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�
{
    AdjListNetworkArc *p;
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 is illegal!");	// �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 is illegal!");	// �׳��쳣
    if (v1 == v2)
        throw Error("v1 cannot equals to v2!");// �׳��쳣

    p = vexTable[v1].firstarc;
    while (p != nullptr && p->adjVex != v2)
        p = p->nextarc;

    if (p == nullptr || p->nextarc == nullptr)
        return -1;                   // ��������һ���ڽӵ�
    else
        return p->nextarc->adjVex;
}


void AdjListDirNetwork::InsertVex(const int &d)
// ����������ڶ����ı�β����Ԫ��ֵΪd�Ķ��㡣
{
    if (vexNum == vexMaxNum)
        throw Error("number of nodes cannot bigger than allowed!");	// �׳��쳣

    vexTable[vexNum].data = d;
    vexTable[vexNum].firstarc = nullptr;
    tag[vexNum] = UNVISITED;
    vexNum++;
}


void AdjListDirNetwork::InsertArc(int v1, int v2, int w)
// ������������붥��Ϊv1��v2,ȨΪw�ı�
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 is illegal!");	// �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 is illegal!");	// �׳��쳣
    if (v1 == v2)
        throw Error("v1 cannot equals to v2!");// �׳��쳣
    if (w == infinity)
        throw Error("w cannot be infinity!");// �׳��쳣

    AdjListNetworkArc *p, *q;
    p = vexTable[v1].firstarc;
    vexTable[v1].firstarc = new AdjListNetworkArc(v2, w, p);
    arcNum++;
}


void AdjListDirNetwork::DeleteVex(const int &d)
// ���������ɾ��Ԫ��ֵΪd�Ķ���
{
    int v;
    AdjListNetworkArc *p, *q;
    for (v = 0; v < vexNum; v++)
        if	(vexTable[v].data == d)
            break;
    if (v == vexNum)
        throw Error("there is no node need to be deleted!");	// �׳��쳣

    for (int u = 0; u < vexNum; u++)           // ɾ������d�Ļ�
        if (u != v)
            DeleteArc(u, v);

    p = vexTable[v].firstarc;                  // ɾ����d�����Ļ�
    while (p != nullptr) {
        vexTable[v].firstarc = p->nextarc;
        delete p;
        p = vexTable[v].firstarc;
        arcNum--;
    }

    vexNum--;
    vexTable[v].data = vexTable[vexNum].data;
    vexTable[v].firstarc = vexTable[vexNum].firstarc;
    vexTable[vexNum].firstarc = nullptr;
    tag[v] = tag[vexNum];

    for (int u = 0; u < vexNum; u++)
        if (u != v) {
            p = vexTable[u].firstarc;
            while (p != nullptr) {
                if (p->adjVex == vexNum)
                    p->adjVex = v;
                p = p->nextarc;
            }
        }
}


void AdjListDirNetwork::DeleteArc(int v1, int v2)
// ���������ɾ������Ϊv1��v2�ı�
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 is illegal!");	// �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 is illegal!");	// �׳��쳣
    if (v1 == v2) throw
                Error("v1 cannot equals to v2!");		// �׳��쳣

    AdjListNetworkArc *p, *q;
    p = vexTable[v1].firstarc;
    while (p != nullptr && p->adjVex != v2) {
        q = p;
        p = p->nextarc;
    }
    if (p != nullptr) {
        if (vexTable[v1].firstarc == p)
            vexTable[v1].firstarc = p->nextarc;
        else
            q->nextarc = p->nextarc;
        delete p;
        arcNum--;
    }
}


int AdjListDirNetwork::GetWeight(int v1, int v2) const
// ������������ض���Ϊv1��v2�ıߵ�Ȩֵ
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 is illegal!");	// �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 is illegal!");	// �׳��쳣

    AdjListNetworkArc *p;
    p = vexTable[v1].firstarc;
    while (p != nullptr && p->adjVex != v2)
        p = p->nextarc;
    if (p != nullptr)
        return p->weight;			// ����Ȩֵ
    else
        return infinity;				// ����ȨֵΪinfinity����ʾ�߲�����
}


void AdjListDirNetwork::SetWeight(int v1, int v2, int w)
// ������������ö���Ϊv1��v2�ıߵ�Ȩֵ
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 is illegal!");        // �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 is illegal!");	    // �׳��쳣
    if (v1 == v2)
        throw Error("v1 cannot equals to v2!");    // �׳��쳣
    if (w == infinity)
        throw Error("w cannot be infinity!");   // �׳��쳣

    AdjListNetworkArc *p;
    p = vexTable[v1].firstarc;
    while (p != nullptr && p->adjVex != v2)
        p = p->nextarc;
    if (p != nullptr)
        p->weight = w;		            // �޸�Ȩֵ
}


Status AdjListDirNetwork::GetTag(int v) const
// ������������ض���v�ı�־
{
    if (v < 0 || v >= vexNum)
        throw Error("v���Ϸ�!");		// �׳��쳣

    return tag[v];
}


void AdjListDirNetwork::SetTag(int v, Status val) const
// ������������ö���v�ı�־Ϊval
{
    if (v < 0 || v >= vexNum)
        throw Error("v���Ϸ�!");		// �׳��쳣

    tag[v] = val;
}


AdjListDirNetwork::AdjListDirNetwork(const AdjListDirNetwork &copy)
// ��������������������ڽӾ���copy���������������ڽӾ���copy�������ƹ��캯��
{
    AdjListNetworkArc *p, *q;
    infinity =copy.infinity;
    vexNum = copy.vexNum;
    vexMaxNum = copy.vexMaxNum;
    arcNum = copy.arcNum;

    tag = new Status[vexMaxNum];
    vexTable = new AdjListNetWorkVex[vexMaxNum];
    for (int v = 0; v < vexNum; v++)	{
        tag[v] = copy.tag[v];
        vexTable[v].data = copy.vexTable[v].data;
        vexTable[v].firstarc = nullptr;
        p = copy.vexTable[v].firstarc;
        while (p != nullptr)
            if (vexTable[v].firstarc == nullptr) {
                vexTable[v].firstarc = new AdjListNetworkArc(p->adjVex, p->weight);
                q = vexTable[v].firstarc;
                p = p->nextarc;
            }
            else {
                q->nextarc = new AdjListNetworkArc(p->adjVex, p->weight);
                q = q->nextarc;
                p = p->nextarc;
            }
    }
}


AdjListDirNetwork &AdjListDirNetwork::operator =(const AdjListDirNetwork &copy)
// ��������������������ڽӾ���copy��ֵ����ǰ���������ڽӾ��󡪡���ֵ�������
{
    if (&copy != this)
    {
        Clear();                                    // �ͷŵ�ǰ�������߽��
        delete []tag;								// �ͷŵ�ǰ��������־����
        delete []vexTable;							// �ͷŵ�ǰ�����������

        AdjListNetworkArc *p, *q;
        infinity =copy.infinity;
        vexNum = copy.vexNum;
        vexMaxNum = copy.vexMaxNum;
        arcNum = copy.arcNum;

        tag = new Status[vexMaxNum];
        vexTable = new AdjListNetWorkVex[vexMaxNum];
        for (int v = 0; v < vexNum; v++)	{
            tag[v] = copy.tag[v];
            vexTable[v].data = copy.vexTable[v].data;
            vexTable[v].firstarc = nullptr;
            p = copy.vexTable[v].firstarc;
            while (p != nullptr)
                if (vexTable[v].firstarc == nullptr) {
                    vexTable[v].firstarc = new AdjListNetworkArc(p->adjVex, p->weight);
                    q = vexTable[v].firstarc;
                    p = p->nextarc;
                }
                else {
                    q->nextarc = new AdjListNetworkArc(p->adjVex, p->weight);
                    q = q->nextarc;
                    p = p->nextarc;
                }
        }
    }
    return *this;
}


void AdjListDirNetwork::Display()
// �������: ��ʾ�ڽӾ���������
{
    AdjListNetworkArc *p;
    cout << "Directed graph has " << vexNum << " nodes, " << arcNum << " edges." << endl;
    for (int v = 0; v < vexNum; v++)	{	// ��ʾ��v���ڽ�����
        cout << v << ":\t" << vexTable[v].data;				// ��ʾ�����
        p = vexTable[v].firstarc;
        while (p != nullptr) {
            cout << "-->(" << p->adjVex << "," << p->weight << ")";
            p = p->nextarc;
        }
        cout << endl;
    }
}






void ShortestPathFloyd(const AdjListDirNetwork &g, int **path,
                       int **dist)
// �������: ��Floyd�㷨��������g�и��Զ���u��v֮������·��path[u][v]��·������
//	dist[u][v],path[u][v]�洢��u��v�����·�������˶����ǰһ����Ķ����,dist[u][v]
//	�洢��u��v�����·���ĳ���
{
    for (int u = 0; u < g.GetVexNum(); u++)
        for (int v = 0; v < g.GetVexNum(); v++)
        {	// ��ʼ��path��dist
            dist[u][v] = (u != v) ? g.GetWeight(u, v) : 0;
            if (u != v && dist[u][v] < g.GetInfinity())
                path[u][v] = u;	// ���ڱ�<u,v>
            else
                path[u][v] = -1;											// �����ڱ�<u,v>
        }

    for (int k = 0; k < g.GetVexNum(); k++)
        for (int i = 0; i < g.GetVexNum(); i++)
            for (int j = 0; j < g.GetVexNum(); j++)
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    // ��i��k�ٵ�j��·�����ȸ���
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
}


void DisplayPathAndDist(const AdjListDirNetwork &g, int **path, int **dist)
{
    int e1, e2;
    for (int v1 = 0; v1 < g.GetVexNum(); v1++)
        for (int v2 = 0; v2 < g.GetVexNum(); v2++)
            if (v1 != v2) {
                cout << endl;
                g.GetElem(v1, e1);
                g.GetElem(v2, e2);
                if (dist[v1][v2] < g.GetInfinity() )	{	// ���ڴ�v1��v2���·��
                    cout << "from " << e1 << " to " << e2 << ":";
                    cout << " dist = " << dist[v1][v2];
                    cout << " edge��";
                    LinkStack s;	// �洢·�ϵĶ���
                    int v = v2;
                    while (v != v1)	{
                        s.Push(v);	// vΪ·���ϵĶ���
                        v = path[v1][v];// ȡ��·���ϵ�ǰһ������
                    }
                    s.Push(v1);		// v��·������ʼ��
                    while (!s.IsEmpty())		{	// ���·�ϵĶ���
                        s.Pop(v);
                        g.GetElem(v, e1);
                        cout << e1 << " ";
                    }
                }
                else 	{	// ��v1��v2��·��
                    cout << "from " << e1 << " to " << e2 << ":";
                    cout << " none path";
                }
            }
    cout << endl;
}

// /////////////////////////////////////////////////////////////////////////



// ����ͼ���ڽӾ�����

class AdjMatrixUndirNetwork
{
protected:
// �ڽӾ�������ݳ�Ա:
    int vexNum, vexMaxNum, edgeNum;			// ������Ŀ������Ķ��������Ŀ�ͱ���
    int **arcs;							// ��ű���Ϣ�ڽӾ���
    int *vertexes;						// ��Ŷ�����Ϣ������
    Status *tag;							// ��־����
    int infinity;					// �����

public:
// �ڽӾ������͵ķ�������:
    AdjMatrixUndirNetwork(int es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE,
                          int infinit = (int)DEFAULT_INFINITY);
    // ������es[]Ϊ����,�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
    AdjMatrixUndirNetwork(int vertexMaxNum = DEFAULT_SIZE, int infinit = (int)DEFAULT_INFINITY);
    // ��������Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
    ~AdjMatrixUndirNetwork();					// ��������
    void Clear();			              // ���ͼ
    bool IsEmpty();                 // �ж�����ͼ�Ƿ�Ϊ��
    int GetOrder(int &e) const;// �󶥵�����
    Status GetElem(int v, int &e) const;// �󶥵��Ԫ��ֵ
    Status SetElem(int v, const int &e);// ���ö����Ԫ��ֵ
    int GetInfinity() const;				// ���������
    int GetVexNum() const;					// ���ض������
    int GetEdgeNum() const;					// ���ر���
    int FirstAdjVex(int v) const;		// ���ض���v�ĵ�һ���ڽӵ�
    int NextAdjVex(int v1, int v2) const;		 // ���ض���v1�������v2����һ���ڽӵ�
    void InsertVex(const int &e);			 // ����Ԫ��ֵΪe�Ķ���
    void DeleteVex(const int &e);			 // ɾ��Ԫ��ֵΪe�Ķ���
    void InsertArc(int v1, int v2, int w);	// ���붥��Ϊv1��v2,ȨΪw�ı�
    void DeleteArc(int v1, int v2);			// ɾ������Ϊv1��v2�ı�
    int GetWeight(int v1, int v2) const;	// ���ض���Ϊv1��v2�ıߵ�Ȩֵ
    Status GetTag(int v) const;			         // ���ض���v�ı�־
    void SetTag(int v, Status val) const;	   // ���ö���v�ı�־Ϊval
    AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork &g);	// ���ƹ��캯��
    AdjMatrixUndirNetwork &operator =(const AdjMatrixUndirNetwork &g);
    // ��ֵ�������
    void Display();	                         // ��ʾ�ڽӾ�������ͼ
};

// ����ͼ���ڽӾ������ʵ�ֲ���

AdjMatrixUndirNetwork::AdjMatrixUndirNetwork(int es[], int vertexNum, int vertexMaxNum, int infinit)
// �����������������Ԫ��Ϊes[],�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
{
    if (vertexMaxNum < 0)
        throw Error("����Ķ��������Ŀ����Ϊ��!");        // �׳��쳣

    if (vertexMaxNum < vertexNum)
        throw Error("������Ŀ���ܴ�������Ķ��������Ŀ!");// �׳��쳣

    vexNum = vertexNum;
    vexMaxNum = vertexMaxNum;
    edgeNum = 0;
    infinity = infinit;

    vertexes = new int[vexMaxNum];     	// �������ɶ�����Ϣ����
    tag = new Status[vexMaxNum];			 	// ���ɱ�־����
    arcs = (int **)new int *[vexMaxNum];     	// �����ڽӾ���
    for (int v = 0; v < vexMaxNum; v++)
        arcs[v] = new int[vexMaxNum];

    for (int v = 0; v < vexNum; v++) {
        vertexes[v] = es[v];
        tag[v] = UNVISITED;
        for (int u = 0; u < vexNum; u++)
            arcs[v][u] = infinity;
        arcs[v][v] = 0;
    }
}


AdjMatrixUndirNetwork::AdjMatrixUndirNetwork(int vertexMaxNum, int infinit)
// �������������������������ĿΪvertexMaxNum�Ŀ�����ͼ
{
    if (vertexMaxNum < 0)
        throw Error("����Ķ��������Ŀ����Ϊ��!");// �׳��쳣

    vexNum = 0;
    vexMaxNum = vertexMaxNum;
    edgeNum = 0;
    infinity = infinit;

    vertexes = new int[vexMaxNum];     // �������ɶ�����Ϣ����
    tag = new Status[vexMaxNum];			      // ���ɱ�־����
    arcs = (int **)new int *[vexMaxNum];    // �����ڽӾ���
    for (int v = 0; v < vexMaxNum; v++)
        arcs[v] = new int[vexMaxNum];
}


void AdjMatrixUndirNetwork::Clear()
// ���������������ͼ�Ķ������ͱ�������Ϊ0.
{
    vexNum = 0;
    edgeNum = 0;
}


bool AdjMatrixUndirNetwork::IsEmpty()
// ����������������ͼΪ�շ���true,���򷵻�false.
{
    return vexNum == 0;
}


AdjMatrixUndirNetwork::~AdjMatrixUndirNetwork()
// ����������ͷŶ�����ռ�õĿռ�
{
    delete []vertexes;					// �ͷŶ�������
    delete []tag;						    // �ͷű�־

    for (int v = 0; v < vexMaxNum; v++)	// �ͷ��ڽӾ������
        delete []arcs[v];
    delete []arcs;					    // �ͷ��ڽӾ���
}


int AdjMatrixUndirNetwork::GetOrder(int &e) const
// ����������󶥵�e�����.�������Ŵ�0��ʼ��ͼ�в����ڶ���eʱ������-1.
{
    for (int v = 0; v < vexNum; v++)
        if (vertexes[v] == e)
            return v;	    // ����e����,�����������
    return -1;	        // ����e������,����-1
}


Status AdjMatrixUndirNetwork::GetElem(int v, int &e) const
// ��������������Ϊv�Ķ���ֵ, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
// ͨ��eȡ�ö���ֵ��������ENTRY_FOUND������������NOT_PRESENT
{
    if (v < 0 || v >= vexNum)
        return NOT_PRESENT;	// v��Χ��,����Ԫ�ز�����
    else	{
        e = vertexes[v];	  // ������v��Ԫ��ֵ����e
        return ENTRY_FOUND;	// ����Ԫ�ش���
    }
}


Status AdjMatrixUndirNetwork::SetElem(int v, const int &e)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
    if (v < 0 || v >= vexNum)
        return RANGE_ERROR;	// v��Χ��,����λ�ô�
    else	{
        vertexes[v] = e;		// ������Ԫ�ص�ֵ��Ϊe
        return SUCCESS;		  // �����޸ĳɹ�
    }
}


int AdjMatrixUndirNetwork::GetInfinity() const
// ������������������
{
    return infinity;
}


int AdjMatrixUndirNetwork::GetVexNum() const
// ������������ض������
{
    return vexNum;
}


int AdjMatrixUndirNetwork::GetEdgeNum() const
// ������������ر���
{
    return edgeNum;
}


int AdjMatrixUndirNetwork::FirstAdjVex(int v) const
// ������������ض���v�ĵ�1���ڽӵ�����
{
    if (v < 0 || v >= vexNum)
        throw Error("v���Ϸ�!");// �׳��쳣

    for (int u = 0; u < vexNum; u++)
        if (arcs[v][u] != 0 && arcs[v][u] != infinity)
            return u;

    return -1;					// ����-1��ʾ���ڽӵ�
}


int AdjMatrixUndirNetwork::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1���Ϸ�!");	// �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2���Ϸ�!");	// �׳��쳣
    if (v1 == v2) throw
                Error("v1���ܵ���v2!");		// �׳��쳣

    for (int u = v2 + 1; u < vexNum; u++)
        if (arcs[v1][u] != 0 && arcs[v1][u] != infinity)
            return u;

    return -1;						// ����-1��ʾ����һ���ڽӵ�
}


void AdjMatrixUndirNetwork::InsertVex(const int &e)
// ������������붥��e
{
    if (vexNum == vexMaxNum)
        throw Error("ͼ�Ķ��������ܳ�������������!");	// �׳��쳣

    vertexes[vexNum] = e;
    tag[vexNum] = UNVISITED;

    for (int v = 0; v < vexNum; v++) {
        arcs[vexNum][v] = infinity;
        arcs[v][vexNum] = infinity;
    }
    arcs[vexNum][vexNum] = 0;
    vexNum++;
}


void AdjMatrixUndirNetwork::InsertArc(int v1, int v2, int w)
// ���������������������v1��v2�ı�
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1���Ϸ�!");	// �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2���Ϸ�!");	// �׳��쳣
    if (v1 == v2)
        throw Error("v1���ܵ���v2!");// �׳��쳣

    if (arcs[v1][v2] == infinity)	{	  // ԭ����ͼ��û�б�(v1, v2)
        edgeNum++;
        arcs[v1][v2] = w;
        arcs[v2][v1] = w;
    }
}


void AdjMatrixUndirNetwork::DeleteVex(const int &e)
// ���������ɾ��Ԫ��Ϊe�Ķ���
{
    int v;
    for (v = 0; v < vexNum; v++)
        if	(vertexes[v] == e)
            break;
    if (v == vexNum)
        throw Error("ͼ�в�����Ҫɾ���Ķ���!");	// �׳��쳣

    for (int u = 0; u < vexNum; u++)             // ɾ���붥��e������ı�
        if (u != v && arcs[v][u] != infinity) {
            edgeNum--;
            arcs[v][u] = infinity;
            arcs[u][v] = infinity;
        }

    vexNum--;
    if (v < vexNum) {
        vertexes[v] = vertexes[vexNum];
        tag[v] = tag[vexNum];
        for (int u = 0; u <= vexNum; u++)
            arcs[v][u] = arcs[vexNum][u];
        for (int u = 0; u <= vexNum; u++)
            arcs[u][v] = arcs[u][vexNum];
    }
}


void AdjMatrixUndirNetwork::DeleteArc(int v1, int v2)
// ���������ɾ����������v1��v2�ı�
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1���Ϸ�!");	// �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2���Ϸ�!");	// �׳��쳣
    if (v1 == v2)
        throw Error("v1���ܵ���v2!");// �׳��쳣

    if (arcs[v1][v2] != infinity)	{	// ԭ����ͼ���ڱ�(v1, v2)
        edgeNum--;
        arcs[v1][v2] = infinity;
        arcs[v2][v1] = infinity;
    }
}


int AdjMatrixUndirNetwork::GetWeight(int v1, int v2) const
// ������������ض���Ϊv1��v2�ıߵ�Ȩֵ
{
    if (v1 < 0 || v1 >= vexNum) throw Error("v1���Ϸ�!");	// �׳��쳣
    if (v2 < 0 || v2 >= vexNum) throw Error("v2���Ϸ�!");	// �׳��쳣

    return arcs[v1][v2];
}


Status AdjMatrixUndirNetwork::GetTag(int v) const
// ������������ض���v�ı�־
{
    if (v < 0 || v >= vexNum)
        throw Error("v���Ϸ�!");	// �׳��쳣

    return tag[v];
}


void AdjMatrixUndirNetwork::SetTag(int v, Status val) const
// ������������ö���v�ı�־Ϊval
{
    if (v < 0 || v >= vexNum)
        throw Error("v���Ϸ�!");	// �׳��쳣

    tag[v] = val;
}


AdjMatrixUndirNetwork::AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork &g)
// ���������������ͼ���ڽӾ���g����������ͼ���ڽӾ���g�������ƹ��캯��
{
    vexNum = g.vexNum;
    vexMaxNum = g.vexMaxNum;
    edgeNum = g.edgeNum;
    infinity = g.infinity;

    vertexes = new int[vexMaxNum];		// ���ɶ�����������
    tag = new Status[vexMaxNum];			// ���ɱ�־����
    arcs = (int **)new int *[vexMaxNum];	// �����ڽӾ���
    for (int v = 0; v < vexMaxNum; v++)
        arcs[v] = new int[vexMaxNum];

    for (int v = 0; v < vexNum; v++)	{	// ���ƶ�����������
        vertexes[v] = g.vertexes[v];
        tag[v] = g.tag[v];
        for (int u = 0; u < vexNum; u++)
            arcs[v][u] = g.arcs[v][u];
    }
}


AdjMatrixUndirNetwork &AdjMatrixUndirNetwork::operator =(const AdjMatrixUndirNetwork &g)
// ���������������ͼ���ڽӾ���g��ֵ����ǰ����ͼ���ڽӾ��󡪡���ֵ�������
{
    if (&g != this)	{
        delete []vertexes;				// �ͷŶ�������
        delete []tag;						  // �ͷű�־

        for (int v = 0; v < vexMaxNum; v++)	// �ͷ��ڽӾ������
            delete []arcs[v];
        delete []arcs;					  // �ͷ��ڽӾ���
        vexNum = g.vexNum;
        vexMaxNum = g.vexMaxNum;
        edgeNum = g.edgeNum;
        infinity = g.infinity;

        vertexes = new int[vexMaxNum];	 // ���ɶ�����������
        tag = new Status[vexMaxNum];			   // ���ɱ�־����
        arcs = (int **)new int *[vexMaxNum]; // �����ڽӾ���
        for (int v = 0; v < vexMaxNum; v++)
            arcs[v] = new int[vexMaxNum];

        for (int v = 0; v < vexNum; v++)	{	 // ���ƶ�����������
            vertexes[v] = g.vertexes[v];
            tag[v] = g.tag[v];
            for (int u = 0; u < vexNum; u++)
                arcs[v][u] = g.arcs[v][u];
        }
    }
    return *this;
}


void AdjMatrixUndirNetwork::Display()
// �������: ��ʾ�ڽӾ�������ͼ
{

    for (int v = 0; v < vexNum; v++)
        cout << "\t" << vertexes[v];
    cout << endl;

    for (int v = 0; v < vexNum; v++)	{
        cout << vertexes[v];
        for (int u = 0; u < vexNum; u++)
            if (arcs[v][u] == infinity)
                cout << "\t" << "��";
            else
                cout << "\t" << arcs[v][u];
        cout << endl;
    }
}







struct CloseArcType {
    int lowweight;
    int nearvertex;
};


void MiniSpanTreePrim(const AdjMatrixUndirNetwork &g, int u0)
// ��ʼ������������g,u0Ϊg��һ������
// �����������Prim�㷨��u0����������g����С����������
{
    int min;
    int v1, v2;
    int vexnum = g.GetVexNum();
    CloseArcType * closearc;

    if (u0 < 0 || u0 >= vexnum)
        throw Error("����u0������!"); // �׳��쳣

    int u, v, k;						// ��ʾ�������ʱ����
    closearc = new CloseArcType[vexnum];	// ����洢�ռ�
    for (v = 0; v < vexnum; v++)	{	// ��ʼ����������adjVex�����Զ�������־����ʱU = {v0}
        closearc[v].nearvertex = u0;
        closearc[v].lowweight = g.GetWeight(u0, v);
    }
    closearc[u0].nearvertex = -1;
    closearc[u0].lowweight = 0;

    for (k = 1; k < vexnum; k++) {	// ѡ��������������g.GetVexNum() - 1������
        min = g.GetInfinity();
        v = u0;// ѡ��ʹ�ñ�<w, adjVex[w]>Ϊ����V-U��U�ľ�����СȨֵ�ı�
        for (u = 0; u < vexnum; u++)
            if (closearc[u].lowweight != 0 && closearc[u].lowweight < min) {
                v = u;
                min = closearc[u].lowweight;
            }
        if (v != u0) {
            g.GetElem(closearc[v].nearvertex, v1);
            g.GetElem(v, v2);
            cout << "��:( " << v1 << ", " <<  v2 << " ) Ȩ:" << min << endl ; // ����߼�Ȩֵ
            closearc[v].lowweight = 0;		// ��w����U
            for (u = g.FirstAdjVex(v); u != -1 ; u = g.NextAdjVex(v, u)) 	// �¶��㲢��U������ѡ����С��
                if (closearc[u].lowweight != 0 && (g.GetWeight(v, u) < closearc[u].lowweight))	{	// <v, w>Ϊ�µ���С��
                    closearc[u].lowweight = g.GetWeight(v, u);
                    closearc[u].nearvertex = v;
                }
        }

    }
    delete []closearc;			// �ͷŴ洢�ռ�
}





// /////////////////////////////////////////////////////////////////////////

#endif