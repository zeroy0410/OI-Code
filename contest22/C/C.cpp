#include<bits/stdc++.h>
#define N 705
#define M 100005
#define LL long long
using namespace std;
const double eps=1e-10;
const double inf=1e9;
int n,m,n1,m1,h[N],h2[N],tt,tt2=1;
struct edge{
    int nxt,to,t,s;
}G[M];
struct Edge{
    int nxt,to;
    double t;
}H[M*10];
void Add(int a,int b,int t,int s){
    G[++tt]=(edge){h[a],b,t,s};
    h[a]=tt;
}
void Add2(int a,int b,double c){
    H[++tt2]=(Edge){h2[a],b,c};
    h2[a]=tt2;
}
bool vis[N];
int dep[N],cur[N],s,t;
double ans=0.0;
queue<int>Q;
double dis[M],f[M];
bool SPFA(int ed,double mid){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)dis[i]=inf;dis[n]=0.0;
    while(!Q.empty())Q.pop();Q.push(n);vis[n]=1;
    while(!Q.empty()){
        int x=Q.front();Q.pop();vis[x]=0;
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to;
            double c=(double)(G[i].t)-(double)(G[i].s)*mid;
            if(dis[x]+c<dis[u]){
                dis[u]=dis[x]+c;
                if(dis[ed]<=eps)return 1;
                if(!vis[u]){
                    vis[u]=1;
                    Q.push(u);
                }
            }
        }
    }
    return 0;
}
bool bfs(){
    for(int i=s;i<=t;i++){
        dep[i]=-1;cur[i]=h2[i];
    }
    while(!Q.empty())Q.pop();
    dep[s]=0;Q.push(s);
    while(!Q.empty()){
        int x=Q.front();Q.pop();
        for(int i=h2[x];i;i=H[i].nxt){
            int u=H[i].to;double c=H[i].t;
            if(dep[u]!=-1||!c)continue;
            dep[u]=dep[x]+1;
            if(u==t)return 1;
            Q.push(u);
        }
    }
    return 0;
}
double dfs(int x,double mi){
    double rlow=0,used=0;
    if(x==t||!mi)return mi;
    for(int &i=cur[x];i;i=H[i].nxt){
        int u=H[i].to;double c=H[i].t;
        if(dep[u]!=dep[x]+1||!c)continue;
        if(rlow=dfs(u,min(mi-used,c))){
            used+=rlow;
            H[i].t-=rlow;
            H[i^1].t+=rlow;
            if(used==mi)break;
        }
    }
    return used;
}
void Dinic(){
    while(bfs()){
        ans+=dfs(s,inf);
    }
}
int main(){
    // freopen("secret.in","r",stdin);
    // freopen("secret.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1,a,b,t,s;i<=m;i++){
        scanf("%d%d%d%d",&a,&b,&t,&s);
        Add(a,b,t,s);
    }
    scanf("%d%d",&m1,&n1);
    for(int i=1;i<=n1;i++){
        double l=0,r=10.0;
        while(l+eps<=r){
            double mid=(l+r)/2.0;
            if(SPFA(i,mid))r=mid-eps;
            else l=mid+eps;
        }
        if(dis[i]==inf)f[i]=inf;
        else f[i]=r+eps;
    }
    s=0;t=n1+1;
    for(int i=1,a,b;i<=m1;i++){
        scanf("%d%d",&a,&b);
        Add2(a,b,inf);Add2(b,a,0);
        if(f[a]==inf&&f[b]==inf){puts("-1");return 0;}
    }
    for(int i=1;i<=n1;i++)
        if(i&1){Add2(s,i,f[i]);Add2(i,s,0);}
        else {Add2(i,t,f[i]);Add2(t,i,0);}
    Dinic();
    printf("%.1lf\n",ans);
    return 0;
}