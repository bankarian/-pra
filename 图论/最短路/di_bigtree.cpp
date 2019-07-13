#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define ll long long 
#define Inf 0x3f3f3f3f
const int maxn = 50000 + 5, st = 1;
struct Edge{
	int to, w;	int next;
	Edge(int a=0, int b=0, int c=0):to(a), w(b), next(c){}
}e[maxn * 2];
int head[maxn], cnte, pw[maxn];
struct Node{
	int u; ll dis;
	Node(int a=0, ll b=0):u(a), dis(b){}
	bool operator < (const Node& b) const{
		return this->dis > b.dis;
	}
};
bool vis[maxn];
ll ans, dis[maxn];
int nv, ne, a, b, w, t;

inline void ini(){
	cnte = ans = 0;
	memset(head, 0, sizeof(head));
	return;
}
inline void add_edge(const int& from, const int& to, const int& w){
	++cnte;
	e[cnte].to = to, e[cnte].w = w;
	e[cnte].next = head[from];
	head[from] = cnte;
	return;
}
void dijkstra(){
	memset(vis, false, sizeof(vis));	memset(dis, Inf, sizeof(dis));
	dis[st] = 0;
	priority_queue<Node> pq;
	pq.push(Node(st, 0));
	while(pq.size()){
		Node cur = pq.top();
		pq.pop();
		if(vis[cur.u]) continue;
		vis[cur.u] = true;
		for(int i = head[cur.u]; i; i = e[i].next){
			if(dis[e[i].to] > dis[cur.u] + e[i].w){
				dis[e[i].to] = dis[cur.u] + e[i].w;
				pq.push(Node(e[i].to, dis[e[i].to]));
			}
			else continue;
		}
	}
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
		nv = read(), ne = read();
		for(int i=1; i<=nv; ++i) 
			pw[i] = read();
		for(int i=0; i<ne; ++i){
			a = read(), b = read(), w = read();
			add_edge(a, b, w);
			add_edge(b, a, w);
		}
		if(nv == 1 || nv == 0 || ne == 0){
			puts("0");
			continue;
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