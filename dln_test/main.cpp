#include "svpng.inc"
#include <bits/stdc++.h>
using namespace std;
const int width = 1024,height = 512,intensity = 64;
unsigned char rgba[width * height * 4];
int rgbapix[width*height],mm[3000][3000];
const int possionnumber = intensity*intensity/2,maxn = 100000;
int res[possionnumber],realnumber;
double possionr  = width/intensity;


void pixel(int posx,int posy,int colr,int colg,int colb)
{

    if(posx < 0 || posx > width || posy < 0 || posy > height)
        return;
    int idx = posx;
    posx = posy,posy = idx,
    posx = 512 - posx,idx = posx*1024*4+posy*4;
    if(colr>255)
        colr=255;
    if(colg>255)
        colg=255;
    if(colb>255)
        colb=255;
    rgba[idx++]=colr;
    rgba[idx++]=colg;
    rgba[idx++] = colb;
    rgba[idx] = 255;

}

void drawbox(int x,int y,int r,int b,int g)
{
    for(int i = x - 1; i < x + 1; i++)
        for(int j = y - 1; j < y + 1; j++)
            pixel(x,y,r,g,b);
}

struct Point
{
    int x,y;
} p[maxn];
int pnum = 0;

struct Edge
{
    int a,b;
    int ta,tb;//连接的两个三角形
    int use;
} edge[maxn];

int edgenum = 0;
int addEdge(int a,int b,int ta,int tb)
{
    edge[++edgenum].ta = ta;
    edge[edgenum].tb = tb;
    edge[edgenum].a = a;
    edge[edgenum].b = b;
    return edgenum;
}

//修改连接的两点
void editEdge1(int e,int a,int b)
{
    edge[e].a = a;
    edge[e].b = b;
}

void printEdge(int idx)
{
    printf("idx = %d,a = %d,b = %d,ta = %d,tb = %d\n",idx,edge[idx].a,edge[idx].b,edge[idx].ta,edge[idx].tb);
}

//修改连接的三角形
void editEdge2(int e,int oldt,int newt)
{
    if(edge[e].ta == oldt)
        edge[e].ta = newt;
    else
        edge[e].tb = newt;
}

struct Triangle
{
    int e[3],p[3],use,near[3],connect[3];
    double a[3];
} tri[maxn];

int trinum = 0;

void printTri(int idx)
{
    printf("--------------------------------------new tir idx = %d\n",idx);
    printf("p0 = %d,p1 = %d,p2 = %d\n",tri[idx].p[0],tri[idx].p[1],tri[idx].p[2]);
    printf("p0x = %d,p0y = %d,",p[tri[idx].p[0]].x,p[tri[idx].p[0]].y);
    printf("p1x = %d,p1y = %d,",p[tri[idx].p[1]].x,p[tri[idx].p[1]].y);
    printf("p2x = %d,p2y = %d\n",p[tri[idx].p[2]].x,p[tri[idx].p[2]].y);
    printf("e0 = %d,e1 = %d,e2 = %d\n",tri[idx].e[0],tri[idx].e[1],tri[idx].e[2]);
    printf("a0 = %lf,a1 = %lf,a2 = %lf\n",tri[idx].a[0],tri[idx].a[1],tri[idx].a[2]);
}

void deleteTriangle(int idx)
{
    tri[idx].use = 0;
}

double calangle(int ce,int p1,int p2)
{
    // printf("ce = %d,p1 = %d,p2 = %d\n",ce,p1,p2);
    double v1x = p[p1].x - p[ce].x,v1y = p[p1].y - p[ce].y;
    double v2x = p[p2].x - p[ce].x,v2y = p[p2].y - p[ce].y;
    // printf("v1x = %lf,v1y = %lf,v2x = %lf,v2y = %lf\n",v1x,v1y,v2x,v2y);
    double res = acos((v1x*v2x + v1y*v2y)/(sqrt(v1x*v1x + v1y*v1y)*sqrt(v2x*v2x + v2y*v2y)));
    printf("res = %lf\n",res);
    return res;
}

