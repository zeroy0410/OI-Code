#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
const LL mod=1e9+7;
int n,A[M];
namespace Px{
    int cnt[M];
    int gcd(int a,int b){
        return !b?a:gcd(b,a%b);
    }
    struct node{
        int x,y;
    }ED[20];
    LL pw2[M],ans;
    int ch[M];
    void Add(LL &x,LL y){
        x+=y;
        if(x>=mod)x-=mod;
        if(x<0)x+=mod;
    }
    vector<int>to[M],poi,son[M];
    bool vis[M],mark[M],cho[M];int le,w[M];
    void dfsuntre(int v,int f){
        vis[v]=1;poi.push_back(v);
        for(int u:to[v]){
            if(u==f)continue;
            if(vis[u]){
                ED[++le]=(node){min(u,v),max(u,v)};
                mark[u]=mark[v]=1;
            }else{
                dfsuntre(u,v);
                son[v].push_back(u);
            }
        }
    }
    LL dp[M][2];
    void dfstree(int v,int f){
        dp[v][0]=1,dp[v][1]=pw2[cnt[v]]-1;
        if(mark[v])dp[v][!cho[v]]=0;
        for(int u:son[v]){
            dfstree(u,v);
            dp[v][0]=dp[v][0]*(dp[u][1]+dp[u][0])%mod;
            dp[v][1]=dp[v][1]*dp[u][0]%mod;
        }
    }
    void dfssolve(int x,int rt,LL &res){
        if(x>w[0]){
            for(int i=1;i<=le;i++)
                if(cho[ED[i].x]&&cho[ED[i].y])return;
            dfstree(rt,0);
            res=(res+dp[rt][0]+dp[rt][1])%mod;
            return;
        }
        cho[w[x]]=1;dfssolve(x+1,rt,res);
        cho[w[x]]=0;dfssolve(x+1,rt,res);
    }

    void solve(){
        pw2[0]=1;int mx=0,tl=0;
        for(int i=1;i<=n;i++){
            pw2[i]=pw2[i-1]*2%mod;
            mx=max(mx,A[i]);
            cnt[A[i]]++;
        }
        for(LL i=2;i*2<=mx;i++)
            for(LL j=1+(i&1);j*i*2<=mx&&j<i;j+=2)
                if(gcd(i,j)==1){
                    LL a=i*i-j*j;
                    LL b=2*i*j;
                    if(a>mx)continue;
                    if(!cnt[a]||!cnt[b])continue;
                    to[a].push_back(b);
                    to[b].push_back(a);
                }
        ans=1;
        for(int i=1,res;i<=mx;i++)if(!vis[i]){
            poi.clear();
            w[0]=le=0;
            dfsuntre(i,0);
            for(int u:poi)
                if(mark[u])
                    w[++w[0]]=u;
            LL res=0;
            dfssolve(1,i,res);
            ans=ans*res%mod;
        }

        printf("%lld\n",--ans);
    }
}
int main(){
    freopen("gougu.in","r",stdin);
    freopen("gougu.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&A[i]);
    Px::solve();
    return 0;
}