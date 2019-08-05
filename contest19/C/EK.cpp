#include<bits/stdc++.h>
#define M 10005
using namespace std;
int n,m,s,t,h[M],tt=1;
struct edge{
    int nxt,to,co;
}G[M*50];
void Add(int a,int b,int c){
    // G[++tt]=(edge){h[a],b,c};
    G[++tt].to=b;
    G[tt].co=c;
    G[tt].nxt=h[a];
    h[a]=tt;
}
bool vis[M];
int pre[M],dis[M];
queue<int>Q;
bool bfs(){
    memset(vis,0,sizeof(vis));
    while(!Q.empty())Q.pop();
    vis[s]=1;dis[s]=1e9;
    Q.push(s);
    while(!Q.empty()){
        int e=Q.front();Q.pop();
        for(int i=h[e];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co;
            if(vis[u]||!c)continue;
            pre[u]=i;
            dis[u]=min(dis[e],c);
            if(u==t)return 1;
            Q.push(u);vis[u]=1;
        }
    }
    return 0;
}
int ans=0;
void update(){
    ans+=dis[t];
    int x=t;
    while(x!=s){
        int i=pre[x];
        G[i].co-=dis[t];
        G[i^1].co+=dis[t];
        x=G[i^1].to;
    }
}
int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1,x,y,c;i<=m;i++){
        scanf("%d%d%d",&x,&y,&c);
        Add(x,y,c);
        Add(y,x,0);
    }
    while(bfs())update();
    printf("%d",ans);
    return 0;
}