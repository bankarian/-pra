#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define ll long long
#define Inf 0x3f3f3f3f
const int maxn = 50000 + 5;
struct Edge{
	int to, w;
	int next;
	Edge(int a=0, int b=0, int c=0):to(a), w(b), next(c){}
}e[maxn * 2];
int st, cnte, head[maxn], pw[maxn];
bool in_que[maxn];
ll ans, dis[maxn];
int nv, ne, u, v, w, t;

inline void ini()
{
	memset(in_que, false, sizeof(in_que));
	memset(dis, Inf, sizeof(dis));
	memset(head, 0, sizeof(head));
	cnte = ans = 0;
	return;
}
inline void add_edge(const int& from, const int& to, const int& w)
{
	++cnte;
	e[cnte].to = to, e[cnte].w = w;
	e[cnte].next = head[from];
	head[from] = cnte;
	return;
}
//单源最短路
void spfa(const int s){
	queue<int> que;	while(que.size()) que.pop();
	que.push(s);
	in_que[s] = true;
	dis[s] = 0;

	while(que.size()){
		int cur = que.front();
		que.pop(); 	in_que[cur] = false;
		for(int i = head[cur]; i; i = e[i].next){
			if(dis[e[i].to] > dis[cur] + e[i].w){
				dis[e[i].to] = dis[cur] + e[i].w;
				if(!in_que[e[i].to]){
					que.push(e[i].to);
					in_que[e[i].to] = true;
				}
			}
		}
	}
	return;
}
inline bool operator < (const Edge& a, const Edge& b){
	return a.w > b.w;
}

inline int read(){
	char ch = getchar();
	int ans = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9'){
		ans = (ans << 3) + (ans << 1) + ch - '0';
		ch = getchar();
	}
	return ans;
}
int main()
{
	t = read();
	while(t--){
		ini();
		nv = read(), ne = read();
		for(int i = 1; i <= nv; ++i)
			pw[i] = read();
		for(int i = 1; i <= ne; ++i){
			u = read(), v = read(), w = read();
			add_edge(u, v, w);
			add_edge(v, u, w);
		}
		if(nv == 0 || ne == 0 || nv == 1){
			puts("0");	continue;
		}
		spfa(1);
		bool have_ans = true;
		for(int i = 1; i <= nv; ++i){
			if(dis[i] == Inf){
				have_ans = false;
				printf("No Answer\n");
				break;
			}
			ans += dis[i] * pw[i];
		}
		if(have_ans) printf("%lld\n", ans);
	}
	return 0;
}