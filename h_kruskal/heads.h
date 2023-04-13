#ifndef __HEADS_H__
#define __HEADS_H__

#include "assistance.h"

// 结点类

struct Node
{
// 数据成员:
    int data;				// 数据域
    Node *next;		// 指针域

// 构造函数:
    Node();						// 无参数的构造函数
    Node(int item, Node *link = nullptr);	// 已知数数据元素值和指针建立结构
};

// 结点类的实现部分

Node::Node()
// 操作结果：构造指针域为空的结点
{
    next = nullptr;
}

Node::Node(int item, Node *link)
// 操作结果：构造一个数据域为item和指针域为link的结点
{
    data = item;
    next = link;
}

// 链栈类

class LinkStack
{
protected:
//  链栈的数据成员:
    Node *top;							// 栈顶指针

public:
//  链栈的函数成员:
    LinkStack();									// 无参数的构造函数
    virtual ~LinkStack();							// 析构函数
    int GetLength() const;							// 求栈长度
    bool IsEmpty() const;							// 判断栈是否为空
    void Clear();									// 将栈清空
    void Traverse(void (*Visit)(const int &)) const ;	// 遍历栈
    Status Push(const int e);					// 入栈
    Status Top(int &e) const;					// 返回栈顶元素
    Status Pop(int &e);						// 出栈
    LinkStack(const LinkStack &s);		// 复制构造函数
    LinkStack &operator =(const LinkStack &s); // 赋值语句重载
};


// 链栈类的实现部分

LinkStack::LinkStack()
// 操作结果：构造一个空栈表
{
    top = nullptr;
}


LinkStack::~LinkStack()
// 操作结果：销毁栈
{
    Clear();
}


int LinkStack::GetLength() const
// 操作结果：返回栈元素个数
{
    int count = 0;		// 计数器
    Node *p;
    for (p = top; p != nullptr; p = p->next)		// 用p依次搜寻每个元素
        count++;		// 统计链栈中结点数
    return count;
}


bool LinkStack::IsEmpty() const
// 操作结果：如栈为空，则返回true，否则返回false
{
    return top == nullptr;
}


void LinkStack::Clear()
// 操作结果：清空栈
{
    Node *p;
    while (top != nullptr) {
        p = top;
        top = top->next;
        delete p;
    }
}


void LinkStack::Traverse(void (*Visit)(const int &)) const
// 操作结果：从栈顶到栈底依次对栈的每个元素调用函数(*visit)访问
{
    Node *p;
    for (p = top; p != nullptr; p = p->next)	// 用p依次搜寻当前栈的每个元素
        (*Visit)(p->data);		// 对p所指向的元素调用函数(*visit)访问
}


Status LinkStack::Push(const int e)
// 操作结果：将元素e追加到栈顶,如成功则返加SUCCESS,否则如动态内存已耗尽
//	将返回OVER_FLOW
{
    Node *p = new Node(e, top);
    if (p == nullptr) 	// 系统内存耗尽
        return OVER_FLOW;
    else	{	// 操作成功
        top = p;
        return SUCCESS;
    }
}


Status LinkStack::Top(int &e) const
// 操作结果：如栈非空,用e返回栈顶元素,函数返回SUCCESS,否则函数返回UNDER_FLOW
{
    if(IsEmpty())	// 栈空
        return UNDER_FLOW;
    else	{	// 栈非空,操作成功
        e = top->data;				// 用e返回栈顶元素
        return SUCCESS;
    }
}


Status LinkStack::Pop(int &e)
// 操作结果：如栈非空,删除栈顶元素,并用e返回栈顶元素,函数返回SUCCESS,否则
//	函数返回UNDER_FLOW
{
    if (IsEmpty())	// 栈空
        return UNDER_FLOW;
    else	{	// 操作成功
        Node *p = top;	// 保留原栈顶
        e = top->data;				// 用e返回栈顶元素
        top = top->next;			// 修改栈顶
        delete p;					// 删除原栈顶结点
        return SUCCESS;
    }
}


