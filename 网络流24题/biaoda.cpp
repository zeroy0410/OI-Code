#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1005,M=1e6,INF=1e9;
int read(){
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0'; c=getchar();}
    return x*f;
}
int n,a[N],f[N],g[N],s,t,l;
void dp(){
    for(int i=1;i<=n;i++) g[i]=INF;
    for(int i=1;i<=n;i++){
        int k=upper_bound(g+1,g+1+n,a[i])-g;
        f[i]=k;
        g[k]=a[i];
        l=max(l,f[i]);
    }
}
struct edge{
    int v,ne,c,f;
}e[M<<1];
int cnt,h[N];
inline void ins(int u,int v,int c){
    cnt++;
    e[cnt].v=v;e[cnt].c=c;e[cnt].f=0;e[cnt].ne=h[u];h[u]=cnt;
    cnt++;
    e[cnt].v=u;e[cnt].c=0;e[cnt].f=0;e[cnt].ne=h[v];h[v]=cnt;
}
void build(){
    cnt=0;
    memset(h,0,sizeof(h));
    for(int i=1;i<=n;i++){
        if(f[i]==1) ins(s,i,1);
        ins(i,i+n,1);
        if(f[i]==l) ins(i+n,t,1);
        for(int j=1;j<i;j++) if(a[j]<=a[i]&&f[j]+1==f[i]) ins(j+n,i,1);
    }
}
void build2(){
    cnt=0;
    memset(h,0,sizeof(h));
    for(int i=1;i<=n;i++){
        if(i==1||i==n){
            if(f[i]==1) ins(s,i,INF);
            ins(i,i+n,INF);
            if(f[i]==l) ins(i+n,t,INF);
        }else{
            if(f[i]==1) ins(s,i,1);
            ins(i,i+n,1);
            if(f[i]==l) ins(i+n,t,1);
        }
        for(int j=1;j<i;j++) if(a[j]<=a[i]&&f[j]+1==f[i]) ins(j+n,i,1);
    }
}
int vis[N],d[N],q[N],head=1,tail=1;
bool bfs(){
    memset(vis,0,sizeof(vis));
    memset(d,0,sizeof(d));
    head=tail=1;
    q[tail++]=s;d[s]=0;vis[s]=1;
    while(head!=tail){
        int u=q[head++];
        for(int i=h[u];i;i=e[i].ne){
            int v=e[i].v;
            if(!vis[v]&&e[i].c>e[i].f){
                vis[v]=1;d[v]=d[u]+1;
                q[tail++]=v;
                if(v==t) return 1;
            }
        }
    }
    return 0;
}
int cur[N];
int dfs(int u,int a){
    if(u==t||a==0) return a;
    int flow=0,f;
    for(int &i=cur[u];i;i=e[i].ne){
        int v=e[i].v;
        if(d[v]==d[u]+1&&(f=dfs(v,min(a,e[i].c-e[i].f)))>0){
            flow+=f;
            e[i].f+=f;
            e[((i-1)^1)+1].f-=f;
            a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
int dinic(){
    int flow=0;
    while(bfs()){//cout<<"p";
        for(int i=s;i<=t;i++) cur[i]=h[i];
        flow+=dfs(s,INF);
    }
    return flow;
}
int main(){
    n=read();s=1;t=n+n+1;
    for(int i=1;i<=n;i++) a[i]=read();
    dp();printf("%d\n",l);
    if(l==1) {printf("%d\n%d",n,n);return 0;}
    build();
    printf("%d\n",dinic());
    build2();
    printf("%d",dinic());
}