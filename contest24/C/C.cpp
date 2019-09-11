#include<bits/stdc++.h>
#define LL long long
#define M 40005
using namespace std;
const LL mod=999911659;
LL n,G;
LL md[15]={2,3,4679,35617};
LL tmp[15];
void exgcd(LL a,LL b,LL &d,LL &x,LL &y){
    if(!b){d=a;x=1;y=0;return;}
    exgcd(b,a%b,d,y,x);y-=a/b*x;
}
LL qkpow(LL a,LL b,LL MOD){
    LL res=1;
    while(b){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}
LL fac[M][4],Ifac[M][4];
void Init(){
    for(int op=0;op<4;op++){
        fac[0][op]=1;Ifac[0][op]=1;
        for(int i=1;i<M;i++){
            fac[i][op]=fac[i-1][op]*i%md[op];
            Ifac[i][op]=Ifac[i-1][op]*qkpow(i,md[op]-2,md[op])%md[op];
        }
    }
}
LL C(LL a,LL b,int op){return fac[a][op]*Ifac[b][op]%md[op]*Ifac[a-b][op]%md[op];}
LL lucas(LL a,LL b,int op){
    LL res=1;
    while(a&&b){
        LL x=a%md[op],y=b%md[op];if(y>x)return 0;
        res=res*C(x,y,op)%md[op];
        a/=md[op];b/=md[op];
    }
    return res;
}
#undef M
LL po=0;
int main(){
    freopen("pig.in","r",stdin);
    freopen("pig.out","w",stdout);
    Init();
    scanf("%lld%lld",&n,&G);
    for(LL i=1;i*i<=n;i++){
        if(n%i==0){
            for(int op=0;op<4;op++){
                tmp[op]=(tmp[op]+lucas(n,i,op))%md[op];
                if(i*i<n)tmp[op]=(tmp[op]+lucas(n,n/i,op))%md[op];
            }
        }
    }
    for(int op=0;op<4;op++){
        LL x,y,d;
        LL M=(mod-1)/md[op];
        exgcd(M,md[op],d,x,y);
        x=(x%md[op]+md[op])%md[op];
        po=(po+tmp[op]*x%(mod-1)*M%(mod-1))%(mod-1);
    }
    LL ans=qkpow(G,po,mod);
    if(po==0)printf("0");
    else printf("%lld\n",ans);
    return 0;
}