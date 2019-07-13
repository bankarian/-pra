#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
#define Inf 0x3f3f3f3f
const int maxv = 1e4 + 4, maxe = 2 * 1e5 + 4, ill = 3;
struct Edge{
	int to, w;	int next;
}e1[maxe], e2[maxe];
int head1[maxv], head2[maxv], cnte;
int dis[maxv], judge[maxv], ans;
bool can_reach[maxv], vis[maxv];
struct Node{
	int u, w;
	Node(int a=0, int b=0): u(a), w(b){}
	bool operator < (const Node& b) const{
		return this->w > b.w;
	}
};
int n, m, s, t, a, b;
//bfs预处理反图，can_reach标记反向能到达的点，即合法点
bool bfs(const int& en, const int& st){
	//处理反向图
	queue<int> que; 	while(que.size()) que.pop();
	que.push(en);
	while(que.size()){	
		int cur = que.front();	que.pop();
		if(can_reach[cur])	continue;
		can_reach[cur] = true;
		for(int i = head2[cur]; i; i = e2[i].next){
			que.push(e2[i].to);
		}
	}
	//正图，注意这里是用正向图的边！！因为最后是正向遍历
	for(int i=1; i<=n; ++i){
		if(can_reach[i])
			for(int j = head1[i]; j; j = e1[j].next){//所有与i相连的出边
				if(!can_reach[e1[j].to]){//i能到达终点但是不合法
					judge[i] = ill; break;
				}
			}
		else continue;
	}
	if(can_reach[st] && judge[st] != ill) return true;
	return false;
}
//注意之前标记过，加入节点前判读起出边的节点是否能到达终点
void dijkstra(const int& st, const int& en){
	memset(dis, Inf, sizeof(dis));
	dis[st] = 0;
	priority_queue<Node> pq;	while(pq.size()) pq.pop();
	pq.push(Node(st, 0));
	while(pq.size()){
		Node cur = pq.top();
		pq.pop();
		if(vis[cur.u]) continue;
		vis[cur.u] = true;
		for(int i = head1[cur.u]; i; i = e1[i].next){
			if(vis[e1[i].to]) continue;
			if(!can_reach[e1[i].to]) continue;
			if(judge[e1[i].to] == ill && e1[i].to != en) continue;//可连通，但不合法

			if(dis[e1[i].to] > dis[cur.u] + e1[i].w){
				dis[e1[i].to] = dis[cur.u] + e1[i].w;
				pq.push(Node(e1[i].to, dis[e1[i].to]));
			}
		}
	}
	if(dis[en] == Inf) ans = -1;
	else ans = dis[en];
	return;
}
inline void add_edge(const int& from, const int& to){
	cnte += 1;
	e1[cnte].to = to, e1[cnte].w = 1;
	e1[cnte].next = head1[from];
	head1[from] = cnte;

	e2[cnte].to = from, e2[cnte].w = 1;
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
inline void get_info(){
	n = read(), m = read();
	while(m--){
		a = read(), b = read();
		add_edge(a, b);
	}
	s = read(), t = read();
	return;
}
inline void solve(){
	if(bfs(t, s)){
		dijkstra(s, t);
		printf("%d\n", ans);
	}
	else puts("-1");
	return;
}
int main()
{
	get_info();
	solve();
	return 0;
}