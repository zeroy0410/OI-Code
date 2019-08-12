#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
const LL mod=1e9+7;
int n,A[M];
LL gcd(LL a,LL b){
    return b==0?a:gcd(b,a%b);
}
LL qkpow(LL a,LL b){
    LL res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
struct P30{
    LL ans;
    LL cnt[3005],hav[M];
    int hcnt,in[3005],h[M],tt;
    LL dp[3005][2];
    struct edge{
        int nxt,to;
    }G[M];
    void Add(int a,int b){
        G[++tt]=(edge){h[a],b};
        h[a]=tt;
    }
    queue<int>Q;
    void solve(){
        hcnt=tt=0;ans=1;
        memset(dp,0,sizeof(dp));
        memset(in,0,sizeof(in));
        for(int i=1;i<=n;i++)cnt[A[i]]++;
        for(int i=1;i<=3000;i++){
            if(cnt[i])hav[++hcnt]=i;
        }
        for(int i=1;i<=hcnt;i++)
            for(int j=i+1;j<=hcnt;j++){
                LL k=sqrt(hav[i]*hav[i]+hav[j]*hav[j]);
                if(k*k==hav[i]*hav[i]+hav[j]*hav[j]&&gcd(hav[i],hav[j])==1){
                    Add(i,j);
                    in[j]++;
                }
            }
        int t=hcnt+1;
        for(int i=1;i<=hcnt;i++){
            if(h[i]==0){Add(i,t);in[t]++;}
        }
        hcnt++;
        for(int i=1;i<=hcnt;i++){
            dp[i][0]=1;
            dp[i][1]=(qkpow(2,cnt[hav[i]])-1+mod)%mod;
            if(!in[i]){
                Q.push(i);
            }
        }
        while(!Q.empty()){
            int x=Q.front();Q.pop();
            for(int i=h[x];i;i=G[i].nxt){
                int u=G[i].to;
                dp[u][0]=(dp[u][0]*(dp[x][0]+dp[x][1]))%mod;
                dp[u][1]=(dp[u][1]*dp[x][0])%mod;
                in[u]--;
                if(in[u]==0)
                    Q.push(u);
            }
        }
        printf("%lld\n",(dp[t][0]-1+mod)%mod);
    }
}p30;
int main(){
    freopen("gougu.in","r",stdin);
    freopen("gougu.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&A[i]);
    p30.solve();
    return 0;
}