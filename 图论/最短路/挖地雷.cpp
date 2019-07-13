//这题比较巧秒的地方在于用一个数组记录了每个点的前驱点，方便记录经过的节点
//类似的还可以用这种方式记录与前驱相连接的边的编号
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxv = 20 + 2, maxe = (maxv - 1) * maxv;
struct Edge{
	int to, next;
}e[maxe * 2];
int head[maxv], cnte, pw[maxv], dis[maxv], pre[maxv], lis[maxv];
bool in_que[maxv];
int n, a, b, maxlen = -1, cntv;

inline int read(){
	int ans = 0, tool = 1;
	char ch = getchar();
	while(ch<'0' || ch>'9'){
		if(ch == '-') tool = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <='9'){
		ans = (ans << 3) + (ans << 1) + ch -'0';
		ch = getchar();
	}return (ans * tool);
}
inline void add_edge(const int& from, const int& to){
	++cnte;
	e[cnte].to = to;	e[cnte].next = head[from];
	head[from] = cnte;
	return;
}
//找最长路,spfa其实就是求单源路径版的bfs
inline void spfa(const int &st){
	memset(dis, 0, sizeof(dis));
	memset(pre, 0, sizeof(pre));
	dis[st] = pw[st];
	queue<int> que;		while(que.size()) que.pop();
	que.push(st);
	in_que[st] = true;

	while(que.size()){
		int cur = que.front();
		que.pop();	in_que[cur] = false;
		for(int i = head[cur]; i; i = e[i].next){
			if(dis[e[i].to] < dis[cur] + pw[e[i].to]){//为何有==？
				dis[e[i].to] = dis[cur] + pw[e[i].to];
				pre[e[i].to] = cur;	//记录前驱节点！
				if(!in_que[e[i].to]){
					que.push(e[i].to);
					in_que[e[i].to] = true;
				}
			}
			else continue;
		}
	}
	return;
}
inline void get_info(){
	n = read();
	for(int i = 1; i <= n; ++i)
		pw[i] = read();
	for(int i=1; i < n; ++i){
		for(int j = i+1; j <= n; ++j){
			a = read();	
			if(a){
				add_edge(i, j);
				// add_edge(j, i);//无向图哪来的最长路。。。
			}
		}
	}
	return;
}
int main()
{
	get_info();
	for(int i=1; i<=n; ++i){
		spfa(i);
		for(int j = 1; j<=n; ++j){
			if(maxlen < dis[j]){
				maxlen = dis[j];
				cntv = 0;
				int tmp = j;
				lis[cntv++] = j;
				while(pre[tmp]){
					lis[cntv++] = pre[tmp];
					tmp = pre[tmp];
				}
			}
		}
	}
	printf("%d", lis[cntv-1]);	//注意节点是由后往前存储，所以要反向输出
	for(int i=cntv-2; i>=0; --i)
		printf(" %d", lis[i]);
	puts("");
	printf("%d\n", maxlen);
	return 0;
}