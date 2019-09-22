#include<stdio.h>
#include<algorithm>
#include<string.h>
#define LL long long
#define M 100005
using namespace std;
const int mod=998244353;
int n,m,K;
LL sum[M],fac[M],inv[M];
void Plus(LL &x,LL y){
    x+=y;
    if(x>=mod)x-=mod;
    if(x<0)x+=mod;
}
LL S(int l,int r){
    if(l<=r)return sum[r]-sum[l-1];
    return sum[n]-sum[l-1]+sum[r];
}
LL Pow(LL x,int n){
    LL res=1;
    while(n){
        if(n&1)res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }return res;
}
LL Com(int a,int b){
    if(a<b||a<0||b<0)return 0;
    return fac[a]*inv[a-b]%mod*inv[b]%mod;
}
LL Per(int a,int b){
    if(a<b||a<0||b<0)return 0;
    return fac[a]*inv[a-b]%mod;
}
void init(){
    int ed=1e5;
    fac[0]=1;
    for(int i=1;i<=ed;i++)fac[i]=fac[i-1]*i%mod;
    inv[ed]=Pow(fac[ed],mod-2);
    for(int i=ed;i;i--)inv[i-1]=inv[i]*i%mod;
}
LL calc0(int c1,int c2){
    LL res=0;
    Plus(res,Com(m,c1+c2)*Com(c1+c2,c1)%mod*Per(n-1-c1-c2,m-c1-c2)%mod);
    Plus(res,Com(m,c1+c2+1)*Com(c1+c2,c1+1)%mod*Per(n-1-c1-c2,m-c1-c2-1)%mod);
    Plus(res,Com(m,c1+c2+1)*Com(c1+c2,c2+1)%mod*Per(n-1-c1-c2,m-c1-c2-1)%mod);
    return res;
}
LL calc1(int c1,int c2){
    LL res=0;
    Plus(res,c1*Com(m,c1+c2+1)%mod*Com(c1+c2,c1+1)%mod*Per(n-1-c1-c2,m-c1-c2-1)%mod);
    Plus(res,c2*Com(m,c1+c2+1)%mod*Com(c1+c2,c2+1)%mod*Per(n-1-c1-c2,m-c1-c2-1)%mod);
    return res;
}
int main(){
    init();
    for(int _=(scanf("%d",&_),_);_;_--){
        scanf("%d%d%d",&n,&m,&K);
        for(int i=1,x;i<=n;i++)scanf("%d",&x),sum[i]=sum[i-1]+x;
        if(K==0){puts("1");continue;}
        LL ans=0;
        for(int l=2,r=3;l<n;l++){
            while(r<=n&&S(r,l)>=K)r++;
            if(S(r-1,l)<K)continue;
            Plus(ans, calc0(l-1,n-r+2));
            Plus(ans,-calc0(l  ,n-r+2));
        }
        for(int l=2,r=3;l<n;l++){
            while(r<=n&&S(r,l)+sum[1]>=K)r++;
            if(S(r-1,l)+sum[1]<K)continue;
            Plus(ans, calc1(l-1,n-r+2));
            Plus(ans,-calc1(l  ,n-r+2));
        }
        for(int l=2;l<n;l++){
            if(S(1,l)<K)continue;
            int c=l-1;
            Plus(ans,Com(m,c)*Per(n-2-c,m-c)%mod);
            Plus(ans,c*Com(m,c+1)%mod*Per(n-2-c,m-c-1)%mod);
            break;
        }
        for(int r=n;r>2;r--){
            if(S(r,1)<K)continue;
            int c=n-r+1;
            Plus(ans,Com(m,c)*Per(n-2-c,m-c)%mod);
            Plus(ans,c*Com(m,c+1)%mod*Per(n-2-c,m-c-1)%mod);
            break;
        }
        if(sum[1]>=K)Plus(ans,Per(n-3,m));
        printf("%lld\n",ans*Pow(Per(n,m),mod-2)%mod);
    }
    return 0;
}
