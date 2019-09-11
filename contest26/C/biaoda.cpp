#include<bits/stdc++.h>
#define LL long long
const LL maxn=5e4+9,mod=10007,maxm=209;
struct node{
    LL to,nxt;
}dis[maxn<<1];
LL n,num,K;
LL head[maxn],dp1[maxn][maxm],dp2[maxn][maxm],strl[maxm][maxm],tmp[maxm],fac[maxm];
inline void Add(LL u,LL v){
    dis[++num]=(node){v,head[u]}; head[u]=num;
}
void Dfs1(LL u,LL f){
    dp1[u][0]=1;
    for(LL i=head[u];i;i=dis[i].nxt){
        LL v(dis[i].to);
        if(v==f) continue;
        Dfs1(v,u);
        for(LL j=1;j<=K;++j) dp1[u][j]=(dp1[u][j]+dp1[v][j]+dp1[v][j-1])%mod;
        dp1[u][0]=(dp1[u][0]+dp1[v][0])%mod;
    }
}
void Dfs2(LL u,LL f){
    for(LL i=0;i<=K;++i) dp2[u][i]=dp1[u][i];
    if(f){
        for(LL i=1;i<=K;++i) tmp[i]=(dp2[f][i]-dp1[u][i]+mod-dp1[u][i-1]+mod)%mod;
        tmp[0]=(dp2[f][0]-dp1[u][0]+mod)%mod;
        for(LL i=1;i<=K;++i) dp2[u][i]=(dp2[u][i]+tmp[i]+tmp[i-1])%mod;
        dp2[u][0]=(dp2[u][0]+tmp[0])%mod;
    }
    for(LL i=head[u];i;i=dis[i].nxt){
        LL v(dis[i].to);
        if(v==f) continue;
        Dfs2(v,u);
    }
}
int main(){
    scanf("%lld%lld",&n,&K);
    strl[0][0]=strl[1][1]=1;
    for(LL i=2;i<=K;++i)
        for(LL j=1;j<=i;++j)
            strl[i][j]=(strl[i-1][j-1]+j*strl[i-1][j])%mod;
    fac[0]=fac[1]=1;
    for(LL i=2;i<=K;++i) fac[i]=fac[i-1]*i%mod;
    for(LL i=1;i<n;++i){
        scanf("%lld%lld",&u,&v);
        Add(u,v); Add(v,u);
    }
    Dfs1(1,0); Dfs2(1,0);
    for(LL i=1;i<=n;++i){
        LL ret(0);
        for(LL j=0;j<=K;++j) ret=(ret+1ll*strl[K][j]*fac[j]*dp2[i][j])%mod;
        printf("%d\n",ret);
    }
    return 0;
}