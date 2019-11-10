#include<bits/stdc++.h>
#define M 2005
#define LL long long
using namespace std;
const LL inf=1e18;
int n,m,t1,m1,t2,m2,h[M*M],tt=1,s,t;
struct edge{
    int nxt,to;
    LL co,fe;
}G[M*M*15];
void Add(int a,int b,LL c,LL d){
    G[++tt]=(edge){h[a],b,c,d};
    h[a]=tt;
    G[++tt]=(edge){h[b],a,0,-d};
    h[b]=tt;
}
int pre[M*M];
LL mi[M*M];
LL dis[M];
bool vis[M*M];
queue<int>Q;
bool SPFA(){
    for(int i=s;i<=t;i++)
        vis[i]=0,dis[i]=inf;
    Q.push(s);vis[s]=1;dis[s]=0;mi[s]=inf;
    while(!Q.empty()){
        int x=Q.front();Q.pop();vis[x]=0;
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to;LL c=G[i].co,fe=G[i].fe;
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
LL ans=0,ans2=0;
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
    scanf("%d",&n);
    scanf("%d%d%d%d%d",&m,&t1,&m1,&t2,&m2);
    s=0,t=n*2+1;
    for(int i=1,x;i<=n;i++){
        scanf("%d",&x);
        Add(s,i,x,0);
        Add(i+n,t,x,0);
    }
    for(int i=1;i<=n;i++){
        if(i+1<=n)Add(i,i+1,inf,0);
        if(i+t1<=n)Add(i,i+n+t1,inf,m1);
        if(i+t2<=n)Add(i,i+n+t2,inf,m2);
        Add(s,i+n,inf,m);
    }
    while(SPFA())Update();
    printf("%lld\n",ans2);
    return 0;
}