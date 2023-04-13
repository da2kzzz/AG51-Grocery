#include<cstdio>
#include<stack>
#include<algorithm>
#include<cmath>
#include <ctime>
#include <stdlib.h>

using namespace std;
const int maxn = 1000;
struct Node{
    int x,y;
}u,node[maxn];
int N=50;

int cmp1(const Node &a, const Node &b)
{
    return a.y < b.y;
}
/*极角排序*/
int cmp2(const Node &a, const Node &b)
{
    return atan2(1.0*(a.y-u.y), 1.0*(a.x-u.x)) < atan2(1.0*(b.y-u.y), 1.0*(b.x-u.x));
}
/*计算叉积*/
int Direction(Node a, Node b, Node c)
{
    return (c.x-a.x) * (b.y-a.y) - (b.x-a.x) * (c.y - a.y);
}
/*判断是否向右*/
bool right(Node a, Node b, Node c)
{
    if(Direction(a, b, c) < 0)
    {
        return true;
    }
    else
        return false;
}

int main()
{
    srand((unsigned int) (time(NULL)));
    for(int i=0; i<N; i++)
    {
        node[i].x=(rand() % (450 - 50 + 1)) + 50;
        node[i].y=(rand() % (450 - 50 + 1)) + 50;
    }

    sort(node, node+N, cmp1);
    stack<Node> s;
    s.push(node[0]);
    u = node[0];
    sort(node+1, node+N, cmp2);
    s.push(node[1]);
    s.push(node[2]);
    for(int i=3; i<N; i++)
    {
        Node top = s.top();
        s.pop();
        Node n_top = s.top();
        if(right(node[i], top, n_top))
        {
            s.push(node[i]);
        }
        else{
            s.push(top);
            s.push(node[i]);
        }
    }
    while(!s.empty())
    {
        printf("%d %d\n",s.top().x, s.top().y);
        s.pop();
    }
    return 0;
}