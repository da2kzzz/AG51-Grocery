#ifndef __HEADS_H__
#define __HEADS_H__
#include "assistance.h"
struct Node{
    int data;				
    Node *next;		
    Node();						
    Node(int item, Node *link = nullptr);	
};
Node::Node(){
    next = nullptr;
}
Node::Node(int item, Node *link){
    data = item;
    next = link;
}
class LinkStack{
protected:
    Node *top;							
public:
    LinkStack();									
    virtual ~LinkStack();							
    bool IsEmpty() const;							
    void Clear();									
    Status Push(const int e);					
    Status Pop(int &e);						
    LinkStack(const LinkStack &s);		
    LinkStack &operator =(const LinkStack &s); 
};
LinkStack::LinkStack(){
    top = nullptr;
}
LinkStack::~LinkStack(){
    Clear();
}
bool LinkStack::IsEmpty() const{
    return top == nullptr;
}
void LinkStack::Clear(){
    Node *p;
    while (top != nullptr) {
        p = top;
        top = top->next;
        delete p;
    }
}
Status LinkStack::Push(const int e){
    Node *p = new Node(e, top);
    if (p == nullptr) 	
        return OVER_FLOW;
    else	{	
        top = p;
        return SUCCESS;
    }
}
Status LinkStack::Pop(int &e){
    if (IsEmpty())	
        return UNDER_FLOW;
    else	{	
        Node *p = top;	
        e = top->data;				
        top = top->next;			
        delete p;					
        return SUCCESS;
    }
}
LinkStack &LinkStack::operator = (const LinkStack &s){
    if (&s != this)	{
        Clear();			
        if (!s.IsEmpty())	{	                            
            top = new Node(s.top->data);       
            Node *q = top;			            
            for (Node *p = s.top->next; p != nullptr; p = p->next){
                q->next = new Node(p->data);      
                q = q->next;			                    
            }
        }
    }
    return *this;
}
struct AdjListNetworkArc{
    int adjVex;								
    int weight;						
    AdjListNetworkArc *nextarc; 
    AdjListNetworkArc();					
    AdjListNetworkArc(int v, int w, AdjListNetworkArc * next = NULL);
    
};
AdjListNetworkArc::AdjListNetworkArc(){
    adjVex = -1;
}
AdjListNetworkArc::AdjListNetworkArc(int v, int w, AdjListNetworkArc *next){
    adjVex = v;
    weight = w;
    nextarc = next;
}
struct AdjListNetWorkVex{
    int data;						
    AdjListNetworkArc *firstarc;
    
