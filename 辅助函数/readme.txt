sort.h里面放了大量的辅助函数
kdTree用法
kd树使用方法（该kd树最多支持三维数据的搜索且使用qt开发，现在看来这个kd树写的比较粗糙，仅供参考)
提供两种搜索方法
Data search(KdNode* node , QVector3D pos); //寻找最近邻
QVector<Data> search(KdNode *node,float radius,QVector3D pos);//寻找范围点
Data数据结构里主要含有（ QVector3D value; int index）值和值对应的下表

KdTree mtree;   //声明
Range range(0,0,0,w,h,0);//定义需要搜搜索区域的大小,Range在kdtree.h已定义。搜索范围是（0，0，0）->(w,h,0) 因为是图片处理，第三维未使用
mtree.init(range,points); //初始化kd树，points的类型为QVector<QVector3D>
//搜索与point点距离范围为20以内的所有点
QVector<Data> neighbor = mtree.search(mtree.header(),20,point);
//找到与point 最近的点
Data neighbor = mtree.search(mtree.header(),20,point);