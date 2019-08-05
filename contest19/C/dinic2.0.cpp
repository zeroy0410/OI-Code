#include<bits/stdc++.h>
#define M 10005
using namespace std;
int n,m,s,t,h[M],tt=1;
int ans=0;
const int inf=1e9;
struct edge{
    int nxt,to,co;
}G[M*30];
void Add(int a,int b,int c){
    G[++tt]=(edge){h[a],b,c};
    h[a]=tt;
}
queue<int>Q;
bool vis[M];
int dep[M],cur[M];
bool bfs(){
    for(int i=1;i<=n;i++){
        vis[i]=0;dep[i]=inf;
        cur[i]=h[i];
    }
    dep[s]=0;Q.push(s);vis[s]=1;
    while(!Q.empty()){
        int e=Q.front();Q.pop();
        for(int i=h[e];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co;
            if(vis[u]||!c)continue;
            dep[u]=dep[e]+1;
            vis[u]=1;
            Q.push(u);
        }
    }
    if(dep[t]!=inf)return 1;
    return 0;
}
int dfs(int x,int mi){
    int rlow=0;
    if(x==t){
        ans+=mi;
        return mi;
    }
    int used=0;
    for(int &i=cur[x];i;i=G[i].nxt){
        int u=G[i].to,c=G[i].co;
        if(dep[u]!=dep[x]+1||!c)continue;
        if(rlow=dfs(u,min(mi-used,c))){
            used+=rlow;
            G[i].co-=rlow;
            G[i^1].co+=rlow;
            if(used==mi)break;
        }
    }
    return used;
}
void Dinic(){
    while(bfs()){
        dfs(s,inf);
    }
}
int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1,a,b,c;i<=m;i++){
        scanf("%d%d%d",&a,&b,&c);
        Add(a,b,c);
        Add(b,a,0);
    }
    Dinic();
    printf("%d",ans);
    return 0;
}