LinkStack::LinkStack(const LinkStack &s)
// 操作结果：由栈s构造新栈--复制构造函数
{
    if (s.IsEmpty())	// s为空
        top = nullptr;									// 构造一空栈
    else 	{	                                    // s非空,复制栈
        top = new Node(s.top->data);	// 生成当前栈项
        Node *q = top;			        // 设置当前栈底指针
        for (Node *p = s.top->next; p != nullptr; p = p->next){
            q->next = new Node(p->data); // 向栈底追加元素
            q = q->next;					       // 修改栈底指针
        }
    }
}



LinkStack &LinkStack::operator = (const LinkStack &s)
// 操作结果：将栈s赋值给当前栈--赋值语句重载
{
    if (&s != this)	{
        Clear();			// 清空当前栈
        if (!s.IsEmpty())	{	                            // s非空,复制栈
            top = new Node(s.top->data);       // 生成当前栈项
            Node *q = top;			            // 设置当前栈底指针
            for (Node *p = s.top->next; p != nullptr; p = p->next){
                q->next = new Node(p->data);      // 向栈底追加元素
                q = q->next;			                    // 修改栈底指针
            }
        }
    }
    return *this;
}



// 邻接表网边数据类
struct AdjListNetworkArc
{
// 数据成员:
    int adjVex;								// 弧头顶点序号
    int weight;						// 边的权值
    AdjListNetworkArc *nextarc; // 下一条边结点的指针
// 构造函数:
    AdjListNetworkArc();					// 无参数的构造函数
    AdjListNetworkArc(int v, int w, AdjListNetworkArc * next = NULL);
    // 构造邻接点为v，权为w的邻接边
};

// 邻接表网边数据类的实现部分

AdjListNetworkArc::AdjListNetworkArc()
// 操作结果：构造一个空邻接表边结点边——无参构造函数
{
    adjVex = -1;
}


AdjListNetworkArc::AdjListNetworkArc(int v, int w, AdjListNetworkArc *next)
// 操作结果：构造邻接点序号为v，边的权为w，下一条边结点的指针为next的邻接边
{
    adjVex = v;
    weight = w;
    nextarc = next;
}

// 邻接表网顶点结点类

struct AdjListNetWorkVex
{
// 数据成员:
    int data;						// 数据元素值
    AdjListNetworkArc *firstarc;
    // 指向邻接链表边结点的指针

// 构造函数:
    AdjListNetWorkVex();				// 无参数的构造函数
    AdjListNetWorkVex(int val,
                      AdjListNetworkArc *adj = nullptr);
    // 有参数的构造函数
};

// 邻接表网顶点结点类的实现部分

AdjListNetWorkVex::AdjListNetWorkVex()
// 操作结果：构造一个空顶点结点——无参构造函数
{
    firstarc = nullptr;
}

AdjListNetWorkVex::AdjListNetWorkVex(int  val,
                                     AdjListNetworkArc *adj)
// 操作结果：构造数据为val,边为eg的顶点
{
    data = val;
    firstarc = adj;
}



// 有向网的邻接表类
class AdjListDirNetwork
{
protected:
// 邻接表的数据成员:
    int vexNum, vexMaxNum, arcNum;					// 顶点数目、允许的顶点最大数目和边数
    AdjListNetWorkVex *vexTable;	// 顶点表
    mutable Status *tag;					        // 标志数组
    int infinity;							// 无穷大的值

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
    AdjListDirNetwork(int es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE,
                      int infinit = (int)DEFAULT_INFINITY);
    // 以数组es[]为顶点数据,顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,
    // infinit表示无穷大,边数为0构造有向网
    AdjListDirNetwork(int vertexMaxNum = DEFAULT_SIZE,
                      int infinit = (int)DEFAULT_INFINITY);
    // 构造允许的顶点最大数目为vertexMaxNum,infinit表示无穷大,边数为0的有向网
    ~AdjListDirNetwork();						 // 析构函数
    void Clear();			                     // 清空有向网
    bool IsEmpty();                              // 判断有向网是否为空
    int GetOrder(int &d) const;             // 求顶点的序号
    Status GetElem(int v, int &d) const;    // 求顶点的元素值
    Status SetElem(int v, const int &d);    // 设置顶点的元素值
    int GetInfinity() const;				 // 取无穷大的值
    int GetVexNum() const;						 // 求有向网的顶点个数
    int GetArcNum() const;						 // 求有向网的边数个数
    int FirstAdjVex(int v) const;				 // 求有向网中顶点v的第一个邻接点
    int NextAdjVex(int v1, int v2) const;		 // 求有向网中顶点v1的相对于v2的下一个邻接点
    void InsertVex(const int &d);			 // 插入元素值为d的顶点
    void InsertArc(int v1, int v2, int w);// 插入从顶点为v1到v2、权为w的边
    void DeleteVex(const int &d);			 // 删除元素值为d的顶点
    void DeleteArc(int v1, int v2);			     // 删除从顶点为v1到v2的边
    int GetWeight(int v1, int v2) const;	 // 求从顶点为v1到v2的边的权值
    void SetWeight(int v1, int v2, int w);// 设置从顶点为v1到v2的边的权值
    Status GetTag(int v) const;				     // 求顶点v的标志
    void SetTag(int v, Status tag) const;	     // 设置顶点v的标志为tag
    AdjListDirNetwork(const AdjListDirNetwork &copy);	// 复制构造函数
    AdjListDirNetwork &operator =
            (const AdjListDirNetwork &copy); // 重载赋值运算符
    void Display();	// 显示有向网邻接表
};

