//http://acm.hdu.edu.cn/showproblem.php?pid=1233
//类型：最小生成树
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int Maxn = 50*99+5; //多边数 
const int Point = 105;
struct Node{
	int u,v,w; //起 末 权 
}node[Maxn]={0};
int Root[Point],Len[Point]={0};
int N,M;
int FindRoot(int q)
{
	while(q ^ Root[q]){
		Root[q] = Root[Root[q]];//压缩路径
		q = Root[q]; 
	}return q;
} 
void Unite(const int &a,const int &b)
{
	int rootA = FindRoot(a), rootB = FindRoot(b);
	if(rootA == rootB) return;//已经连通 
	//小树连到大树 
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
	//从最小的边开始选择
	int edgeCnt = 0;//记录选用的边数 
	int sumW = 0; 
	for(int i=0;i<M;++i)
	{
		if(FindRoot(node[i].u) ^ FindRoot(node[i].v)){
			//两端点不在同一个连通块，可以相连 
//			printf("%d-->%d,w==%d\n",node[i].u,node[i].v,node[i].w);
			Unite(node[i].u,node[i].v);
//			printf("rootU=%d,rootV=%d\n",Root[node[i].u],Root[node[i].v]);
			edgeCnt += 1;
			sumW += node[i].w;
		}
		if(edgeCnt == N-1){//达到树的最多边 
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
