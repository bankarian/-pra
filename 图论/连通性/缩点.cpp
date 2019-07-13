#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
inline int read(){
	char ch = getchar();
	int ans = 0, tool = 1;
	while(ch < '0' || ch > '9'){
		if(ch == '-') tool = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		ans = (ans << 3) + (ans << 1) + ch - '0';
		ch =getchar();
	}return (ans * tool);
}
const int maxv = 1e4 + 5, maxe = 1e5 + 5;
struct Edge{
	int from, to, next;
}e[maxe], e2[maxe];
int head[maxv], cnte;
inline void add_edge(const int& from, const int& to, Edge e[]){
	cnte += 1;
	e[cnte].to = to, e[cnte].from = from, e[cnte].next = head[from];
	head[from] = cnte;
	return;
}
int dfn[maxv], low[maxv], num[maxv], mystack[maxv], belong[maxv];
int pw[maxv], f[maxv];
bool in_stack[maxv];
int scc_cnt, top, indx, n, m, ans;

void tarjan(const int& q){
	dfn[q] = low[q] = ++indx;
	mystack[++top] = q;
	in_stack[q] = true;
	for(int i = head[q]; i; i = e[i].next){
		if(!dfn[e[i].to]){
			tarjan(e[i].to);
			low[q] = min(low[q], low[e[i].to]);
		}else if(in_stack[e[i].to]){
			low[q] = min(low[q], dfn[e[i].to]);
		}else
			continue;
	}
	int v = 0;
	if(dfn[q] == low[q]){
		scc_cnt += 1;
		do{
			v = mystack[top--];
			num[scc_cnt] += pw[v];	//强连通分量的总权值
			in_stack[v] = false;
			belong[v] = scc_cnt;
		}while(q != v);
	}
	return;
}
inline void get_info(){
 	n = read(), m = read();
 	for(int i=1; i<=n; ++i)	pw[i] = read();
 	int a=0, b=0;
 	for(int i=1; i<=m; ++i){
 		a = read(), b = read();
 		add_edge(a, b, e);
 	}
 	return;
}
void new_graph(){//新建单向无环图
	memset(head, 0, sizeof(head));	cnte = 0;
	for(int i=1; i<=m; ++i){
		if(belong[e[i].from] != belong[e[i].to]){
			add_edge(belong[e[i].from], belong[e[i].to], e2);	//强连通分量为点，即所谓的缩点
		}else
			continue;
	}
	return;
}
//在新建的单向无环图上进行dp，注意此时权值为强连通缩点的权值
int memor_dp(int id){
	if(f[id]) return f[id];
    f[id] = num[id];
    int tmpmax = 0;
	for(int i = head[id]; i; i = e2[i].next){
		tmpmax = max(tmpmax, memor_dp(e2[i].to));
	}//注意这里不能直接用f[id]相加进行最大的取值，要用一个临时变量
	f[id] += tmpmax;
	return f[id];
}
void solve(){
	for(int i=1; i<=n; ++i){//强连通缩点
		if(!dfn[i]){
			tarjan(i);
		}else
			continue;
	}
	new_graph();
	for(int i=1; i<=scc_cnt; ++i){
		ans = max(ans, memor_dp(i));
	}
	printf("%d\n", ans);
	return;
}
int main()
{
	get_info();
	solve();
	return 0;
}