// 有向网的邻接表类的实现部分
AdjListDirNetwork::AdjListDirNetwork(int es[],
                                     int vertexNum, int vertexMaxNum, int infinit)
// 操作结果：构造顶点数据为es[],顶点数为numVex,顶点个数为vertexNum,infinit表示无穷大,边数为0的有向网
{
    if (vertexMaxNum < 0)
        throw Error("the number of allowed nodes cannot be a negative number!");        // 抛出异常

    if (vertexMaxNum < vertexNum)
        throw Error("number of nodes cannot bigger than allowed!");// 抛出异常

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
// 操作结果：构造顶点最大数目为vertexMaxNum,infinit表示无穷大的空有向网
{
    if (vertexMaxNum < 0)
        throw Error("the number of allowed nodes cannot be a negative number!");// 抛出异常

    vexNum = 0;
    vexMaxNum = vertexMaxNum;
    arcNum = 0;
    infinity = infinit;

    tag = new Status[vexMaxNum];
    vexTable = new AdjListNetWorkVex[vexMaxNum];
}


AdjListDirNetwork::~AdjListDirNetwork()
// 操作结果：释放邻接表有向网所占用空间
{
    Clear();                                // 释放边结点
    delete []tag;							// 释放标志
    delete []vexTable;						// 释放邻接表
}


void AdjListDirNetwork::Clear()
// 操作结果：释放所有的边结点，并把有向网的顶点数和边数设置为0.
{
    AdjListNetworkArc *p;
    for (int v = 0; v < vexNum; v++)	{	// 释放边结点
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
// 操作结果：如果有向网为空返回true,否则返回false.
{
    return vexNum == 0;
}


int AdjListDirNetwork::GetOrder(int &d) const
// 操作结果：求顶点d的序号.顶点的序号从0开始，图中不存在顶点d时返回-1.
{
    int v;
    for (v = 0; v < vexNum; v++)
        if (d == vexTable[v].data)
            break;

    if (v < 0 || v >= vexNum)
        return -1;	// 顶点d不存在,返回-1
    else
        return v;	// 顶点d不存在,返回它的序号
}


Status AdjListDirNetwork::GetElem(int v, int &d) const
// 操作结果：求序号为v的顶点值, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数
//	通过d取得顶点值，并返回ENTRY_FOUND；否则函数返回NOT_PRESENT
{
    if (v < 0 || v >= vexNum)
        return NOT_PRESENT;			// 元素不存在
    else	{
        d = vexTable[v].data;		// 将顶点v的元素值赋给d
        return ENTRY_FOUND;			// 元素存在
    }
}


Status AdjListDirNetwork::SetElem(int v, const int &d)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
    if (v < 0 || v >= vexNum)
        return RANGE_ERROR;			// 位置错
    else	{
        vexTable[v].data = d;		// 顶点元素
        return SUCCESS;				// 成功
    }
}


int AdjListDirNetwork::GetInfinity() const
// 操作结果：返回无穷大的值
{
    return infinity;
}


int AdjListDirNetwork::GetVexNum() const
// 操作结果：返回顶点个数
{
    return vexNum;
}


int AdjListDirNetwork::GetArcNum() const
// 操作结果：返回边数个数
{
    return arcNum;
}


int AdjListDirNetwork::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第一个邻接点
{
    if (v < 0 || v >= vexNum)
        throw Error("v is illegal!");// 抛出异常

    if (vexTable[v].firstarc == nullptr)
        return -1;              // 不存在邻接点
    else
        return vexTable[v].firstarc->adjVex;
}


int AdjListDirNetwork::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点
{
    AdjListNetworkArc *p;
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 is illegal!");	// 抛出异常
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 is illegal!");	// 抛出异常
    if (v1 == v2)
        throw Error("v1 cannot equals to v2!");// 抛出异常

    p = vexTable[v1].firstarc;
    while (p != nullptr && p->adjVex != v2)
        p = p->nextarc;

    if (p == nullptr || p->nextarc == nullptr)
        return -1;                   // 不存在下一个邻接点
    else
        return p->nextarc->adjVex;
}


void AdjListDirNetwork::InsertVex(const int &d)
// 操作结果：在顶点表的表尾插入元素值为d的顶点。
{
    if (vexNum == vexMaxNum)
        throw Error("number of nodes cannot bigger than allowed!");	// 抛出异常

    vexTable[vexNum].data = d;
    vexTable[vexNum].firstarc = nullptr;
    tag[vexNum] = UNVISITED;
    vexNum++;
}


void AdjListDirNetwork::InsertArc(int v1, int v2, int w)
// 操作结果：插入顶点为v1和v2,权为w的边
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 is illegal!");	// 抛出异常
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 is illegal!");	// 抛出异常
    if (v1 == v2)
        throw Error("v1 cannot equals to v2!");// 抛出异常
    if (w == infinity)
        throw Error("w cannot be infinity!");// 抛出异常

    AdjListNetworkArc *p, *q;
    p = vexTable[v1].firstarc;
    vexTable[v1].firstarc = new AdjListNetworkArc(v2, w, p);
    arcNum++;
}


void AdjListDirNetwork::DeleteVex(const int &d)
// 操作结果：删除元素值为d的顶点
{
    int v;
    AdjListNetworkArc *p, *q;
    for (v = 0; v < vexNum; v++)
        if	(vexTable[v].data == d)
            break;
    if (v == vexNum)
        throw Error("there is no node need to be deleted!");	// 抛出异常

    for (int u = 0; u < vexNum; u++)           // 删除到达d的弧
        if (u != v)
            DeleteArc(u, v);

    p = vexTable[v].firstarc;                  // 删除从d出发的弧
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
// 操作结果：删除顶点为v1和v2的边
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 is illegal!");	// 抛出异常
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 is illegal!");	// 抛出异常
    if (v1 == v2) throw
                Error("v1 cannot equals to v2!");		// 抛出异常

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
// 操作结果：返回顶点为v1和v2的边的权值
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 is illegal!");	// 抛出异常
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 is illegal!");	// 抛出异常

    AdjListNetworkArc *p;
    p = vexTable[v1].firstarc;
    while (p != nullptr && p->adjVex != v2)
        p = p->nextarc;
    if (p != nullptr)
        return p->weight;			// 返回权值
    else
        return infinity;				// 返回权值为infinity，表示边不存在
}


void AdjListDirNetwork::SetWeight(int v1, int v2, int w)
// 操作结果：设置顶点为v1和v2的边的权值
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 is illegal!");        // 抛出异常
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 is illegal!");	    // 抛出异常
    if (v1 == v2)
        throw Error("v1 cannot equals to v2!");    // 抛出异常
    if (w == infinity)
        throw Error("w cannot be infinity!");   // 抛出异常

    AdjListNetworkArc *p;
    p = vexTable[v1].firstarc;
    while (p != nullptr && p->adjVex != v2)
        p = p->nextarc;
    if (p != nullptr)
        p->weight = w;		            // 修改权值
}


