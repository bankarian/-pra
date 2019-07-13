//数据量不大-->floyd。
//每当看到节点数<300时都可以考虑floyd
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define ll long long 
#define Inf 0x3f3f3f3f
const int maxv = 200 + 2;
int pt[maxv], n, m, a, b, c;
ll table[maxv][maxv];
int Q, x, y, t, k;

bool floyd(const int& st, const int& en, const int& tt){
	if(pt[st] > tt || pt[en] > tt) return false;
	while(pt[k] <= tt && k < n){
		for(int u=0; u<n; ++u){
			for(int v=0; v<n; ++v){
				if(u == v || u ==k || v == k) continue;
				// if(pt[u] > tt || pt[v] > tt) continue;//想想为什么这句不要？
				table[u][v] = min(table[u][v], table[u][k] + table[k][v]);
			}
		}
		k += 1;
	}
	return table[st][en] != Inf;
}

inline int read(){
	char ch = getchar();
	int ans = 0, tool = 1;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9'){
		ans = (ans << 3) + (ans << 1) + ch - '0';
		ch = getchar();
	}return (ans * tool);
}
int main()
{
	n = read(), m = read();
	for(int i=0; i<n; ++i)	//table只需要初始化一次，因为之后的t都是增加的
		for(int j=0; j<n; ++j)
			table[i][j] = Inf;
	for(int i=0; i<n; ++i)
		pt[i] = read();
	while(m--){
		a = read(), b = read(), c = read();
		table[a][b] = table[b][a] = c;
	}
	Q = read();
	while(Q--){
		x = read(), y = read(), t = read();
		if(floyd(x, y, t)){
			printf("%lld\n", table[x][y]);
		}
		else puts("-1");
	}
	return 0;
}