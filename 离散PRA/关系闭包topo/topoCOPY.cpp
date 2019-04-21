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
// ��� 
vector<int> G[N];
queue<int> q;
void initial()
{
	memset(in, 0, sizeof(in));
	for(int i=0;i<n;++i){
		G[i].clear(); 
		vector<int>().swap(G[i]); //����ڴ�
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
			q.push(i); //���Ϊ��ĵ�
	pos= 0;
	bool Sure= true;
	while(!q.empty())
	{
		if(q.size()>1) Sure= false;
		int node= q.front();
		q.pop();
		Result[pos++]= node; //����ڵ� 
		for(int i=0;i<G[node].size();++i){
			in[G[node][i]] -= 1;
			if(!in[G[node][i]]) //��ȱ�Ϊ��
				q.push(G[node][i]); 
		}
	} 
	if(pos<n) return 1; //�л���������ì�� 
	if(!Sure) return 2; //��ϵδȷ�� 
	return 3; //�ź��� 
}
int main()
{
	int x=0,y=0,i=0,flag=0,ok=0,step=0;
	while(~scanf("%d%d*c",&n,&m)){  //*����һ��c(char)���� 
		if(!n || !m) break;
		initial();	
		flag= 2;
		ok= false;
		for(int i=1;i<=m;++i)
		{
			cin>> sm;  cin.get();
			cin>> bi;
			if(ok) continue; //�лػ��������Ѿ�Ψһ����
			int u= sm-'A', v= bi-'A'; 
			if(!Find(u,v)){
				G[u].push_back(v); //���С���������Сָ���Ϊ���� 
				++in[v]; //v�����ͳ��
			}  
//			else if(cha=='>' && !Find(v,u)){
//				G[v].push_back(u);
//				++in[u];
//			} 
			//����������������һ�ε�in ��ԭ
			memcpy(temp, in, sizeof(in));
			flag= TopoSort();	 
			memcpy(in, temp, sizeof(temp));
			if(flag != 2){ //Ҫô�ź���Ҫô��ì�� 
				step= i; 
				ok= true;
			}
		}
		if(flag==3){ //�ź��� 
			printf("Sorted sequence determined after %d relations: ",step);
			for(int i= 0; i<pos; ++i)
				printf("%c",Result[i]+'A');
			printf(".\n");
		} 
		else if(flag==1){ //��ì�� 
			printf("Inconsistency found after %d relations.\n",step);
		}
		else if(flag==2){ //�޷�ȷ�� 
			printf("Sorted sequence cannot be determined.\n");
		}
	}
	return 0;
}


