sort.h������˴����ĸ�������
kdTree�÷�
kd��ʹ�÷�������kd�����֧����ά���ݵ�������ʹ��qt���������ڿ������kd��д�ıȽϴֲڣ������ο�)
�ṩ������������
Data search(KdNode* node , QVector3D pos); //Ѱ�������
QVector<Data> search(KdNode *node,float radius,QVector3D pos);//Ѱ�ҷ�Χ��
Data���ݽṹ����Ҫ���У� QVector3D value; int index��ֵ��ֵ��Ӧ���±�

KdTree mtree;   //����
Range range(0,0,0,w,h,0);//������Ҫ����������Ĵ�С,Range��kdtree.h�Ѷ��塣������Χ�ǣ�0��0��0��->(w,h,0) ��Ϊ��ͼƬ��������άδʹ��
mtree.init(range,points); //��ʼ��kd����points������ΪQVector<QVector3D>
//������point����뷶ΧΪ20���ڵ����е�
QVector<Data> neighbor = mtree.search(mtree.header(),20,point);
//�ҵ���point ����ĵ�
Data neighbor = mtree.search(mtree.header(),20,point);