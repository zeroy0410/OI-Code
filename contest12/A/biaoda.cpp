#include <cstdio>
const int N=500005,M=2000005,p=998244353;
int T,n,m,e,x,y,a1,tt,hd[N],nx[M],to[M],df[N],v[N],d[N],f[N],g[N];
void ad(int x,int y) {to[++e]=y,nx[e]=hd[x],hd[x]=e;}
bool dfs(int x) {
    df[x]=++tt;
    for(int i=hd[x];i;i=nx[i])
    if(!df[to[i]]) {f[to[i]]=x; if(dfs(to[i])) return 1;}
    else if(df[to[i]]>df[x]) {d[x]-=2; for(int y=to[i];y^x;v[y]=1,d[y]-=2,y=f[y]) if(v[y]) return 1;}
    return 0;
}
int main() {
    scanf("%d",&T),g[0]=g[1]=1;
    for(int i=2;i<N;i++) g[i]=((long long)(i-1)*g[i-2]+g[i-1])%p;
    while(T--) {
        scanf("%d%d",&n,&m),e=0,a1=1;
        for(int i=1;i<=n;i++) hd[i]=df[i]=d[i]=v[i]=0;
        while(m--) scanf("%d%d",&x,&y),ad(x,y),ad(y,x),d[x]++,d[y]++;
        if(dfs(1)) {puts("0"); continue;}
        for(int i=1;i<=n;i++) a1=(long long)a1*g[d[i]]%p;
        printf("%d\n",a1);
    }
    return 0;
}
