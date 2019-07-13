//Minimum Spanning Tree. 
//kruskal�㷨 �Ա�Ϊ����+̰��.  �����ڱ߽�ϡ�� 
//��������̵ı�,ĳ�����㵱ǰ����ͬһ����ͨ��,������
//��������:M = N-1. --���ıߵ����� 
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 30;
int N=0,M=0; //n��������m���� 
int Root[maxn]={0}, Len[maxn]={0};//�� ���ĸ߶� 
struct Node{
	int u=0,v=0,w=0;
	//��(u,v)  Ȩֵ 
}node[maxn];
//��ϲ��鼯 
inline int FindRoot(int q)
{
	while(q != Root[q]){ //ѹ��·�� 
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
//̰�ģ��ұߣ�����ͨ 
void Kruskal()
{
	int sumW = 0;//��������Ȩֵ 
	int cntEdge = 0;//��ѡ���� 
	sort(node,node+M,Comp);//��Ȩֵ����
	for(int i=0;i<M;++i){ //������ 
		if(FindRoot(node[i].u) ^ FindRoot(node[i].v))//����ͬһ����ͨ�� 
		{	//ע����������FindRoot()���ң���Ҫ�ó���Root[]~ 
			printf("%dRoot==%d, %dRoot==%d\n",node[i].u,Root[node[i].u],node[i].v,Root[node[i].v]);
			printf("%d , %d,  w==%d\n",node[i].u,node[i].v,node[i].w);
			Unite(node[i].u, node[i].v);
			sumW += node[i].w;
			cntEdge += 1; //ͳ�ƽڵ��� 
		} 
		if(cntEdge == N-1) break; //N-1�����Ѿ����� 
	}
	printf("THE WEIGHT OF MST IS %d.\n", sumW); 
} 
void Initial()
{
	for(size_t i=0;i<N;++i){ 
		Root[i] = i;//��ʼʱ��ÿ��������Լ��ĸ� 
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
