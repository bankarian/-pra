#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
#define Inf 0x3f3f3f3f
const int maxv = 2000 + 4, maxe = 3000 + 4, st = 1;
struct Edge{
	int to, w, next;
}e[maxe * 2];
int head[maxv], cnte, dis[maxv], getin[maxv];
bool in_que[maxv];
int t, n, m, a, b, w;

inline void add_edge(const int& from, const int& to, const int& w){
	++cnte;
	e[cnte].to = to, e[cnte].w = w;
	e[cnte].next = head[from];
	head[from] = cnte;
	return;
}
inline int read(){
	char ch = getchar();
	int ans = 0, tool = 1;
	while(ch < '0' || ch > '9'){
		if(ch == '-') tool = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		ans = (ans << 3) + (ans << 1) + ch - '0';
		ch = getchar();
	}return (ans * tool);
}
bool spfa(){
	memset(dis, Inf, sizeof(dis));	dis[st] = 0;
	memset(in_que, 0, sizeof(in_que));
	queue<int> que;		while(que.size()) que.pop();
	que.push(st);
	getin[st] += 1;
	while(que.size()){
		int cur = que.front();	que.pop();
		in_que[cur] = false;
		if(getin[cur] > n) { return true; }
		for(int i = head[cur]; i; i = e[i].next){
			if(dis[e[i].to] > dis[cur] + e[i].w){
				dis[e[i].to] = dis[cur] + e[i].w;
				if(!in_que[e[i].to]){
					que.push(e[i].to);
					in_que[e[i].to] = true;	
					getin[e[i].to] += 1;
				}
			}
		}
	}
	return false;
}
inline void get_info(){
	memset(head, 0, sizeof(head));	memset(getin, false, sizeof(getin));
	cnte = 0;
	n = read(),m = read();
	while(m--){
		a = read(), b = read(), w = read();
		add_edge(a, b, w);
		if(w >= 0) add_edge(b, a, w);
	}
	return;
}
inline void solve(){
	if(spfa()) puts("YE5");
	else puts("N0");
	return;
}
int main()
{
	t = read();
	while(t--){
		get_info();
		solve();
	}
	
	return 0;
}