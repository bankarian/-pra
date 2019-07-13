#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define Inf 0x3f3f3f3f
const int maxp = 1e3 + 2, maxe = 1e5 + 2;
struct Astar
{
	long long f, g;
	int index;
	bool operator < (const Astar& b) const{	//返回true是b优先，注意
		if(this->f != b.f) return this->f > b.f;
		return this->g > b.g;
	}
};
//1为正图， 2为反图
struct Edge
{
	int to, w;
	int next;
}edge1[maxe], edge2[maxe];
int head1[maxp], head2[maxp], cnte, dis[maxp];
int n, m, s, t, k;
bool in_que[maxp];
long long ans;

//同时建立正图，反图.建反图时稍微注意下，别晕了~
inline void add_edge(const int& from, const int& to, const int& w)
{
	cnte += 1;
	edge1[cnte].to = to, edge1[cnte].w = w;
	edge1[cnte].next = head1[from];
	head1[from] = cnte;

	edge2[cnte].to = from, edge2[cnte].w = w;
	edge2[cnte].next = head2[to];
	head2[to] = cnte;
	return;
}
//从终点为起始，单源最短路预处理得到dis[]预估代价
void spfa(int st){
	memset(dis, Inf, sizeof(dis));
	dis[st] = 0;
	queue<int> que;
	que.push(st);	in_que[st] = true;
	
	while(que.size()){	
		int cur = que.front();
		que.pop(); 	in_que[cur] = false;
		for(int i=head2[cur]; i; i = edge2[i].next){	
			if(dis[edge2[i].to] > dis[cur] + edge2[i].w)
			{	
				dis[edge2[i].to] = dis[cur] + edge2[i].w;
				if(!in_que[edge2[i].to]){
					que.push(edge2[i].to);
					in_que[edge2[i].to] = true;
				}
			}
		}
	}
	return;
}

void AA()
{
	if(dis[s] == Inf){ ans = -1; 	return; } //不能到达
	priority_queue<Astar> pq;
	Astar tmp = {dis[s] + 0, 0, s};
	pq.push(tmp);
	int times = 0;
	while(pq.size()){
		tmp = pq.top();
		pq.pop();
		if(tmp.index == t) times += 1;
		if(times == k){
			ans = tmp.g;	return;
		}

		for(int i = head1[tmp.index]; i; i = edge1[i].next){
			pq.push({dis[edge1[i].to] + tmp.g + edge1[i].w, tmp.g + edge1[i].w, edge1[i].to});
		}
	}
	ans = -1;
	return;
}
int main()
{
	ios::sync_with_stdio(false);	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	int a=0, b=0, c=0;
	while(m--){
		cin >> a >> b >> c;
		add_edge(a, b, c);
	}
	cin >> s >> t >> k;
	spfa(t);
	AA();
	cout << ans << endl;
	return 0;
}