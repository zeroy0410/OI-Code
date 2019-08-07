#include<bits/stdc++.h>
#define M 5005
using namespace std;
const int inf=1e9;
int n,m,h[M],tt=1;
int s,t;
struct edge{
    int nxt,to,co,fe;
}G[M*20];
void Add(int a,int b,int c,int f){
    G[++tt]=(edge){h[a],b,c,f};
    h[a]=tt;
}
int dis[M],pre[M],mi[M];
bool vis[M];
queue<int>Q;
bool SPFA(){
    for(int i=1;i<=n;i++)
        vis[i]=0,dis[i]=inf;
    Q.push(s);vis[s]=1;dis[s]=0;mi[s]=inf;
    while(!Q.empty()){
        int x=Q.front();Q.pop();vis[x]=0;
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co,fe=G[i].fe;
            if(dis[u]>dis[x]+fe&&c){
                dis[u]=dis[x]+fe;
                pre[u]=i;
                mi[u]=min(c,mi[x]);
                if(!vis[u]){
                    vis[u]=1;
                    Q.push(u);
                }
            }
        }
    }
    return dis[t]!=inf;
}
int ans=0,ans2=0;
void Update(){
    ans+=mi[t];
    ans2+=dis[t]*mi[t];
    int x=t;
    while(x!=s){
        int i=pre[x];
        G[i].co-=mi[t];
        G[i^1].co+=mi[t];
        x=G[i^1].to;
    }
}
int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1,a,b,c,f;i<=m;i++){
        scanf("%d%d%d%d",&a,&b,&c,&f);
        Add(a,b,c,f);
        Add(b,a,0,-f);
    }
    // puts("!");
    while(SPFA())Update();
    printf("%d %d\n",ans,ans2);
    return 0;
}