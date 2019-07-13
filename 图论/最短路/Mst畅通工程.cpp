//http://acm.hdu.edu.cn/showproblem.php?pid=1233
//���ͣ���С������
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int Maxn = 50*99+5; //����� 
const int Point = 105;
struct Node{
	int u,v,w; //�� ĩ Ȩ 
}node[Maxn]={0};
int Root[Point],Len[Point]={0};
int N,M;
int FindRoot(int q)
{
	while(q ^ Root[q]){
		Root[q] = Root[Root[q]];//ѹ��·��
		q = Root[q]; 
	}return q;
} 
void Unite(const int &a,const int &b)
{
	int rootA = FindRoot(a), rootB = FindRoot(b);
	if(rootA == rootB) return;//�Ѿ���ͨ 
	//С���������� 
	if(Len[rootA]>Len[rootB]){
		Root[rootB] = rootA;
	}
	else{
		if(Len[rootA] == Len[rootB]) Len[rootB] += 1;
		Root[rootA] = rootB;
	}
}
inline bool Comp(const Node &a,const Node &b)
{
	return a.w<b.w;
}
int Kruskal()
{
	sort(node,node+M,Comp);
	//����С�ı߿�ʼѡ��
	int edgeCnt = 0;//��¼ѡ�õı��� 
	int sumW = 0; 
	for(int i=0;i<M;++i)
	{
		if(FindRoot(node[i].u) ^ FindRoot(node[i].v)){
			//���˵㲻��ͬһ����ͨ�飬�������� 
//			printf("%d-->%d,w==%d\n",node[i].u,node[i].v,node[i].w);
			Unite(node[i].u,node[i].v);
//			printf("rootU=%d,rootV=%d\n",Root[node[i].u],Root[node[i].v]);
			edgeCnt += 1;
			sumW += node[i].w;
		}
		if(edgeCnt == N-1){//�ﵽ�������� 
			return sumW;
		}
	}
} 
inline void Initial()
{
	for(int i=1;i<Point;++i)	Root[i] = i;
	memset(Len,0,sizeof(Len));
}
int main()
{
	while(~scanf("%d",&N) && N!=0)
	{
		Initial();
		M = N*(N-1)/2;
		for(int i=0;i<M;++i){
			scanf("%d%d%d",&node[i].u,&node[i].v,&node[i].w);
		}
		printf("%d\n",Kruskal());
	}	
	return 0;
} 