Status AdjListDirNetwork::GetTag(int v) const
// 操作结果：返回顶点v的标志
{
    if (v < 0 || v >= vexNum)
        throw Error("v不合法!");		// 抛出异常

    return tag[v];
}


void AdjListDirNetwork::SetTag(int v, Status val) const
// 操作结果：设置顶点v的标志为val
{
    if (v < 0 || v >= vexNum)
        throw Error("v不合法!");		// 抛出异常

    tag[v] = val;
}


AdjListDirNetwork::AdjListDirNetwork(const AdjListDirNetwork &copy)
// 操作结果：由有向网的邻接矩阵copy构造新有向网的邻接矩阵copy——复制构造函数
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
// 操作结果：将有向网的邻接矩阵copy赋值给当前有向网的邻接矩阵——赋值语句重载
{
    if (&copy != this)
    {
        Clear();                                    // 释放当前有向网边结点
        delete []tag;								// 释放当前有向网标志数组
        delete []vexTable;							// 释放当前有向网顶点表

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
// 操作结果: 显示邻接矩阵有向网
{
    AdjListNetworkArc *p;
    cout << "Directed graph has " << vexNum << " nodes, " << arcNum << " edges." << endl;
    for (int v = 0; v < vexNum; v++)	{	// 显示第v个邻接链表
        cout << v << ":\t" << vexTable[v].data;				// 显示顶点号
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
// 操作结果: 用Floyd算法求有向网g中各对顶点u和v之间的最短路径path[u][v]和路径长度
//	dist[u][v],path[u][v]存储从u到v的最短路径上至此顶点的前一顶点的顶点号,dist[u][v]
//	存储从u到v的最短路径的长度
{
    for (int u = 0; u < g.GetVexNum(); u++)
        for (int v = 0; v < g.GetVexNum(); v++)
        {	// 初始化path和dist
            dist[u][v] = (u != v) ? g.GetWeight(u, v) : 0;
            if (u != v && dist[u][v] < g.GetInfinity())
                path[u][v] = u;	// 存在边<u,v>
            else
                path[u][v] = -1;											// 不存在边<u,v>
        }

    for (int k = 0; k < g.GetVexNum(); k++)
        for (int i = 0; i < g.GetVexNum(); i++)
            for (int j = 0; j < g.GetVexNum(); j++)
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    // 从i到k再到j的路径长度更短
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
                if (dist[v1][v2] < g.GetInfinity() )	{	// 存在从v1到v2最短路径
                    cout << "from " << e1 << " to " << e2 << ":";
                    cout << " dist = " << dist[v1][v2];
                    cout << " edge：";
                    LinkStack s;	// 存储路上的顶点
                    int v = v2;
                    while (v != v1)	{
                        s.Push(v);	// v为路径上的顶点
                        v = path[v1][v];// 取上路径上的前一个顶点
                    }
                    s.Push(v1);		// v是路径上起始点
                    while (!s.IsEmpty())		{	// 输出路上的顶点
                        s.Pop(v);
                        g.GetElem(v, e1);
                        cout << e1 << " ";
                    }
                }
                else 	{	// 从v1到v2无路径
                    cout << "from " << e1 << " to " << e2 << ":";
                    cout << " none path";
                }
            }
    cout << endl;
}

// /////////////////////////////////////////////////////////////////////////



// 无向图的邻接矩阵类

class AdjMatrixUndirNetwork
{
protected:
// 邻接矩阵的数据成员:
    int vexNum, vexMaxNum, edgeNum;			// 顶点数目、允许的顶点最大数目和边数
    int **arcs;							// 存放边信息邻接矩阵
    int *vertexes;						// 存放顶点信息的数组
    Status *tag;							// 标志数组
    int infinity;					// 无穷大

public:
// 邻接矩阵类型的方法声明:
    AdjMatrixUndirNetwork(int es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE,
                          int infinit = (int)DEFAULT_INFINITY);
    // 以数组es[]为顶点,顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,边数为0的无向图
    AdjMatrixUndirNetwork(int vertexMaxNum = DEFAULT_SIZE, int infinit = (int)DEFAULT_INFINITY);
    // 构造允许的顶点最大数目为vertexMaxNum,边数为0的无向图
    ~AdjMatrixUndirNetwork();					// 析构函数
    void Clear();			              // 清空图
    bool IsEmpty();                 // 判断无向图是否为空
    int GetOrder(int &e) const;// 求顶点的序号
    Status GetElem(int v, int &e) const;// 求顶点的元素值
    Status SetElem(int v, const int &e);// 设置顶点的元素值
    int GetInfinity() const;				// 返回无穷大
    int GetVexNum() const;					// 返回顶点个数
    int GetEdgeNum() const;					// 返回边数
    int FirstAdjVex(int v) const;		// 返回顶点v的第一个邻接点
    int NextAdjVex(int v1, int v2) const;		 // 返回顶点v1的相对于v2的下一个邻接点
    void InsertVex(const int &e);			 // 插入元素值为e的顶点
    void DeleteVex(const int &e);			 // 删除元素值为e的顶点
    void InsertArc(int v1, int v2, int w);	// 插入顶点为v1和v2,权为w的边
    void DeleteArc(int v1, int v2);			// 删除顶点为v1和v2的边
    int GetWeight(int v1, int v2) const;	// 返回顶点为v1和v2的边的权值
    Status GetTag(int v) const;			         // 返回顶点v的标志
    void SetTag(int v, Status val) const;	   // 设置顶点v的标志为val
    AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork &g);	// 复制构造函数
    AdjMatrixUndirNetwork &operator =(const AdjMatrixUndirNetwork &g);
    // 赋值语句重载
    void Display();	                         // 显示邻接矩阵无向图
};

// 无向图的邻接矩阵类的实现部分

AdjMatrixUndirNetwork::AdjMatrixUndirNetwork(int es[], int vertexNum, int vertexMaxNum, int infinit)
// 操作结果：构造数据元素为es[],顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,边数为0的无向图
{
    if (vertexMaxNum < 0)
        throw Error("允许的顶点最大数目不能为负!");        // 抛出异常

    if (vertexMaxNum < vertexNum)
        throw Error("顶点数目不能大于允许的顶点最大数目!");// 抛出异常

    vexNum = vertexNum;
    vexMaxNum = vertexMaxNum;
    edgeNum = 0;
    infinity = infinit;

    vertexes = new int[vexMaxNum];     	// 生成生成顶点信息数组
    tag = new Status[vexMaxNum];			 	// 生成标志数组
    arcs = (int **)new int *[vexMaxNum];     	// 生成邻接矩阵
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
// 操作结果：构造允许顶点的最大数目为vertexMaxNum的空无向图
{
    if (vertexMaxNum < 0)
        throw Error("允许的顶点最大数目不能为负!");// 抛出异常

    vexNum = 0;
    vexMaxNum = vertexMaxNum;
    edgeNum = 0;
    infinity = infinit;

    vertexes = new int[vexMaxNum];     // 生成生成顶点信息数组
    tag = new Status[vexMaxNum];			      // 生成标志数组
    arcs = (int **)new int *[vexMaxNum];    // 生成邻接矩阵
    for (int v = 0; v < vexMaxNum; v++)
        arcs[v] = new int[vexMaxNum];
}


void AdjMatrixUndirNetwork::Clear()
// 操作结果：把无向图的顶点数和边数设置为0.
{
    vexNum = 0;
    edgeNum = 0;
}


bool AdjMatrixUndirNetwork::IsEmpty()
// 操作结果：如果无向图为空返回true,否则返回false.
{
    return vexNum == 0;
}


AdjMatrixUndirNetwork::~AdjMatrixUndirNetwork()
// 操作结果：释放对象所占用的空间
{
    delete []vertexes;					// 释放顶点数据
    delete []tag;						    // 释放标志

    for (int v = 0; v < vexMaxNum; v++)	// 释放邻接矩阵的行
        delete []arcs[v];
    delete []arcs;					    // 释放邻接矩阵
}


int AdjMatrixUndirNetwork::GetOrder(int &e) const
// 操作结果：求顶点e的序号.顶点的序号从0开始，图中不存在顶点e时，返回-1.
{
    for (int v = 0; v < vexNum; v++)
        if (vertexes[v] == e)
            return v;	    // 顶点e存在,返回它的序号
    return -1;	        // 顶点e不存在,返回-1
}


Status AdjMatrixUndirNetwork::GetElem(int v, int &e) const
// 操作结果：求序号为v的顶点值, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数
// 通过e取得顶点值，并返回ENTRY_FOUND；否则函数返回NOT_PRESENT
{
    if (v < 0 || v >= vexNum)
        return NOT_PRESENT;	// v范围错,返回元素不存在
    else	{
        e = vertexes[v];	  // 将顶点v的元素值赋给e
        return ENTRY_FOUND;	// 返回元素存在
    }
}


Status AdjMatrixUndirNetwork::SetElem(int v, const int &e)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
    if (v < 0 || v >= vexNum)
        return RANGE_ERROR;	// v范围错,返回位置错
    else	{
        vertexes[v] = e;		// 将顶点元素的值改为e
        return SUCCESS;		  // 返回修改成功
    }
}


int AdjMatrixUndirNetwork::GetInfinity() const
// 操作结果：返回无穷大
{
    return infinity;
}


int AdjMatrixUndirNetwork::GetVexNum() const
// 操作结果：返回顶点个数
{
    return vexNum;
}


int AdjMatrixUndirNetwork::GetEdgeNum() const
// 操作结果：返回边数
{
    return edgeNum;
}


int AdjMatrixUndirNetwork::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第1个邻接点的序号
{
    if (v < 0 || v >= vexNum)
        throw Error("v不合法!");// 抛出异常

    for (int u = 0; u < vexNum; u++)
        if (arcs[v][u] != 0 && arcs[v][u] != infinity)
            return u;

    return -1;					// 返回-1表示无邻接点
}


int AdjMatrixUndirNetwork::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1不合法!");	// 抛出异常
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2不合法!");	// 抛出异常
    if (v1 == v2) throw
                Error("v1不能等于v2!");		// 抛出异常

    for (int u = v2 + 1; u < vexNum; u++)
        if (arcs[v1][u] != 0 && arcs[v1][u] != infinity)
            return u;

    return -1;						// 返回-1表示无下一个邻接点
}


void AdjMatrixUndirNetwork::InsertVex(const int &e)
// 操作结果：插入顶点e
{
    if (vexNum == vexMaxNum)
        throw Error("图的顶点数不能超过允许的最大数!");	// 抛出异常

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
// 操作结果：插入依附顶点v1和v2的边
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1不合法!");	// 抛出异常
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2不合法!");	// 抛出异常
    if (v1 == v2)
        throw Error("v1不能等于v2!");// 抛出异常

    if (arcs[v1][v2] == infinity)	{	  // 原无向图中没有边(v1, v2)
        edgeNum++;
        arcs[v1][v2] = w;
        arcs[v2][v1] = w;
    }
}


void AdjMatrixUndirNetwork::DeleteVex(const int &e)
// 操作结果：删除元素为e的顶点
{
    int v;
    for (v = 0; v < vexNum; v++)
        if	(vertexes[v] == e)
            break;
    if (v == vexNum)
        throw Error("图中不存在要删除的顶点!");	// 抛出异常

    for (int u = 0; u < vexNum; u++)             // 删除与顶点e相关联的边
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
// 操作结果：删除依附顶点v1和v2的边
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1不合法!");	// 抛出异常
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2不合法!");	// 抛出异常
    if (v1 == v2)
        throw Error("v1不能等于v2!");// 抛出异常

    if (arcs[v1][v2] != infinity)	{	// 原无向图存在边(v1, v2)
        edgeNum--;
        arcs[v1][v2] = infinity;
        arcs[v2][v1] = infinity;
    }
}


int AdjMatrixUndirNetwork::GetWeight(int v1, int v2) const
// 操作结果：返回顶点为v1和v2的边的权值
{
    if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
    if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常

    return arcs[v1][v2];
}


Status AdjMatrixUndirNetwork::GetTag(int v) const
// 操作结果：返回顶点v的标志
{
    if (v < 0 || v >= vexNum)
        throw Error("v不合法!");	// 抛出异常

    return tag[v];
}


void AdjMatrixUndirNetwork::SetTag(int v, Status val) const
// 操作结果：设置顶点v的标志为val
{
    if (v < 0 || v >= vexNum)
        throw Error("v不合法!");	// 抛出异常

    tag[v] = val;
}


AdjMatrixUndirNetwork::AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork &g)
// 操作结果：由无向图的邻接矩阵g构造新无向图的邻接矩阵g——复制构造函数
{
    vexNum = g.vexNum;
    vexMaxNum = g.vexMaxNum;
    edgeNum = g.edgeNum;
    infinity = g.infinity;

    vertexes = new int[vexMaxNum];		// 生成顶点数据数组
    tag = new Status[vexMaxNum];			// 生成标志数组
    arcs = (int **)new int *[vexMaxNum];	// 生成邻接矩阵
    for (int v = 0; v < vexMaxNum; v++)
        arcs[v] = new int[vexMaxNum];

    for (int v = 0; v < vexNum; v++)	{	// 复制顶点数据数组
        vertexes[v] = g.vertexes[v];
        tag[v] = g.tag[v];
        for (int u = 0; u < vexNum; u++)
            arcs[v][u] = g.arcs[v][u];
    }
}


