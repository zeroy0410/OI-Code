#include<bits/stdc++.h>
#define M 3000005
#define LL long long
using namespace std;
inline void Rd(int &x){
    char c;x=0;
    while((c=getchar())<48);
    do x=(x<<3)+(x<<1)+(c^48);
    while((c=getchar())>47);
}
const LL mod=998244353;
int n;
struct edge{
    int to,fr;
}E[M<<1];
int lst[M],tote;
void addedge(int a,int b){
    E[++tote]=(edge){b,lst[a]};
    lst[a]=tote;
}
LL fac[M],inv[M];
LL Pow(LL x,int y){
    LL res=1;
    for(;y;y>>=1,x=x*x%mod)if(y&1)res=res*x%mod;
    return res;
}
void init(){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=Pow(fac[n],mod-2);
    for(int i=n;i;i--)inv[i-1]=inv[i]*i%mod;
}
LL Com(int a,int b){
    return fac[a]*inv[a-b]%mod*inv[b]%mod;
}
int sz[M],mxs[M];
void dfs(int v,int f){
    sz[v]=1;int mx=0;mxs[v]=0;
    for(int i=lst[v];i;i=E[i].fr){
        int u=E[i].to;
        if(u==f)continue;
        dfs(u,v);
        sz[v]+=sz[u];
        if(sz[u]>mx)mx=sz[u],mxs[v]=u;
    }
    if(n-sz[v]>mx)mxs[v]=f;
}
LL dp[M];
int redfs(int v,int f){
    sz[v]=0;dp[v]=1;int sonc=0,ed=v;
    for(int i=lst[v];i;i=E[i].fr){
        int u=E[i].to;
        if(u==f)continue;
        sonc++;
        ed=redfs(u,v);
        dp[v]=dp[v]*dp[u]%mod;
        sz[v]+=sz[u];
        dp[v]=dp[v]*Com(sz[v],sz[u])%mod;
    }
    sz[v]++;
    if(sonc>1)ed=v;
    return ed;
}
int main(){
    Rd(n);
    for(int i=1,a,b;i<n;i++){
        Rd(a),Rd(b);
        addedge(a,b);
        addedge(b,a);
    }
    init();
    dfs(1,0);
    int rt=0,so=0;
    for(int i=1;!rt&&i<=n;i++)if((n+1)/2==sz[i])rt=i;
    if(!rt){
        for(int i=2;i<=n/2;i++)putchar('0'),putchar('\n');
    }else{
        so=mxs[rt];
        int sa=redfs(rt,so),sb=redfs(so,rt);
        int mi=max(2,max(sz[sa],sz[sb]));
        LL ans=dp[sa]*dp[sb]*2%mod;
        for(int i=2;i<mi;i++)putchar('0'),putchar('\n');
        for(int i=mi;i<=n/2;i++)printf("%lld\n",ans);
    }
    return 0;
}
