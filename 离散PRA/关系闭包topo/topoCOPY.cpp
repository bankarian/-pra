#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue> 
using namespace std;
const int N=30;
int n=0,m=0,t=0,pos=0,num=0;
int in[N]={0},temp[N]={0},Result[N]={0};
char sm=0,cha=0,bi=0;
// 入度 
vector<int> G[N];
queue<int> q;
void initial()
{
	memset(in, 0, sizeof(in));
	for(int i=0;i<n;++i){
		G[i].clear(); 
		vector<int>().swap(G[i]); //清空内存
	}  
		
}
inline bool Find(int u,int v)
{
	for(int i=0;i<G[u].size();++i)
		if(G[u][i]==v) return true;
	return false;
}
int TopoSort()
{
	while(!q.empty()) q.pop();
	for(int i=0;i<n;++i)
		if(!in[i])
			q.push(i); //入度为零的点
	pos= 0;
	bool Sure= true;
	while(!q.empty())
	{
		if(q.size()>1) Sure= false;
		int node= q.front();
		q.pop();
		Result[pos++]= node; //结果节点 
		for(int i=0;i<G[node].size();++i){
			in[G[node][i]] -= 1;
			if(!in[G[node][i]]) //入度变为零
				q.push(G[node][i]); 
		}
	} 
	if(pos<n) return 1; //有环，即存在矛盾 
	if(!Sure) return 2; //关系未确定 
	return 3; //排好序 
}
int main()
{
	int x=0,y=0,i=0,flag=0,ok=0,step=0;
	while(~scanf("%d%d*c",&n,&m)){  //*跳过一个c(char)类型 
		if(!n || !m) break;
		initial();	
		flag= 2;
		ok= false;
		for(int i=1;i<=m;++i)
		{
			cin>> sm;  cin.get();
			cin>> bi;
			if(ok) continue; //有回环，或者已经唯一排序
			int u= sm-'A', v= bi-'A'; 
			if(!Find(u,v)){
				G[u].push_back(v); //结果小到大输出，小指向大，为出度 
				++in[v]; //v的入度统计
			}  
//			else if(cha=='>' && !Find(v,u)){
//				G[v].push_back(u);
//				++in[u];
//			} 
			//拷贝副本，用于下一次的in 还原
			memcpy(temp, in, sizeof(in));
			flag= TopoSort();	 
			memcpy(in, temp, sizeof(temp));
			if(flag != 2){ //要么排好序，要么有矛盾 
				step= i; 
				ok= true;
			}
		}
		if(flag==3){ //排好序 
			printf("Sorted sequence determined after %d relations: ",step);
			for(int i= 0; i<pos; ++i)
				printf("%c",Result[i]+'A');
			printf(".\n");
		} 
		else if(flag==1){ //有矛盾 
			printf("Inconsistency found after %d relations.\n",step);
		}
		else if(flag==2){ //无法确定 
			printf("Sorted sequence cannot be determined.\n");
		}
	}
	return 0;
}


