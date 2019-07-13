//题目http://acm.hdu.edu.cn/showproblem.php?pid=1232 
//畅通工程 
#include <iostream>
#include <cstdio> 
using namespace std;
#define maxn 1005
int N=0,M=0;
int root[maxn]; //节点
int Len[maxn]; //树的高度 
int FindRoot(int x)
{	 
	while(root[x]^x){
		root[x] = root[root[x]]; //状态压缩 
		x = root[x]; //若有爷爷节点，直接找爷爷 
	}
	return x; //找到了树根 
}
//FindRoot(x)== rootx FindRoot(y)==rooty
inline void Unite(const int &x,const int &y)
{
	root[FindRoot(x)] = root[FindRoot(y)];
}
//由于之前已经进行过路径压缩 可以直接使用Unite1 
//void Unite(int x,int y)
//{
//	int rootx = FindRoot(x); 
//	int rooty = FindRoot(y);
//	if(rootx == rooty) return; //已经连通
//	if(Len[rootx] > Len[rooty]){
//		root[rooty] = rootx; //小树连到大树 
//	}else{
//		if(Len[rootx] == Len[rooty]){
//			Len[rooty] += 1; //相同的话，相连后树增高； 
//		}
//		root[rootx] = rooty;
//	} 
//}
int main()
{
	int a=0,b=0;
	while(~scanf("%d",&N) && N){//一用到循环就要注意重复使用的数据初始化 
		int ans = 0; 
		scanf("%d",&M);
		for(int i=1;i<=N;++i){
			Len[i] = 1;//每个点初始为一棵高为1的树 
			root[i] = i;
		} 
		for(int i=0;i<M;++i){
			scanf("%d%d",&a,&b); // 
			Unite(a,b); //将ab连通 
		}
		for(int i=1;i<=N;++i){
			if(root[i] == i)
				ans++; //找出根节点的总数 
		}
		printf("%d\n",ans-1); //ans个点,ans-1条边 
	}
	return 0;
}
//int FindRoot_2(int x){
//	//还可以用递归的办法，更直观，但还是循环更高效
//	if(root[x]^x) return FindRoot(root[x]);
//	return x; 
//} 


//	
//}
