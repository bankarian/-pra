//节点数超过1000左右就不要考虑dijkstra + A*（用于求第k最短路）耗时较长
//统计最短路数利用times【】数组，注意初始化为1
//每次有最短路更新则times也更新==前一个节点的最短路数，因为前一个节点到当前节点的最短路数只能为1
//具体些是增加times[前一节点] * times【前一节点到当前节点】（就是1）
//一般没有负权，推荐使用稳定性更高的dijkstra+堆优化
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define Inf 0x3f3f3f3f
const int maxv = 2000 + 4, maxe = maxv * (maxv - 1), st = 1;
struct Node{
	int u, cost;
	Node(int a=0, int b=0):u(a), cost(b){}
	bool operator < (const Node& b) const{
		return this->cost > b.cost;
	}
};
bool vis[maxv];
int n, m, a, b, c;	int minLen, table[maxv][maxv];
long long times[maxv], h[maxv];

bool dijkstra(){
	memset(h, Inf, sizeof(h));
	h[st] = 0;
	for(int i=1; i<=n; ++i)	times[i] = 1;
	priority_queue<Node> pq;	while(pq.size()) pq.pop();
	pq.push(Node(st, 0));
	while(pq.size()){
		Node cur = pq.top();	pq.pop();
		if(vis[cur.u]) continue;
		vis[cur.u] = true;
		for(int i=1; i<=n; ++i){
			if(vis[i] || i == cur.u) continue;
			if(h[i] > h[cur.u] + table[cur.u][i]){
				times[i] = times[cur.u];
				h[i] = h[cur.u] + table[cur.u][i];
				pq.push(Node(i, h[i]));
			}
			else if(h[i] == h[cur.u] + table[cur.u][i]){
				times[i] += times[cur.u] * 1;
			}
			else continue;
		}
	}
	minLen = h[n];
	if(minLen == Inf) return false;
	return true;
}

inline int read(){
	char ch = getchar();
	int ans = 0;
	while(ch<'0' || ch>'9') ch = getchar();
	while(ch >= '0' && ch <= '9'){
		ans = (ans << 3) + (ans << 1) + ch - '0';
		ch = getchar();
	}return ans;
}
int main()
{
	n = read(), m = read();
	memset(table, Inf, sizeof(table));
	while(m--){
		a = read(), b = read(), c = read();
		table[a][b] = min(table[a][b], c);
	}
	if(dijkstra()){
		printf("%d %lld\n", minLen, times[n]);
	}
	else puts("No answer");
	return 0;
}