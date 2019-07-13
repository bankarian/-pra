//有向图强连通： tarjan
//无向图强连通： 并查集
#include <iostream>
#include <algorithm>
using namespace std;
const int maxv = 1e4 + 4, maxe = 5 * 1e4 + 4;
struct Edge{
	int to, next;
}e[maxe];
int head[maxv], cnte;
inline void add_edge(const int& from, const int& to){
	cnte += 1;
	e[cnte].to = to, e[cnte].next = head[from];
	head[from] = cnte;
	return;
}
int n, m;
int dfn[maxv], low[maxv], index, scc_cnt;
int num[maxv];
int mystack[maxv], top;
bool in_stack[maxv];
// int belong[maxv];
void tarjan(const int& q){
	dfn[q] = low[q] = ++index;
	mystack[++top] = q;		in_stack[q] = true;
	for(int i=head[q]; i; i = e[i].next){
		if(!dfn[e[i].to]){
			tarjan(e[i].to);
			low[q] = min(low[q], low[e[i].to]);
		}else if(in_stack[e[i].to]){
			low[q] = min(low[q], dfn[e[i].to]);
		}else 
			continue;
	}
	int v = 0;
	if(dfn[q] == low[q]){	//找到强连通分量子树上的根节点
		scc_cnt += 1;
		do{//退栈
			num[scc_cnt] += 1;	//统计强连通分量上点的数量
			v = mystack[top--];
			// belong[v] = scc_cnt;
			in_stack[v] = false;
		}while(q != v);	//q == v 时，q（v）已经退栈
	}
	return;
}
void get_info(){
	cin >> n >> m;
	int a=0, b=0;
	while(m--){
		cin >> a >> b;
		add_edge(a, b);
	}
	return;
}
void solve(){
	int ans = 0;
	for(int i=1; i<=n; ++i){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=1; i<=scc_cnt; ++i){
		if(num[i] > 1)
			ans += 1;
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