//此题有问题，没有考虑确定次序后，后边的条件使原来的条件矛盾
//我哭了，这个tm消磨了我多少时间！！！ 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm> 
using namespace std;
#define Fin freopen("input.txt","r",stdin)
int relation[30][30]={0};
int pos[30]={0};
int n=0,m=0;
char a,b;
inline void initial()
{
	memset(relation,0,sizeof(relation));
	for(int i=0;i<n;++i){
		pos[i]=i;	
	}
}
int expand_relation()
{
	//floyd 关系传递 
	for(int k=0;k<n;++k)
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
			{
				if(i==j || j==k || i==k) continue;
				relation[i][j] |= relation[i][k]&relation[k][j];
				if(relation[i][j] && relation[j][i]){
					return -1; //出现矛盾 
				} 
			}
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
		{
			if(i==j) continue;
			if(!relation[i][j] && !relation[j][i]){
				return 0; //关系不确定 
			}
		}
	return 1; //关系确定 
}
bool Comp(const int &a,const int &b)
{
	return relation[a][b];
}
int main()
{
//	Fin; 
	while(cin>> n>> m)
	{
		if(n==0) break;
	 	initial(); //初始化 
		int judge=0;
		for(int i=1;i<=m;++i)
		{
			cin>> a; cin.get();
			cin>> b;
			if(judge==-1 || judge==1) continue;//已经出现矛盾 
			
			int u= a-'A', v= b-'A';
			relation[u][v]=1;
			if(relation[v][u]){
				judge= -1;
				printf("Inconsistency found after %d relations.\n",i);
			}
			if(judge==-1) continue;
			judge= expand_relation(); 
			if(judge==-1){
				printf("Inconsistency found after %d relations.\n",i);
				continue;	
			}
			else if(judge==1){
				sort(pos,pos+n,Comp);
				printf("Sorted sequence determined after %d relations: ",i);
				for(int i=0;i<n;++i)
					printf("%c",pos[i]+'A');
				puts(".");
			} 
			else continue;
		}
		if(judge==0)	//puts自带回车 
			puts("Sorted sequence cannot be determined.");
		
	}
	return 0;
}