    AdjListNetWorkVex();				
};
AdjListNetWorkVex::AdjListNetWorkVex(){
    firstarc = nullptr;
}
class AdjListDirNetwork{
protected:
    int vexNum, vexMaxNum, arcNum;					
    AdjListNetWorkVex *vexTable;	
    mutable Status *tag;					        
    int infinity;							
public:
    AdjListDirNetwork(int es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE,int infinit = (int)DEFAULT_INFINITY);
    ~AdjListDirNetwork();						 
    void Clear();
    Status GetElem(int v, int &d) const;
    int GetInfinity() const;				 
    int GetVexNum() const;
    void InsertArc(int v1, int v2, int w);
    int GetWeight(int v1, int v2) const;
    AdjListDirNetwork &operator =
            (const AdjListDirNetwork &copy); 
    void Display();	
};
AdjListDirNetwork::AdjListDirNetwork(int es[],int vertexNum, int vertexMaxNum, int infinit){
    if (vertexMaxNum < 0)
        throw Error("the number of allowed nodes cannot be a negative number!");        
    if (vertexMaxNum < vertexNum)
        throw Error("number of nodes cannot bigger than allowed!");
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
AdjListDirNetwork::~AdjListDirNetwork(){
    Clear();                                
    delete []tag;							
    delete []vexTable;						
}
void AdjListDirNetwork::Clear(){
    AdjListNetworkArc *p;
    for (int v = 0; v < vexNum; v++)	{	
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
Status AdjListDirNetwork::GetElem(int v, int &d) const{
    if (v < 0 || v >= vexNum)
        return NOT_PRESENT;			
    else	{
        d = vexTable[v].data;		
        return ENTRY_FOUND;			
    }
}
int AdjListDirNetwork::GetInfinity() const{
    return infinity;
}
int AdjListDirNetwork::GetVexNum() const{
    return vexNum;
}
void AdjListDirNetwork::InsertArc(int v1, int v2, int w){
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 is illegal!");	
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 is illegal!");	
    if (v1 == v2)
        throw Error("v1 cannot equals to v2!");
    if (w == infinity)
        throw Error("w cannot be infinity!");
    AdjListNetworkArc *p, *q;
    p = vexTable[v1].firstarc;
    vexTable[v1].firstarc = new AdjListNetworkArc(v2, w, p);
    arcNum++;
}
int AdjListDirNetwork::GetWeight(int v1, int v2) const{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 is illegal!");	
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 is illegal!");	
    AdjListNetworkArc *p;
    p = vexTable[v1].firstarc;
    while (p != nullptr && p->adjVex != v2)
        p = p->nextarc;
    if (p != nullptr)
        return p->weight;			
    else
        return infinity;				
}
AdjListDirNetwork &AdjListDirNetwork::operator =(const AdjListDirNetwork &copy){
    if (&copy != this)
    {
        Clear();                                    
        delete []tag;								
        delete []vexTable;							
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
void AdjListDirNetwork::Display(){
    AdjListNetworkArc *p;
    cout << "Directed graph has " << vexNum << " nodes, " << arcNum << " edges." << endl;
    for (int v = 0; v < vexNum; v++)	{	
        cout << v << ":\t" << vexTable[v].data;				
        p = vexTable[v].firstarc;
        while (p != nullptr) {
            cout << "-->(" << p->adjVex << "," << p->weight << ")";
            p = p->nextarc;
        }
        cout << endl;
    }
}
void ShortestPathFloyd(const AdjListDirNetwork &g, int **path,int **dist){
    for (int u = 0; u < g.GetVexNum(); u++)
        for (int v = 0; v < g.GetVexNum(); v++)
        {	
            dist[u][v] = (u != v) ? g.GetWeight(u, v) : 0;
            if (u != v && dist[u][v] < g.GetInfinity())
                path[u][v] = u;	
            else
                path[u][v] = -1;											
        }
    for (int k = 0; k < g.GetVexNum(); k++)
        for (int i = 0; i < g.GetVexNum(); i++)
            for (int j = 0; j < g.GetVexNum(); j++)
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
}
void DisplayPathAndDist(const AdjListDirNetwork &g, int **path, int **dist){
    int e1, e2;
    for (int v1 = 0; v1 < g.GetVexNum(); v1++)
        for (int v2 = 0; v2 < g.GetVexNum(); v2++)
            if (v1 != v2) {
                cout << endl;
                g.GetElem(v1, e1);
                g.GetElem(v2, e2);
                if (dist[v1][v2] < g.GetInfinity() )	{	
                    cout << "from " << e1 << " to " << e2 << ":";
                    cout << " dist = " << dist[v1][v2];
                    cout << " edge£º";
                    LinkStack s;	
                    int v = v2;
                    while (v != v1)	{
                        s.Push(v);	
                        v = path[v1][v];
                    }
                    s.Push(v1);		
                    while (!s.IsEmpty())		{	
                        s.Pop(v);
                        g.GetElem(v, e1);
                        cout << e1 << " ";
                    }
                }
                else 	{	
                    cout << "from " << e1 << " to " << e2 << ":";
                    cout << " none path";
                }
            }
    cout << endl;
}
class AdjMatrixUndirNetwork{
protected:
    int vexNum, vexMaxNum, edgeNum;			
    int **arcs;							
    int *vertexes;						
    Status *tag;							
    int infinity;					
public:
    AdjMatrixUndirNetwork(int es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE,int infinit = (int)DEFAULT_INFINITY);
    ~AdjMatrixUndirNetwork();					
    Status GetElem(int v, int &e) const;
    int GetInfinity() const;				
    int GetVexNum() const;					
    int FirstAdjVex(int v) const;		
    int NextAdjVex(int v1, int v2) const;		 
    void InsertArc(int v1, int v2, int w);	
    int GetWeight(int v1, int v2) const;
    AdjMatrixUndirNetwork &operator =(const AdjMatrixUndirNetwork &g);
};
AdjMatrixUndirNetwork::AdjMatrixUndirNetwork(int es[], int vertexNum, int vertexMaxNum, int infinit){
    if (vertexMaxNum < 0)
        throw Error("The maximum number of vertices allowed cannot be negative!");
    if (vertexMaxNum < vertexNum)
        throw Error("The number of vertices cannot be greater than the maximum number of vertices allowed!");
    vexNum = vertexNum;
    vexMaxNum = vertexMaxNum;
    edgeNum = 0;
    infinity = infinit;
    vertexes = new int[vexMaxNum];     	
    tag = new Status[vexMaxNum];			 	
    arcs = (int **)new int *[vexMaxNum];     	
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

AdjMatrixUndirNetwork::~AdjMatrixUndirNetwork(){
    delete []vertexes;					
    delete []tag;						    
    for (int v = 0; v < vexMaxNum; v++)	
        delete []arcs[v];
    delete []arcs;					    
}
Status AdjMatrixUndirNetwork::GetElem(int v, int &e) const{
    if (v < 0 || v >= vexNum)
        return NOT_PRESENT;	
    else	{
        e = vertexes[v];	  
        return ENTRY_FOUND;	
    }
}
int AdjMatrixUndirNetwork::GetInfinity() const{
    return infinity;
}
int AdjMatrixUndirNetwork::GetVexNum() const{
    return vexNum;
}
int AdjMatrixUndirNetwork::FirstAdjVex(int v) const{
    if (v < 0 || v >= vexNum)
        throw Error("v illegal!");
    for (int u = 0; u < vexNum; u++)
        if (arcs[v][u] != 0 && arcs[v][u] != infinity)
            return u;
    return -1;					
}
int AdjMatrixUndirNetwork::NextAdjVex(int v1, int v2) const{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1 illegal!");	
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2 illegal!");	
    if (v1 == v2) throw
                Error("v1 cannot equal to v2!");
    for (int u = v2 + 1; u < vexNum; u++)
        if (arcs[v1][u] != 0 && arcs[v1][u] != infinity)
            return u;
    return -1;						
}
void AdjMatrixUndirNetwork::InsertArc(int v1, int v2, int w){
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1illegal!");	
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2illegal!");	
    if (v1 == v2)
        throw Error("v1 cannot equal to v2!");
    if (arcs[v1][v2] == infinity)	{	  
        edgeNum++;
        arcs[v1][v2] = w;
        arcs[v2][v1] = w;
    }
}
int AdjMatrixUndirNetwork::GetWeight(int v1, int v2) const{
    if (v1 < 0 || v1 >= vexNum) throw Error("v1illegal!");	
    if (v2 < 0 || v2 >= vexNum) throw Error("v2illegal!");	
    return arcs[v1][v2];
}
AdjMatrixUndirNetwork &AdjMatrixUndirNetwork::operator =(const AdjMatrixUndirNetwork &g){
    if (&g != this)	{
        delete []vertexes;				
        delete []tag;						  
        for (int v = 0; v < vexMaxNum; v++)	
            delete []arcs[v];
        delete []arcs;					  
        vexNum = g.vexNum;
        vexMaxNum = g.vexMaxNum;
        edgeNum = g.edgeNum;
        infinity = g.infinity;
        vertexes = new int[vexMaxNum];	 
        tag = new Status[vexMaxNum];			   
        arcs = (int **)new int *[vexMaxNum]; 
        for (int v = 0; v < vexMaxNum; v++)
            arcs[v] = new int[vexMaxNum];
        for (int v = 0; v < vexNum; v++)	{	 
            vertexes[v] = g.vertexes[v];
            tag[v] = g.tag[v];
            for (int u = 0; u < vexNum; u++)
                arcs[v][u] = g.arcs[v][u];
        }
    }
    return *this;
}
struct CloseArcType {
    int lowweight;
    int nearvertex;
};
int MiniSpanTreePrim(const AdjMatrixUndirNetwork &g, int u0){
    int min;
    int sum = 0;
    int v1, v2;
    int vexnum = g.GetVexNum();
    CloseArcType * closearc;
    if (u0 < 0 || u0 >= vexnum)
        throw Error("vertex doesn't exist!"); 
    int u, v, k;						
    closearc = new CloseArcType[vexnum];	
    for (v = 0; v < vexnum; v++)	{	
        closearc[v].nearvertex = u0;
        closearc[v].lowweight = g.GetWeight(u0, v);
    }
    closearc[u0].nearvertex = -1;
    closearc[u0].lowweight = 0;
    for (k = 1; k < vexnum; k++) {	
        min = g.GetInfinity();
        v = u0;
        for (u = 0; u < vexnum; u++)
            if (closearc[u].lowweight != 0 && closearc[u].lowweight < min) {
                v = u;
                min = closearc[u].lowweight;
            }
        if (v != u0) {
            g.GetElem(closearc[v].nearvertex, v1);
            g.GetElem(v, v2);
            cout << "edge:( " << v1 << " to " <<  v2 << " ) weight:" << min << endl ; 
            sum = sum + min;
            closearc[v].lowweight = 0;		
            for (u = g.FirstAdjVex(v); u != -1 ; u = g.NextAdjVex(v, u)) 	
                if (closearc[u].lowweight != 0 && (g.GetWeight(v, u) < closearc[u].lowweight))	{	
                    closearc[u].lowweight = g.GetWeight(v, u);
                    closearc[u].nearvertex = v;
                }
        }
    }
    delete []closearc;			
    return sum;
}
class Assistant{
private:
    size_t V;        
    size_t Index;    
    vector<list<size_t>> &Lines; 
    vector<bool> Visited; 
    vector<size_t> DFN;   
    vector<size_t> LOW;   
    vector<size_t> Stack;
    vector<vector<int>> AllScc;
    vector<int> vec;
public:
    Assistant(size_t v, vector<list<size_t>> &lines) : V(v), Index(0), Lines(lines)    {
        Visited = vector<bool>(V, false);
        DFN = vector<size_t>(V);
        LOW = vector<size_t>(V);
        Stack.reserve(V);
    }
    void PrintCSS(){
        Index = 0;
        for (size_t I = 0; I < V; ++I)
        {
            if (Visited[I] == false)
            {
                Tarjan(I);
            }
        }
    }
    void Tarjan(size_t v)    {
        
        Visited[v] = true;
        DFN[v] = Index;
        LOW[v] = Index;
        ++Index;
        Stack.push_back(v);
        
        for (auto &N : Lines[v])
        {
            if (Visited[N] == false) 
            {
                Tarjan(N);
                LOW[v] = min(LOW[v], LOW[N]);
            }
            else 
            {
                if (find(Stack.begin(), Stack.end(), N) != Stack.end())
                {
                    LOW[v] = min(LOW[v], DFN[N]);
                }
            }
            
        }
        
        if (DFN[v] == LOW[v]){
            while (true){
                size_t Temp = Stack.back();
                Stack.pop_back();
                vec.push_back(Temp);
                cout << Temp << "  ";
                if (Temp == v)
                {
                    AllScc.push_back(vec);
                    vec.clear();
                    break;
                }
            }
            cout << endl;
        }
    }
    vector<vector<int>> getAllScc(){
        return AllScc;
    }
};
class Graph{
private:
    size_t V; 
    vector<list<size_t>> Lines;  
public:
    Graph(size_t v) : V(v), Lines(v) {};
public:
    void AddLine(size_t Source, size_t Dest) 
    {
        Lines[Source].push_back(Dest);
    };
    vector<vector<int>> PrintSCC()
    {
        Assistant Ass(V, Lines);
        Ass.PrintCSS();
        return Ass.getAllScc();
    };
};

#endif