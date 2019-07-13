//
//  main.cpp
//  poj3255
//
//  Created by Candy on 9/14/16.
//  Copyright 漏 2016 Candy. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int N=1005,M=10005,INF=1e9+5;
inline int read(){
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x;
}
int t,n,m,u,v,w,s,f;
struct edge{
    int v,w,ne;
}e[M];
int h[N],ecnt=0;
inline void ins(int u,int v,int w){
    ecnt++;
    e[ecnt].v=v;e[ecnt].w=w;e[ecnt].ne=h[u];h[u]=ecnt;
}
int d[N][2],vis[N][2],cnt[N][2];
struct hn{
    int u,d,p;
    hn(int a=0,int b=0,int c=0):u(a),d(b),p(c){}
    bool operator < (const hn &rhs)const{return d>rhs.d;}
};
void dijkstra(int s){
    priority_queue<hn> q;
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;i++) {d[i][0]=d[i][1]=INF;}
    q.push(hn(s,0,0));
    d[s][0]=0; cnt[s][0]=1;
    while(!q.empty()){
        hn now=q.top();q.pop();
        int u=now.u,p=now.p; 
        if(vis[u][p]) continue;
        vis[u][p]=1;
        for(int i=h[u];i;i=e[i].ne){
            int v=e[i].v,w=e[i].w;
            if(d[v][0]>d[u][p]+w){
                d[v][1]=d[v][0];
                cnt[v][1]=cnt[v][0];
                d[v][0]=d[u][p]+w;
                cnt[v][0]=cnt[u][p];
                
                q.push(hn(v,d[v][0],0));
                q.push(hn(v,d[v][1],1));
            }else 
            if(d[v][0]==d[u][p]+w){
                cnt[v][0]+=cnt[u][p];
            }else 
            if(d[v][1]>d[u][p]+w){
                d[v][1]=d[u][p]+w;
                cnt[v][1]=cnt[u][p];
                 q.push(hn(v,d[v][1],1));
            }else 
            if(d[v][1]==d[u][p]+w)
                cnt[v][1]+=cnt[u][p];
        }        
    }
}
int main(int argc, const char * argv[]) {
t=read();
while(t--){
    memset(h,0,sizeof(h)); ecnt=0;
    n=read();m=read();
    for(int i=1;i<=m;i++){u=read();v=read();w=read();ins(u,v,w);}
    s=read();f=read();
    dijkstra(s);
    if(d[f][1]==d[f][0]+1) cnt[f][0]+=cnt[f][1];
    printf("%d\n",cnt[f][0]);
}
    return 0;
}