AdjMatrixUndirNetwork &AdjMatrixUndirNetwork::operator =(const AdjMatrixUndirNetwork &g)
// 操作结果：将无向图的邻接矩阵g赋值给当前无向图的邻接矩阵——赋值语句重载
{
    if (&g != this)	{
        delete []vertexes;				// 释放顶点数据
        delete []tag;						  // 释放标志

        for (int v = 0; v < vexMaxNum; v++)	// 释放邻接矩阵的行
            delete []arcs[v];
        delete []arcs;					  // 释放邻接矩阵
        vexNum = g.vexNum;
        vexMaxNum = g.vexMaxNum;
        edgeNum = g.edgeNum;
        infinity = g.infinity;

        vertexes = new int[vexMaxNum];	 // 生成顶点数据数组
        tag = new Status[vexMaxNum];			   // 生成标志数组
        arcs = (int **)new int *[vexMaxNum]; // 生成邻接矩阵
        for (int v = 0; v < vexMaxNum; v++)
            arcs[v] = new int[vexMaxNum];

        for (int v = 0; v < vexNum; v++)	{	 // 复制顶点数据数组
            vertexes[v] = g.vertexes[v];
            tag[v] = g.tag[v];
            for (int u = 0; u < vexNum; u++)
                arcs[v][u] = g.arcs[v][u];
        }
    }
    return *this;
}


