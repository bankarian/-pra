//记录路径小技巧：pre_e记录向前边的编号，边结构体新增from属性方便回溯查找
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define Inf 0x3f3f3f3f
#define ll long long
const int maxv = 100 + 4, maxe = 5000 + 4, st = 1;
struct Edge{
	int from, to, w, next;
}e[maxe * 2];
struct Node{
	int u;	ll cost;
	Node(int a=0, ll b=0):u(a), cost(b){}
	bool operator < (const Node& b) const{
		return this->cost > b.cost;
	}
};
int head[maxv], pre_e[maxv], cnte;
ll dis[maxv], origin, cha;
bool vis[maxv], first = true;
int n, m, a, b, w;

inline void add_edge(const int& from, const int& to, const int& w){
	++cnte;
	e[cnte].from = from, e[cnte].to = to, e[cnte].w = w;
	e[cnte].next = head[from];
	head[from] = cnte;
	return;
}
inline int read(){
	char ch = getchar();
	int ans = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9'){
		ans = (ans << 3) + (ans << 1) + ch -'0';
		ch = getchar();
	}return ans;
}
void dijkstra(){
	memset(dis, Inf, sizeof(dis));	dis[st] = 0;
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
			if(dis[e[i].to] > dis[cur.u] + e[i].w){
				dis[e[i].to] = dis[cur.u] + e[i].w;
				if(first) pre_e[e[i].to] = i; //记录最短路上的边的编号
				pq.push(Node(e[i].to, dis[e[i].to]));
			}
		}
	}
	return;
}
inline void get_info(){
	n = read(), m = read();
	while(m--){
		a = read(), b = read(), w = read();
		add_edge(a, b, w);
		add_edge(b, a, w);
	}
	return;
}
inline void solve(){
	dijkstra();	origin = dis[n];
	first = false;	//下一次dijkstra不需要再记录边
	int i = n;
	while(pre_e[i]){
		int cur = pre_e[i];	//当前边的编号
		e[cur].w *= 2;
		// cout << "cur edge w" << e[cur].w << endl;
		dijkstra();
		cha = max(cha, dis[n] - origin);
		e[cur].w /= 2;
		i = e[cur].from;
		// cout << "cur edge from" << e[cur].from << endl;
	}
	printf("%lld\n", cha);
}
int main()
{
	get_info();
	solve();
	return 0;
}