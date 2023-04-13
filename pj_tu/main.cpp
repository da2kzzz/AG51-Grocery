#include "assistance.h"
#include "heads.h"


int main(void) {
    try									// 用try封装可能出现异常的代码
    {
        int infity = DEFAULT_INFINITY;
        int vexs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
        int m[13][13] = {
                {infity,      1,      5, infity, infity, infity, infity, infity, infity, infity, infity, infity, infity},
                {infity, infity, infity,      1,      4, infity, infity, infity, infity, infity, infity, infity, infity},
                {     1, infity,  infity,     2, infity, infity, infity,      1, infity, infity, infity, infity, infity},
                {     1, infity, infity, infity, infity, infity,      1, infity, infity, infity, infity, infity, infity},
                {infity, infity, infity, infity, infity,      1, infity, infity, infity, infity, infity, infity, infity},
                {infity, infity, infity, infity, infity, infity,      4, infity, infity, infity, infity, infity, infity},
                {infity, infity, infity, infity,      2, infity, infity, infity, infity,      1, infity, infity, infity},
                {infity, infity, infity, infity, infity, infity, infity, infity,      1, infity, infity, infity, infity},
                {infity, infity, infity, infity, infity, infity, infity,      3, infity,      3, infity, infity, infity},
                {infity, infity, infity, infity, infity, infity, infity, infity, infity, infity,      1, infity, infity},
                {infity, infity, infity, infity, infity, infity, infity, infity, infity, infity, infity,      6, infity},
                {infity, infity, infity, infity, infity, infity, infity, infity, infity, infity, infity, infity,      7},
                {infity, infity, infity, infity, infity, infity, infity, infity, infity,      8, infity, infity, infity}

        };
        int n = 13;

        AdjListDirNetwork net(vexs, n);

        for (int u = 0; u < n; u++)
            for (int v = n-1; v >=0; v--)
                if (m[u][v] != infity) net.InsertArc(u, v, m[u][v]);

        cout << "the original graph:" << endl;
        net.Display();					// 显示网net
        cout << endl;
        system("PAUSE");				// 调用库函数system()

        int **dist, **path;
        // 分配存储空间
        dist = new int *[net.GetVexNum()], path = new int *[net.GetVexNum()];
        for (int i = 0; i < net.GetVexNum(); i++)	{
            dist[i] = new int[net.GetVexNum()];
            path[i] = new int[net.GetVexNum()];
        }

        ShortestPathFloyd(net, path, dist);	// 用Floyd算法求最短路径
        DisplayPathAndDist(net, path, dist);// 显示最短路径
        cout << endl << endl;

        // 释放存储空间
        for (int j = 0; j < net.GetVexNum(); j++)    {
            delete []dist[j];
            delete []path[j];
        }
        delete []dist; delete []path;
    }
    catch (Error err)					// 捕捉并处理异常
    {
        err.Show();						// 显示异常信息
    }

    system("PAUSE");					// 调用库函数system()
    return 0;							// 返回值0, 返回操作系统
}
