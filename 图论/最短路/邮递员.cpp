//这题最巧秒的是求所有点到源点的距离
//单源问题，单终点问题可以通过正反图相互转化！
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
#define ll long long 
#define Inf 0x3f3f3f3f
const int maxv = 1000 + 4, maxe = 1e5 + 4, st = 1;
struct Edge{
	int to, w, next;
}e1[maxe], e2[maxe];	//1正图 2反图
int cnte, head1[maxv], head2[maxv];
struct Node{
	int index;	ll dis;
	Node(int a=0, ll b=0):index(a), dis(b){}
	const bool operator < (const Node& b) const{
		return this->dis > b.dis;
	}
};
bool vis[maxv];
ll dis1[maxv], dis2[maxv], ans;
int n, m, u, v, w;

inline void ini(){
	memset(dis1, Inf, sizeof(dis1));
	memset(dis2, Inf, sizeof(dis2));
	dis1[st] = dis2[st] = 0;
	return;
}
inline void add_edge(const int& from, const int& to, const int& w){
	cnte += 1;
	e1[cnte].to = to, e1[cnte].w = w;
	e1[cnte].next = head1[from];
	head1[from] = cnte;

	e2[cnte].to = from, e2[cnte].w = w;
	e2[cnte].next = head2[to];
	head2[to] = cnte;
	return;
}
inline int read(){
	char ch = getchar();
	int ans = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9'){
		ans = (ans << 3) + (ans << 1) + ch - '0';
		ch = getchar();
	}return ans;
}
//堆优化dijkstra,传入不同的图
void dijkstra(const int hd[maxv], const Edge edge[maxe], ll dis[maxv]){
	memset(vis, false, sizeof(vis));
	priority_queue<Node> pq;	while(pq.size()) pq.pop();
	pq.push(Node(st, 0));
	while(pq.size()){
		Node cur = pq.top();
		pq.pop();
		if(vis[cur.index]) continue;
		vis[cur.index] = true;
		for(int i = hd[cur.index]; i; i = edge[i].next){
			if(vis[edge[i].to]) continue;
			if(dis[edge[i].to] > dis[cur.index] + edge[i].w)
			{	
				dis[edge[i].to] = dis[cur.index] + edge[i].w;
				pq.push(Node(edge[i].to, dis[edge[i].to]));
			}
		}
	}
	return;
}
int main()
{
	ini();
	n = read(), m = read();
	while(m--){
		u = read(), v = read(), w = read();
		add_edge(u, v, w);
	}
	dijkstra(head1, e1, dis1);
	dijkstra(head2, e2, dis2);
	for(int i=2; i<=n; ++i){
		ans += dis1[i] + dis2[i];	//去，回
	}
	printf("%lld\n", ans);
	return 0;
}