int addTriangle(int p0,int p1,int p2,int e0,int e1,int e2)
{
    tri[++trinum].e[0] = e0;
    tri[trinum].e[1] = e1;
    tri[trinum].e[2] = e2;
    tri[trinum].p[0] = p0;
    tri[trinum].p[1] = p1;
    tri[trinum].p[2] = p2;
    tri[trinum].a[0] = calangle(p0,p1,p2);//0到Pi之间的一个数字
    tri[trinum].a[1] = calangle(p1,p0,p2);
    tri[trinum].a[2] = calangle(p2,p0,p1);
    tri[trinum].near[0] = tri[trinum].near[1] = tri[trinum].near[2] = -1;
    tri[trinum].connect[0] = tri[trinum].connect[1] = tri[trinum].connect[2] = -1;
    tri[trinum].use = 1;
    return trinum;
}

void editTriangle(int t1,int t2,int p0,int p1,int p2,int p3,int e0,int e1,int e2,int e3,int e4,int e5)
{
    tri[t1].p[0] = p0,tri[t1].p[1] = p1,tri[t1].p[2] = p2;
    tri[t1].e[0] = e0,tri[t1].e[1] = e1,tri[t1].e[2] = e2;
    tri[t1].a[0] = calangle(p0,p1,p2);
    tri[t1].a[1] = calangle(p1,p0,p2);
    tri[t1].a[2] = calangle(p2,p0,p1);
    //e2是公共边
    tri[t2].p[0] = p1,tri[t2].p[1] = p2,tri[t2].p[2] = p3;
    tri[t2].e[0] = e3,tri[t2].e[1] = e4,tri[t2].e[2] = e5;
    tri[t2].a[0] = calangle(p1,p2,p3);
    tri[t2].a[1] = calangle(p2,p3,p1);
    tri[t2].a[2] = calangle(p3,p1,p2);

}



void possiondisk()
{
    int pnx = intensity,pny = intensity/2,he = 0,ta = 0;
    int work[possionnumber];
    srand( (unsigned)time( NULL ) );
    int x = rand()%width,y = rand()%height;
    work[ta] = x + y*width;
    res[ta] = x + y*width;
    int grididx =  x/possionr + y/possionr*pnx;
    int grid[pnx*pny];
    memset(grid,-1,sizeof(grid));
    grid[grididx] = ta;
    while(he <= ta && ta < possionnumber)
    {
        int now = work[he++],nowx = now%width,nowy = now/width;
        for(int ix = 0; ix < 30; ix++)
        {
            int flag = 0;
            while(1)
            {
                x = rand()%width;
                y = rand()%height;
                double len  = sqrt((nowx-x)*(nowx-x) + (nowy - y)*(nowy-y));
                if(len < possionr*2 && len > possionr && x > 0 && x < width && y > 0 && y < width)
                break;
            }
            int gridx = x/(int)possionr,gridy = y/(int)possionr;
            if(grid[gridx + gridy*pnx] != -1)
                continue;
            for(int i = gridx - 1; i <= gridx + 1; i++)
            {
                if(i < 0 || i >= pnx)
                    continue;
                for(int j = gridy - 1; j <= gridy + 1; j++)
                {
                    if(j < 0 || j >= pny)
                        continue;
                    if(grid[i + j*pnx] == -1)
                        continue;
                    int newx = res[grid[i + j*pnx]]%width,newy = res[grid[i + j*pnx]]/width;
                    if(sqrt((newx-x)*(newx-x)+(newy-y)*(newy-y)) < possionr)
                    {
                        flag = 1;
                        break;
                    }
                }
            }
            if(flag == 0)
            {
                work[++ta] = x + y*width,res[ta] = x + y*width;
                grid[gridx + gridy*pnx] = ta;
                //  printf("res[%d] = %d\n",ta,res[ta]);
            }
        }

    }
    realnumber = ta;
    for(int i = 0; i <= ta; i++)
        drawbox(res[i]%width,res[i]/width,255,0,0);
}

