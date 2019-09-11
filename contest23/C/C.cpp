#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
bool mm1;
const int mod=1e9+7;
int n,h[M],tt,cnt[M],rt;
LL gcd(LL a,LL b){return b==0?a:gcd(b,a%b);}
LL pw[M],dp[M][2],ans=1,res;
bool mark[M],vis[M],usd[M];
vector<int>son[M],G[M];
vector<int>wk,ut;
struct edge{int a,b;}E[M];
void tarjan(int x,int f){
    vis[x]=1;wk.push_back(x);
    for(int i=0;i<G[x].size();i++){
        int u=G[x][i];
        if(u==f)continue;
        if(vis[u]){
            E[++tt]=(edge){u,x};
            mark[u]=mark[x]=1;
        }
        else {
            tarjan(u,x);
            son[x].push_back(u);
        }
    }
}
void dfs(int x,int f){
    dp[x][0]=1;dp[x][1]=pw[cnt[x]]-1;
    if(mark[x])dp[x][!usd[x]]=0;
    for(int i=0;i<son[x].size();i++){
        int u=son[x][i];
        dfs(u,x);
        dp[x][0]=dp[x][0]*(dp[u][0]+dp[u][1])%mod;
        dp[x][1]=dp[x][1]*dp[u][0]%mod;
    }
}
void dfs_ans(int x,int rt){
    if(x==ut.size()){
        for(int i=1;i<=tt;i++)
            if(usd[E[i].a]&&usd[E[i].b])return;
        dfs(rt,0);
        res=(res+dp[rt][0]+dp[rt][1])%mod;
        return;
    }
    usd[ut[x]]=0;dfs_ans(x+1,rt);
    usd[ut[x]]=1;dfs_ans(x+1,rt);
}
void Init(){
    for(LL i=1;i<=1000000;i++){
        for(LL j=1+(i&1);j*i*2<=1000000&&j<i;j+=2){
            if(gcd(i,j)==1){
                LL a=i*i-j*j;
                LL b=2*i*j;
                if(a>1000000)continue;
                if(!cnt[a]||!cnt[b])continue;
                G[a].push_back(b);
                G[b].push_back(a);
            }
        }
    }
}
int B[M],bc=0;
bool mm2;
int main(){
    // printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
    freopen("gougu.in","r",stdin);
    freopen("gougu.out","w",stdout);
    scanf("%d",&n);
    pw[0]=1;
    for(int i=1,x;i<=n;i++){scanf("%d",&x);if(!mark[x]){mark[x]=1;B[++bc]=x;}cnt[x]++;pw[i]=pw[i-1]*2%mod;}
    Init();
    memset(mark,0,sizeof(mark));
    for(int i=1;i<=bc;i++){
        if(!vis[B[i]]){
            rt=B[i];wk.clear();ut.clear();tt=0;
            tarjan(B[i],0);
            for(int j=0;j<wk.size();j++)
                if(mark[wk[j]])
                    ut.push_back(wk[j]);
            res=0;dfs_ans(0,B[i]);
            ans=ans*res%mod;
        }
    }
    printf("%lld\n",(ans-1+mod)%mod);
    return 0;
}