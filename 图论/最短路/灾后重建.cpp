#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define Inf 0x3f3f3f3f
#define ll long long
const int maxv = 200 + 4, maxe = (maxv - 1) * maxv / 2;
struct Edge{
	int to, w;	int next;
}e[maxe * 2];
int head[maxv], p_tm[maxv], cnte;
ll dis[maxv];
bool vis[maxv];
struct Node{
	int u;	ll cost;
	Node(int a, ll b): u(a), cost(b){}
	bool operator < (const Node& b) const{
		return this->cost > b.cost;
	}
};
int n, m, a, b, c;
int Q, x, y, tt;
//p_tm <= tm时该点才有效
bool dijkstra(const int& st, const int& en, const int& tm){
	if(p_tm[st] > tm || p_tm[en] > tm) 
		return false;
	for(int i=0; i<n; ++i){
		dis[i] = Inf;
	}dis[st] = 0;
	memset(vis, false, sizeof(vis));
	priority_queue<Node> pq;	while(pq.size()) pq.pop();
	pq.push(Node(st, 0));

	while(pq.size()){
		Node cur = pq.top();
		pq.pop();
		if(vis[cur.u]) continue;
		vis[cur.u] = true;
		for(int i = head[cur.u]; i; i = e[i].next){
			if(vis[e[i].to]) continue;
			if(p_tm[e[i].to] > tm) continue;	//该点还不能通行
			if(dis[e[i].to] > dis[cur.u] + e[i].w){
				dis[e[i].to] = dis[cur.u] + e[i].w;
				pq.push(Node(e[i].to, dis[e[i].to]));
			}
		}
	}
	return dis[en] != Inf;
}
inline int read(){
	char ch = getchar();
	int ans = 0, tool = 1;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9'){
		ans = (ans << 3) + (ans << 1) + ch - '0';
		ch = getchar();
	}return (ans * tool);
}
inline void add_edge(const int& from, const int& to, const int& w){
	cnte += 1;
	e[cnte].to = to, e[cnte].w = w;
	e[cnte].next = head[from];
	head[from] = cnte;
	return;
}
int main()
{
	// ll k[3]; memset(k, 0x3f, sizeof(k)/2); cout << k[1] << endl;
	n = read(), m = read();	
	for(int i=0; i<n; ++i){
		p_tm[i] = read();
	}
	while(m--){
		a = read(), b = read(), c = read();
		add_edge(a, b, c);
		add_edge(b, a, c);
	}
	Q = read();
	while(Q--){
		x = read(), y = read(), tt = read();
		if(dijkstra(x, y, tt)){
			printf("%lld\n", dis[y]);
		}
		else puts("-1");
	}
	return 0;
}