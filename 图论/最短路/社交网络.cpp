#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define Inf 0x3f3f3f3f
#define ll long long
const int maxv = 100 + 4, maxe = 4500 + 4;
int table[maxv][maxv];
ll edge[maxv][maxv];
double Imp[maxv];
int n, m, u, v, w;
//注意floyd是所有点间的遍历故双向性已经考虑在内
//每次单向处理即可
void floyd(){
	for(int k=1; k<=n; ++k){
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=n; ++j){
				if(table[i][j] > table[i][k] + table[k][j]){//重新更新
					table[i][j] = table[i][k] + table[k][j];
					edge[i][j] = edge[i][k] * edge[k][j];
				}
				else if(table[i][j] == table[i][k] + table[k][j]){
					//不需要更新，因为中转节点是变化的，所以必然是新的最短路，累加即可
					//不用担心有重复的计算。乘法原理
					edge[i][j] += edge[i][k] * edge[k][j];
				}
			}
		}
	}
	return;
}
void solve(){
	for(int k=1; k<=n; ++k){
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=n; ++j){
                if(i==j || j==k || i==j) continue;
                if(table[i][j] == table[i][k] + table[k][j])
                    Imp[k] += ((double)edge[i][k] * (double)edge[k][j] / (double)edge[i][j]);
			}
		}
		printf("%.3f\n", Imp[k]);
	}
	return;
}
inline int read(){
	char ch = getchar();
	int ans = 0;
	while(ch < '0' || ch >'9') ch = getchar();
	while(ch >= '0' && ch <= '9'){
		ans = (ans << 3) + (ans << 1) + ch - '0';
		ch = getchar();
	}return ans;
}
void inline ini()
{
	memset(table, Inf, sizeof(table));
	n = read(), m = read();
	while(m--){
		u = read(), v = read(), w = read();
		table[u][v] = table[v][u] = w;
		edge[u][v] = edge[v][u] = 1;
	}
	return;
}
int main()
{
	ini();
	floyd();
	solve();
	return 0;
}
