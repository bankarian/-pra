/**Minimum Spanning Tree 
	Prim �㷨���Ե�Ϊ����.  �����ڱ߽ϳ���
	����һ��Ϊ��ʼ���ڸõ����ͨ��������һ������ĵ㣬�ؿ���ͨ��
	�������������е㶼�ҵ�. --���ĵ�����
 **/
#include <iostream>
#include <cstdio>
#include <cstring> 
using namespace std;
#define Inf 0x3f3f3f3f
const int maxn = 30;
int node[maxn][maxn]={0}; //�߽ϳ���,���ڽӾ��������ľ��� 
int N=0,M=0,sumW=0;
int vis[maxn]={0},minCnt[maxn]={0}; //��������С���� 
/**�Ƚ�q�ŵ�����,�γ�һƬ��ʼ���� 
	�������еĵ�,�ҳ���q������ľ��� 
	��� �������еĵ� 
	O2
**/ 
void Prim(int q) 
{
	for(int i=1;i<=N;++i){
			minCnt[i] = node[q][i];
	} 
	vis[q] = 1; 
	for(int i=1;i<N;++i){//����N-1��ѭ������ʣ�µĵ� 
		int minNode;	 //�ڷ�������������ĵ�
		int minLen = Inf;
		for(int j=1;j<=N;++j){
			if(!vis[j] && minCnt[j]<minLen){ //j q�������� 
				minLen = minCnt[j];
				minNode = j; //Ͱ������С 
			}
		}
		sumW += minLen; 		//��������Ȩֵ
		vis[minNode] = 1;
		for(int j=1;j<=N;++j){	//������,���������㵽������С���� 
			if(!vis[j])
			minCnt[j] = (node[minNode][j]<minCnt[j])?node[minNode][j]:minCnt[j]; 
		} //�����ҵ������г���,�жϴ˵��Ƿ��ܸ�������������ľ��� 
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
		node[v][u] = w;//���� 
	}
	Prim(1);
	return 0;
} 
