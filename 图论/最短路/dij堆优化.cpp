#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define ll long long 
#define Inf	2345678901
const int maxe = 50000 + 5, maxv = 50000 + 5;
struct Edge{
	int to, w;	int next;
	Edge(int a=0, int b=0, int c=0):to(a), w(b), next(c){}
}e[maxe * 2];
int head[maxv], cnte, pw[maxv];
struct Node{
	int u; ll dis;
	Node(int a=0, ll b=0):u(a), dis(b){}
	bool operator < (const Node& b) const{
		return this->dis > b.dis;
	}
};
bool vis[maxv];
ll ans, dis[maxv];
int nv, ne, a, b, w, st, t;

inline void ini()
{
	memset(head, 0, sizeof(head));
	cnte = ans = 0;
}
inline void add_edge(const int& from, const int& to, const int& w){
	++cnte;
	e[cnte].to = to, e[cnte].w = w;
	e[cnte].next = head[from];
	head[from] = cnte;
	return;
}
//与Prim的区别，入队更新的是到源点的距离dis[cur.u] + e[i].w
//Prim入队更新的的是到新生成的树的距离e[i].w
//已经确定过的点就不要再入队了，减少stl中不必要的排序
void dijkstra(){
	memset(vis, false, sizeof(vis));
	for(int i=1; i<=nv; ++i) dis[i] = Inf;	//注意这里的Inf不是0x3f3f3f3f只能用循环赋值
	dis[st] = 0;
	priority_queue<Node> pq;	while(pq.size())	pq.pop();
	pq.push(Node(st, 0));
	while(pq.size()){	
		Node cur = pq.top();
		pq.pop();
		if(vis[cur.u]) continue;
		vis[cur.u] = true;
		for(int i = head[cur.u]; i; i = e[i].next)
		{
			if(vis[e[i].to]) continue;
			if(dis[e[i].to] > dis[cur.u] + e[i].w){
				dis[e[i].to] = dis[cur.u] + e[i].w;
				pq.push(Node(e[i].to, dis[e[i].to]));
				//无需再判断是否已经确定，直接入队即可，因为每次弹出的值都是经过筛选的最小值
				//且访问过的不会再操作
			}
			else continue;
		}
	}
	return;
}
inline int read(){
	char ch = getchar();
	int ans = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9'){
		ans = (ans << 3) + (ans << 1) + ch - '0';
		ch = getchar();
	}return ans;
}
int main()
{
	t = read();
	while(t--){
		ini();
		nv = read(), ne = read(), st = 1;
		for(int i=1; i<=nv; ++i) 
			pw[i] = read();
		for(int i=0; i<ne; ++i){
			a = read(), b = read(), w = read();
			add_edge(a, b, w);
			add_edge(b, a, w);
		}
		dijkstra();
		bool have_ans = true;
		for(int i=1; i<=nv; ++i){
			if(dis[i] == Inf){
				have_ans = false;
				break;
			}
			ans += dis[i] * pw[i];
		}
		if(have_ans) printf("%lld\n", ans);
		else puts("No Answer");
	}
	
	return 0;
}