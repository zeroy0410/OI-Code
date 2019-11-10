#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
const int mod=100000007;
int n,m;
struct P0{
    LL qkpow(LL a,LL b){
        LL res=1;
        while(b){
            if(b&1)res=res*a%mod;
            a=a*a%mod;
            b>>=1;
        }
        return res;
    }
    LL dp[M],pre[M];
    void rm(LL &x,LL y){
        x-=y;
        if(x<0)x+=mod;
    }
    void solve(){
        dp[1]=dp[2]=0;
        LL tot=qkpow(2,n)-1;
        pre[0]=1;
        for(int i=1;i<=m;i++)
            pre[i]=pre[i-1]*(tot-i+1)%mod;
        for(int i=3;i<=m;i++)
            dp[i]=pre[i-1],rm(dp[i],dp[i-1]),rm(dp[i],dp[i-2]*(i-1)%mod*(tot-i+2)%mod);
        LL fac=1;
        for(int i=1;i<=m;i++)fac=fac*i%mod;
        printf("%lld\n",dp[m]*qkpow(fac,mod-2)%mod);
    }
}p0; 
int main(){
    freopen("canon.in","r",stdin);
    freopen("canon.out","w",stdout);
    scanf("%d%d",&n,&m);
    p0.solve();
    return 0;
}