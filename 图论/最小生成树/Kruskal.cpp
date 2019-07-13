//Minimum Spanning Tree. 
//kruskal算法 以边为主导+贪心.  适用于边较稀疏 
//先连起最短的边,某边两点当前不在同一个连通区,则连接
//结束条件:M = N-1. --树的边点特性 
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 30;
int N=0,M=0; //n定点数，m边数 
int Root[maxn]={0}, Len[maxn]={0};//根 树的高度 
struct Node{
	int u=0,v=0,w=0;
	//边(u,v)  权值 
}node[maxn];
//结合并查集 
inline int FindRoot(int q)
{
	while(q != Root[q]){ //压缩路径 
		Root[q] = Root[Root[q]];
		q = Root[q];
	}return q;
}
inline void Unite(int x,int y)
{
	Root[FindRoot(x)] = Root[FindRoot(y)];	 
}
bool Comp(const Node &a,const Node &b){
	return a.w < b.w;
}
//贪心，找边，防连通 
void Kruskal()
{
	int sumW = 0;//生成树的权值 
	int cntEdge = 0;//已选边数 
	sort(node,node+M,Comp);//边权值升序
	for(int i=0;i<M;++i){ //遍历边 
		if(FindRoot(node[i].u) ^ FindRoot(node[i].v))//不在同一个连通块 
		{	//注意这里是用FindRoot()查找，不要用成了Root[]~ 
			printf("%dRoot==%d, %dRoot==%d\n",node[i].u,Root[node[i].u],node[i].v,Root[node[i].v]);
			printf("%d , %d,  w==%d\n",node[i].u,node[i].v,node[i].w);
			Unite(node[i].u, node[i].v);
			sumW += node[i].w;
			cntEdge += 1; //统计节点数 
		} 
		if(cntEdge == N-1) break; //N-1条边已经成树 
	}
	printf("THE WEIGHT OF MST IS %d.\n", sumW); 
} 
void Initial()
{
	for(size_t i=0;i<N;++i){ 
		Root[i] = i;//初始时，每个点就是自己的根 
	}
} 
int main()
{
	freopen("input0.txt","r",stdin);
	cin>> N >> M;
	for(int i=0;i<M;++i){
		scanf("%d%d%d",&node[i].u, &node[i].v, &node[i].w);
	}Initial();
	Kruskal();
	return 0;
 } 