void AdjMatrixUndirNetwork::Display()
// 操作结果: 显示邻接矩阵无向图
{

    for (int v = 0; v < vexNum; v++)
        cout << "\t" << vertexes[v];
    cout << endl;

    for (int v = 0; v < vexNum; v++)	{
        cout << vertexes[v];
        for (int u = 0; u < vexNum; u++)
            if (arcs[v][u] == infinity)
                cout << "\t" << "∞";
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
// 初始条件：存在网g,u0为g的一个顶点
// 操作结果：用Prim算法从u0出发构造网g的最小代价生成树
{
    int min;
    int v1, v2;
    int vexnum = g.GetVexNum();
    CloseArcType * closearc;

    if (u0 < 0 || u0 >= vexnum)
        throw Error("顶点u0不存在!"); // 抛出异常

    int u, v, k;						// 表示顶点的临时变量
    closearc = new CloseArcType[vexnum];	// 分配存储空间
    for (v = 0; v < vexnum; v++)	{	// 初始化辅助数组adjVex，并对顶点作标志，此时U = {v0}
        closearc[v].nearvertex = u0;
        closearc[v].lowweight = g.GetWeight(u0, v);
    }
    closearc[u0].nearvertex = -1;
    closearc[u0].lowweight = 0;

    for (k = 1; k < vexnum; k++) {	// 选择生成树的其余g.GetVexNum() - 1个顶点
        min = g.GetInfinity();
        v = u0;// 选择使得边<w, adjVex[w]>为连接V-U到U的具有最小权值的边
        for (u = 0; u < vexnum; u++)
            if (closearc[u].lowweight != 0 && closearc[u].lowweight < min) {
                v = u;
                min = closearc[u].lowweight;
            }
        if (v != u0) {
            g.GetElem(closearc[v].nearvertex, v1);
            g.GetElem(v, v2);
            cout << "边:( " << v1 << ", " <<  v2 << " ) 权:" << min << endl ; // 输出边及权值
            closearc[v].lowweight = 0;		// 将w并入U
            for (u = g.FirstAdjVex(v); u != -1 ; u = g.NextAdjVex(v, u)) 	// 新顶点并入U后重新选择最小边
                if (closearc[u].lowweight != 0 && (g.GetWeight(v, u) < closearc[u].lowweight))	{	// <v, w>为新的最小边
                    closearc[u].lowweight = g.GetWeight(v, u);
                    closearc[u].nearvertex = v;
                }
        }

    }
    delete []closearc;			// 释放存储空间
}





// /////////////////////////////////////////////////////////////////////////

#endif