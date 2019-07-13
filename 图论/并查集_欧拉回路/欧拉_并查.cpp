//并查集连通 +（单向）欧拉路判断:http://poj.org/problem?id=1386 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
const int maxn = 30;
int N=0,T=0;
int Root[maxn]={0},out[maxn]={0},in[maxn]={0};
char str[1005]={0};
bool vis[maxn]={false};
int Id(char x){
	return x-'a'+1;
}
int FindRoot(int x)
{
	//找根+路径压缩 
	while(x^Root[x]){//未找到根 
		Root[x] = Root[Root[x]];
		x = Root[x];
	}
	return x;
}
inline void Unite(int x,int y)
{
	int rootX = FindRoot(x);
	int rootY = FindRoot(y);
	if(rootX == rootY) return ;//已经连通
	else{ //由于只有26个字母，这里就直接连,不判断树的高度 
		Root[rootX] = rootY;
	} 
}
inline void Initial()
{
	memset(out,0,sizeof(out));
	memset(in,0,sizeof(in));
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=26;++i) Root[i] = i;
}
bool HaveEuler()
{	//注意有两种判断：欧拉路 && 欧拉回路！ 
	int st=0,en=0,node=0;
	for(int i=1;i<=26;++i)
	{
		if(out[i]-in[i] == 1){
			st += 1;
		}
		else if(in[i]-out[i] == 1){
			en += 1;
		}
		else if(in[i] == out[i]) node += 1; 
		else return false; //若出入度相差>1则必然没有欧拉路 
		if(en>1 || st>1) return false;//不能一条通路 
	} 
	if((en==1&&st==1) || (node==26)) return true;
	return false;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		Initial();
		for(int i=0;i<N;++i){//边输入边连通 
			scanf("%s",str); getchar();
//			gets(str);
			int head = Id(str[0]);
			int tail = Id(str[strlen(str)-1]);
			++out[head], ++in[tail];
			vis[head]= vis[tail]= true;//标记哪些字母出现过 
			Unite(head,tail);
		}
		int cnt=0;
		for(int i=1;i<=26;++i){
			if(vis[i] && Root[i]==i) cnt += 1;
		}
		if(cnt^1){//根有多个,非连通
			puts("The door cannot be opened.");
			continue; //截断 
		}
		//连通，判断是否有欧拉路
		if(HaveEuler()){//存在欧拉路，成功连接！ 
			puts("Ordering is possible.");
		}
		else puts("The door cannot be opened.");
	}
	return 0;
}
