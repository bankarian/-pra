/**Minimum Spanning Tree 
	Prim 算法：以点为主导.  适用于边较稠密
	任找一点为起始，在该点的连通区外找另一个最近的点，拓宽连通区
	结束条件：所有点都找到. --树的点特性
 **/
#include <iostream>
#include <cstdio>
#include <cstring> 
using namespace std;
#define Inf 0x3f3f3f3f
const int maxn = 30;
int node[maxn][maxn]={0}; //边较稠密,用邻接矩阵，两点间的距离 
int N=0,M=0,sumW=0;
int vis[maxn]={0},minCnt[maxn]={0}; //到树的最小距离 
/**先将q放到树中,形成一片初始树域 
	遍历所有的点,找出与q的树域的距离 
	标记 进入树中的点 
	O2
**/ 
void Prim(int q) 
{
	for(int i=1;i<=N;++i){
			minCnt[i] = node[q][i];
	} 
	vis[q] = 1; 
	for(int i=1;i<N;++i){//进行N-1次循环访问剩下的点 
		int minNode;	 //在非树中离树最近的点
		int minLen = Inf;
		for(int j=1;j<=N;++j){
			if(!vis[j] && minCnt[j]<minLen){ //j q树域间距离 
				minLen = minCnt[j];
				minNode = j; //桶排找最小 
			}
		}
		sumW += minLen; 		//生成树的权值
		vis[minNode] = 1;
		for(int j=1;j<=N;++j){	//树扩大,更新其他点到树的最小距离 
			if(!vis[j])
			minCnt[j] = (node[minNode][j]<minCnt[j])?node[minNode][j]:minCnt[j]; 
		} //遍历找到的所有出边,判断此点是否能辅助缩短其他点的距离 
	}
	printf("THE WEIGHT OF MST IS %d.\n",sumW);
}
void Initial()
{
	memset(vis,0,sizeof(vis));
	memset(minCnt,Inf,sizeof(minCnt));
	memset(node,Inf,sizeof(node));
}
int main()
{
	freopen("input0.txt","r",stdin);
	cin>> N>> M;
	Initial();
	int u,v,w;
	for(int i=0;i<M;++i){
		scanf("%d%d%d",&u,&v,&w);
		node[u][v] = w;
		node[v][u] = w;//无向 
	}
	Prim(1);
	return 0;
} 
