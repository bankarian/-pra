#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
#define ll long long 
#define Inf 0x3f3f3f3f
inline int read(){
	char ch = getchar();
	int ans = 0, tool = 1;
	while(ch < '0' || ch > '9'){
		if(ch == '-') tool = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		ans = (ans << 3) + (ans << 1) + ch -'0';
		ch = getchar();
	}return (ans * tool);
}

int main(){

	return 0;
}