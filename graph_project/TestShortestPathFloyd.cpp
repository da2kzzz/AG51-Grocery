#include "Assistance.h"				// ���������
#include "ShortestPathFloyd.h"		// ���������㷨

int main(void){
    try									// ��try��װ���ܳ����쳣�Ĵ���
	{
		int infity = DEFAULT_INFINITY;
		char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};
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

		AdjListDirNetwork<char, int> net(vexs, n);

		for (int u = 0; u < n; u++)
			for (int v = n-1; v >=0; v--)
				if (m[u][v] != infity) net.InsertArc(u, v, m[u][v]);

		cout << "the original graph:" << endl;
		net.Display();					// ��ʾ��net
		cout << endl;
		system("PAUSE");				// ���ÿ⺯��system()

		int **dist, **path;
		// ����洢�ռ�
		dist = new int *[net.GetVexNum()], path = new int *[net.GetVexNum()];
		for (int i = 0; i < net.GetVexNum(); i++)	{	
			dist[i] = new int[net.GetVexNum()]; 
            path[i] = new int[net.GetVexNum()]; 
		}

		ShortestPathFloyd(net, path, dist);	// ��Floyd�㷨�����·��
		DisplayPathAndDist(net, path, dist);// ��ʾ���·�� 
		cout << endl << endl;

		// �ͷŴ洢�ռ�
		for (int j = 0; j < net.GetVexNum(); j++)    {	
			delete []dist[j];
            delete []path[j]; 
		}
		delete []dist; delete []path;
	}
	catch (Error err)					// ��׽�������쳣
	{
		err.Show();						// ��ʾ�쳣��Ϣ
	}

	system("PAUSE");					// ���ÿ⺯��system()
	return 0;							// ����ֵ0, ���ز���ϵͳ
}

