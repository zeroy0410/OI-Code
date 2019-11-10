#include<bits/stdc++.h>
#define M 90
#define ll long long
using namespace std;
int n,m,s,tot,mk[15][15],sz[1<<13],Mx,mx[1<<13];
ll dp[13][1<<13],cnt[13][1<<13];
ll dfs(int x,int u){
    if(u==(1<<x)){
        cnt[x][u]=1;
        return 0;
    }
    if(dp[x][u]!=-1)return dp[x][u];
    ll res=(1ll<<60);
    int t=u^(1<<x)^mx[u^(1<<x)];
    for(int i=t;i>=0;i=(i-1)&t){
        i|=mx[u^(1<<x)];
        for(int j=0;j<n;j++){
            if((i&(1<<j))==0)continue;
            if(mk[x][j]==2e9)continue;
            ll now=0;//将j作为i的儿子节点
            now=dfs(x,u^i)+dfs(j,i)+s*((u^i)!=(1<<x)||(u==Mx))+1ll*sz[i]*mk[x][j];
            if(now<res)res=now,cnt[x][u]=cnt[x][u^i]*cnt[j][i];
            else if(now==res)cnt[x][u]+=cnt[x][u^i]*cnt[j][i];
        }
        i^=mx[u^(1<<x)];
        if(i==0)break;
    }
    return dp[x][u]=res;
}
int main() {
    scanf("%d%d%d",&n,&m,&s);
    Mx=(1<<n)-1;
    memset(dp,-1,sizeof(dp));
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<(1<<n);i++)sz[i]=sz[i>>1]+(i&1);
    for(int i=0;i<(1<<n);i++)for(int j=0;j<n;j++)if(i&(1<<j))mx[i]=(1<<j);
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)mk[i][j]=2e9;
    for(int i=1;i<=m;i++){
        int l,r,v;
        scanf("%d%d%d",&l,&r,&v);
        l--,r--;
        mk[l][r]=mk[r][l]=min(mk[l][r],v);
    }
    ll ans=2e18,tot=0;
    for(int i=0;i<n;i++){
        ll res=dfs(i,Mx);
        if(res<ans)ans=res,tot=cnt[i][Mx];
        else if(res==ans)tot+=cnt[i][Mx];
    }
    printf("%lld %lld\n",ans+s,tot);
    return 0;
}