void drawaLine(int x0, int y0, int x1, int y1,int r,int g,int b)
{
    printf("x0 = %d,y0 = %d,x1 = %d,y1 = %d\n",x0,y0,x1,y1);
    bool steep = false;
    if (abs(x0-x1)<abs(y0-y1))
    {
        swap(x0, y0);
        swap(x1, y1);
        steep = true;
    }
    if (x0>x1)
    {
        swap(x0, x1);
        swap(y0, y1);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    int derror2 = abs(dy)*2;
    int error2 = 0;
    int y = y0;
    for (int x=x0; x<=x1; x++)
    {
        if (steep)
        {
            pixel(y, x, r,g,b);
        }
        else
        {
            pixel(x,y,r,g,b);
        }
        error2 += derror2;
        if (error2 > dx)
        {
            y += (y1>y0?1:-1);
            error2 -= dx*2;
        }
    }
}

void handleedge(int nowe)
{
    printf("test!\n");
    int TriA = edge[nowe].ta;
    int TriB = edge[nowe].tb;
    if(TriB == -1)
        return;
    printTri(TriA);
    printTri(TriB);
    int ea,eb,f1 = -1,f2,s1 = -1,s2,p0,p1;
    for(int k = 0; k < 3; k++)
    {
        printf("A%d = %d,B%d = %d,nowe = %d\n",k,tri[TriA].e[k],k,tri[TriB].e[k],nowe);
        if(tri[TriA].e[k] == nowe)
            ea = k;
        else if(f1 == -1)
            f1 = tri[TriA].e[k];
        else
            f2 = tri[TriA].e[k];
        if(tri[TriB].e[k] == nowe)
            eb = k;
        else if(s1 == -1)
            s1 = tri[TriB].e[k];
        else
            s2 = tri[TriB].e[k];
    }
    printf("ea = %d,eb = %d,f1 = %d,f2 = %d,s1 = %d,s2 = %d\n",ea,eb,f1,f2,s1,s2);
    double pi = 3.14159;
    int flag = 0;
    //保证f1和s1相连
    if(edge[f1].a == edge[s1].a || edge[f1].a == edge[s1].b || edge[f1].b == edge[s1].a || edge[f1].b == edge[s1].b)
        flag=1;
    else
        flag = s2,s2 = s1,s1 = flag;
    printf("f1 = %d,s1 = %d,f1a = %d,f1b = %d,s1a = %d,s1b = %d\n",f1,s1,edge[f1].a,edge[f1].b,edge[s1].a,edge[s1].b);
    //保证f1和s1的同一点是p0，同理f2和s2的连接点是p1
    if(edge[f1].a == edge[s1].a || edge[f1].a == edge[s1].b)
        p0 = edge[f1].a;
    else if (edge[f1].b == edge[s1].a || edge[f1].b == edge[s1].b)
        p0 = edge[f1].b;
    if(edge[f2].a == edge[s2].a || edge[f2].a == edge[s2].b)
        p1 = edge[f2].a;
    else if (edge[f2].b == edge[s2].a || edge[f2].b == edge[s2].b)
        p1 = edge[f2].b;
    printf("%lf and %lf\n",tri[TriA].a[ea],tri[TriB].a[eb]);
    if(tri[TriA].a[ea] + tri[TriB].a[eb] > pi)
    {
        printf("Flip!\n");
        //p0 , p1原来连接的两点
        int pa = tri[TriA].p[ea],pb = tri[TriB].p[eb];//现在要连接的两点
        editEdge1(nowe,pa,pb);
        printEdge(nowe);
        editEdge2(s1,TriB,TriA);
        editEdge2(f2,TriA,TriB);
        printEdge(f1);
        printEdge(f2);
        printEdge(s1);
        printEdge(s2);
        if(edge[f1].a == pb || edge[f1].b == pb)
            flag = pb,pb = pa,pa = flag;//保证f1连接的是pa
        printf("p0 = %d,p1 = %d,pa = %d,pb = %d\n",p0,p1,pa,pb);
        printf("nowe = %d,f1 = %d,f2 = %d,s1 = %d,s2 = %d\n",nowe,f1,f2,s1,s2);
        editTriangle(TriA,TriB,p0,pa,pb,p1,nowe,s1,f1,s2,f2,nowe);
        printf("after----------------\n");
        printTri(TriA);
        printTri(TriB);
        handleedge(f1);
        handleedge(f2);
        handleedge(s1);
        handleedge(s2);
    }
}

void delaunay()
{
    int tidx;
    p[0].x = -512,p[0].y = -512;
    p[1].x = 512,p[1].y = 1536;
    p[2].x = 1536,p[2].y = -512;
    pnum = 2;
    int ae = addEdge(0,1,1,-1);
    int be = addEdge(1,2,1,-1);
    int ce = addEdge(2,0,1,-1);
    addTriangle(0,1,2,be,ce,ae);

    /*realnumber = 4;
    res[1] = 297 + 137*width;
    res[2] = 471 + 385*width;
    res[3] = 1013 + 194*width;
    res[4] = 561 + 67*width;*/
    for(int i = 1; i <= realnumber; i++)
    {
        //先找这个点在哪个三角形里面
        int nowx = res[i]%width,nowy = res[i]/width,border = 0;
        for(int j = 1; j <= trinum; j++) // edgenum 和 trinum都是从1开始的
        {
            if(tri[j].use==0)
                continue;
            int p0x = p[tri[j].p[0]].x,p0y = p[tri[j].p[0]].y;
            int p1x = p[tri[j].p[1]].x,p1y = p[tri[j].p[1]].y;
            int p2x = p[tri[j].p[2]].x,p2y = p[tri[j].p[2]].y;
            int np0x = nowx-p0x,np0y = nowy-p0y,v0x = p1x-p0x,v0y = p1y-p0y;
            int np1x = nowx-p1x,np1y = nowy-p1y,v1x = p2x-p1x,v1y = p2y-p1y;
            int np2x = nowx-p2x,np2y = nowy-p2y,v2x = p0x-p2x,v2y = p0y-p2y;
            int cal[3];
            cal[0] = np0x * v0y - np0y * v0x;
            cal[1] = np1x * v1y - np1y * v1x;
            cal[2] = np2x * v2y - np2y * v2x;
            double eps = 0.1;
            for(int k=0; k<=2; k++)
            {
                if(abs(cal[k])<eps)
                {
                    border=1;
                    break;
                }
                else if(cal[k]>0)
                    cal[k]=1;
                else
                    cal[k] = -1;
            }
            if(border)
                break;
            //  printf("%d %d %d\n",cal[0],cal[1],cal[2]);
            if((cal[0]*cal[1] > 0) && (cal[1]*cal[2]>0))
            {
                tidx = j;//在这个三角形里面
                break;
            }
        }
        if(border)
            continue;//不要在边界上的点
        printf("---\n%d,%dat %d\n---\n",nowx,nowy,tidx);
        deleteTriangle(tidx);
        p[++pnum].x = nowx,p[pnum].y = nowy;
        int p0 = tri[tidx].p[0],p1 = tri[tidx].p[1],p2 = tri[tidx].p[2];
        printf("new Point %d nad %d delete Tri %d\n", nowx,nowy,tidx);
        printTri(tidx);
        ae = addEdge(pnum,p0,trinum+1,trinum+3);
        be = addEdge(pnum,p1,trinum+2,trinum+1);
        ce = addEdge(pnum,p2,trinum+3,trinum+2);
        int tempe = tri[tidx].e[2],tempt;
        tempt = addTriangle(p0,pnum,p1,be,tempe,ae);
        if(edge[tempe].ta == tidx)
            edge[tempe].ta = tempt;
        else
            edge[tempe].tb = tempt;
        tempe = tri[tidx].e[0];
        tempt = addTriangle(p1,pnum,p2,ce,tempe,be);
        if(edge[tempe].ta == tidx)
            edge[tempe].ta = tempt;
        else
            edge[tempe].tb = tempt;
        tempe = tri[tidx].e[1];
        tempt = addTriangle(p2,pnum,p0,ae,tempe,ce);
        if(edge[tempe].ta == tidx)
            edge[tempe].ta = tempt;
        else
            edge[tempe].tb = tempt;
        for(int j = 0; j < 3; j++)
        {
            handleedge(tri[tidx].e[j]);
        }

    }
    for(int i = 1; i <= trinum; i++)
    {
        if(tri[i].use)
        {
            printTri(i);
            drawaLine(p[tri[i].p[0]].x,p[tri[i].p[0]].y,p[tri[i].p[1]].x,p[tri[i].p[1]].y,0,0,255);
            drawaLine(p[tri[i].p[1]].x,p[tri[i].p[1]].y,p[tri[i].p[2]].x,p[tri[i].p[2]].y,0,0,255);
            drawaLine(p[tri[i].p[2]].x,p[tri[i].p[2]].y,p[tri[i].p[0]].x,p[tri[i].p[0]].y,0,0,255);
            for(int j = 0; j < 3; j++)
            {
                if(edge[tri[i].e[j]].ta == i)
                    tri[i].near[j]=edge[tri[i].e[j]].tb;
                else
                    tri[i].near[j]=edge[tri[i].e[j]].ta;
            }
        }
    }
}

int cirx[maxn],ciry[maxn];
void calcir(int p0,int p1,int p2,int idx)
{

    printf("calcir-----------------\n");
    double p0x = p[p0].x,p0y = p[p0].y;
    double p1x = p[p1].x,p1y = p[p1].y;
    double p2x = p[p2].x,p2y = p[p2].y;
    printf("p0x = %lf,p0y = %lf\n",p0x,p0y);
    printf("p1x = %lf,p1y = %lf\n",p1x,p1y);
    printf("p2x = %lf,p2y = %lf\n",p2x,p2y);
    double m0x = (p0x + p1x)/2,m0y = (p0y + p1y)/2;
    double m1x = (p0x + p2x)/2,m1y = (p0y + p2y)/2;
    if(abs(p1y - p0y) < 1e-5)//斜率k0不存在
    {
        double k1 = -(p2x-p0x)/(p2y - p0y);
        double d1 = m1y - k1*m1x;
        double cx = m0x;
        double cy = cx*k1 + d1;
        printf("m1x = %lf,m1y = %lf,k1 = %lf,d1 = %lf\n",m1x,m1y,k1,d1);
        printf("cx = %lf,cy = %lf k0 not exist\n",cx,cy);
        cirx[idx] = cx;
        ciry[idx] = cy;
        printf("cirx = %d,ciry = %d\n",cirx[idx],ciry[idx]);
    }
    else if(abs(p2y - p0y) < 1e-5)
    {
        double k0 = -(p1x-p0x)/(p1y - p0y);
        double d0 = m0y - k0*m0x;
        printf("m0x = %lf,m0y = %lf,k0 = %lf,d0 = %lf\n",m0x,m0y,k0,d0);
        double cx = m0x;
        double cy = cx*k0 + d0;
        printf("cx = %lf,cy = %lf,k1 not exist\n",cx,cy);
        cirx[idx] = cx;
        ciry[idx] = cy;
        printf("cirx = %d,ciry = %d\n",cirx[idx],ciry[idx]);
    }
    else
    {
        double k0 = -(p1x-p0x)/(p1y - p0y);
        double k1 = -(p2x-p0x)/(p2y - p0y);
        double d0 = m0y - k0*m0x;
        double d1 = m1y - k1*m1x;
        double cx = (d0-d1)/(k1-k0);
        double cy = cx*k0 + d0;
        printf("cx = %lf,cy = %lf\n",cx,cy);
        cirx[idx] = cx;
        ciry[idx] = cy;
        printf("cirx = %d,ciry = %d\n",cirx[idx],ciry[idx]);
    }
}

void voronoi()
{
    for(int i = 1; i <= trinum; i++)
    {
        if(!tri[i].use)
            continue;
        //printf("for %d near,%d,%d,%d\n",i,tri[i].near[0],tri[i].near[1],tri[i].near[2]);
        calcir(tri[i].p[0],tri[i].p[1],tri[i].p[2],i);
        if(cirx[i] > width)
            cirx[i] = width*1.1;
        if(cirx[i] < 0 )
            cirx[i] = -width*0.1;
        if(ciry[i] > height)
            ciry[i] = height*1.1;
        if(ciry[i] < 0 )
            ciry[i] = -height*0.1;
        drawbox(cirx[i],ciry[i],0,255,0);
    }
    int mark[maxn];
    memset(mark,0,sizeof(mark));
    for(int i = 1; i <= trinum; i++)
    {
        if(!tri[i].use)
            continue;
        for(int j = 0; j < 3; j++)
        {
            int ne = tri[i].near[j];
            if(ne == -1)
                continue;
            bool flag = 0;
            for(int k = 0; k < mark[ne]; k++)
            {
                if(tri[ne].connect[k] == i)
                    flag = 1;
            }
            if(!flag)
            {
                tri[i].connect[mark[i]++] = ne;
                tri[ne].connect[mark[ne]++] = i;
                printf("%d -- %d\n",i,ne);
                drawaLine(cirx[i],ciry[i],cirx[ne],ciry[ne],255,255,0);
            }
        }
    }
}

int main(void)
{
    possiondisk();
    delaunay();
    voronoi();
    FILE* fp = fopen("rgba.png", "wb");
    svpng(fp, 1024, 512, rgba, 1);
    fclose(fp);
    return 0;
}
