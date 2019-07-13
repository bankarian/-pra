#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define Inf 0x3f3f3f3f
#define ll long long
const int maxn = 250 + 4;
struct Node{
	int w, id;
}node[maxn];
ll table[maxn][maxn], dis[maxn][maxn];
int n, m, k, u, v, w, st, en;
int newid[maxn];
inline int read(){
	char ch = getchar();
	int ans = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9'){
		ans = (ans << 3) + (ans << 1) + ch - '0';
		ch =getchar();
	}return ans;
}
inline bool comp(const Node& a, const Node& b){
	return a.w < b.w;
}

inline void floyd(){
	for(int k=1; k<=n; ++k){
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=n; ++j){
				if(i == j || i == k || j == k) continue;
				table[i][j] = min(table[i][j], table[i][k] + table[k][j]);
				dis[i][j] = min(dis[i][j], table[i][j] + max(node[k].w, max(node[i].w, node[j].w)));
			}
		}
	}
	return;
}
//涉及到最短路和最短路上的最大节点，用两个数组分别存储
//由于floyd中间节点由前往后遍历，所以我们把权值越大的点越往后遍历
//使得最终遍历到k==n时，保证如果选取中间节点选取的节点是所有中间节点中权值最大的
int main()
{
	memset(table, Inf, sizeof(table));
	memset(dis, Inf, sizeof(dis));
	n = read(), m = read(), k = read();
	for(int i=1; i<=n; ++i) 
		{node[i].w = read(), node[i].id = i, table[i][i] = 0;}
	sort(node+1, node+n+1, comp); //节点按权值升序
	for(int i=1; i<=n; ++i)
		newid[node[i].id] = i; 
		//相当于把我想要优先遍历的序号排在前边
		//这样在floyd中的遍历就更加方便注意之后的存图位置也要用newid数组

	for(int i=1; i<=m; ++i){
		u = read(), v = read(), w = read();
		table[newid[u]][newid[v]] = table[newid[v]][newid[u]] = min(table[newid[u]][newid[v]], (ll)w);
		//为方便之后的floyd访问，用newid【】数组来获取新的顺序编号
		//转换之后，权值较小的节点会被优先遍历到
		//注意可能会有重边，所以要有一个min()判断一下
	}

	floyd();
	while(k--){
		st = read(), en = read();
		printf("%lld\n", dis[newid[st]][newid[en]]);
	}
	return 0;
}