#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int N = 1e3 + 5, M = 1e4 + 5, Inf = 0x3f3f3f3f;
struct Edge{
	int to, w;	int next;
}e[M];
int head[N], cnte;
int t, n, m, u, v, w, st, en;
int dis[N][2], vis[N][2], cnt[N][2];
struct Node{
	int index, dis, type;
	Node(int a=0, int b=0, int c=0):index(a), dis(b), type(c){}
	bool operator < (const Node& b) const{
		return this->dis > b.dis;
	}
};//看到这各重载应该就懂要干嘛了吧，对，用priority_queue优化dijkstra!

void dijkstra(){
	priority_queue<Node> pq;
	memset(vis, 0, sizeof(vis));
	memset(cnt, 0, sizeof(cnt));
	for(int i=1; i<=n; ++i) 
		dis[i][0] = dis[i][1] = Inf;
	dis[st][0] = 0;	cnt[st][0] = 1;//最短路确定存在
	// pq.push({st, 0, 0});
	pq.push(Node(st, 0, 0));

	while(pq.size()){ 
		Node cur = pq.top();	pq.pop();
		if(vis[cur.index][cur.type]) continue;
		vis[cur.index][cur.type] = true;

		for(int i = head[cur.index]; i; i = e[i].next)
		{	
			int nindex = e[i].to, w = e[i].w;
			if(dis[nindex][0] > dis[cur.index][cur.type] + w){
				dis[nindex][1] = dis[nindex][0];
				cnt[nindex][1] = cnt[nindex][0];

				dis[nindex][0] = dis[cur.index][cur.type] + w;
				cnt[nindex][0] = cnt[cur.index][cur.type];

				// pq.push({nindex, dis[nindex][0], 0});
				// pq.push({nindex, dis[nindex][1], 1});
				pq.push(Node(nindex, dis[nindex][0], 0));
				pq.push(Node(nindex, dis[nindex][1], 1));
			}
			else{
				if(dis[nindex][0] == dis[cur.index][cur.type] + w)
					cnt[nindex][0] += cnt[cur.index][cur.type];
				else{
					if(dis[nindex][1] > dis[cur.index][cur.type] + w){
						dis[nindex][1] = dis[cur.index][cur.type] + w;
						cnt[nindex][1] = cnt[cur.index][cur.type];

						// pq.push({nindex, dis[nindex][1], 1});
						pq.push(Node(nindex, dis[nindex][1], 1));
					}
					else{
						if(dis[nindex][1] == dis[cur.index][cur.type] + w)
							cnt[nindex][1] += cnt[cur.index][cur.type];
					}
				}
			}
		}
	}
	return;
}
inline void add_edge(const int& from, const int& to, const int& w){
	++cnte;
	e[cnte].to = to;	e[cnte].w = w;
	e[cnte].next = head[from];
	head[from] = cnte;
	return;
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
	t = read();
	while(t--){
		memset(head, 0, sizeof(head));	cnte = 0;

		n = read(), m = read();
		for(int i = 1; i <= m; ++i){
			u = read(), v = read(), w = read();
			add_edge(u, v, w);
		}
		st = read(); en = read();
		dijkstra();
		if(dis[en][1] == dis[en][0] + 1)
			cnt[en][0] += cnt[en][1];
		printf("%d\n", cnt[en][0]);
	}
	return 0;
}




