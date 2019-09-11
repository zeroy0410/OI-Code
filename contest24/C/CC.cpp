#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
//999911658=2*3*4679*35617
#define LL long long
#define mod 999911659
using namespace std;
LL N,G,e;
LL x[4];
LL pre[4][40000];
LL ni[4][40000];
LL zs[4]={2,3,4679,35617};
LL gcd(LL a,LL b,LL &x,LL &y)//求逆元
{
    if(b==0) {x=1;y=0;}
    else     {gcd(b,a%b,y,x); y-=(a/b)*x;}
}
LL lucas(LL p,LL q,LL o)//卢卡斯定理
{
    LL sum=1;
    while(p && q)
    {
        LL x=p%zs[o],y=q%zs[o];
        if(y>x) return 0;
        sum=(sum*(pre[o][x]*(ni[o][x-y]*ni[o][y])%zs[o])%zs[o])%zs[o];
        p/=zs[o];
        q/=zs[o];
    }
    return sum;
}
int main()
{
    scanf("%lld%lld",&N,&G);
    if(G%mod==0) {printf("0\n");return 0;}
    for(int o=0;o<4;o++)//预处理
    {
        pre[o][0]=1;ni[o][0]=1; 
        for(int i=1;i<=zs[o];i++)
        pre[o][i]=(pre[o][i-1]*i)%zs[o];
        ni[o][zs[o]-1]=zs[o]-1;
        for(int i=zs[o]-2;i>=1;i--)
        ni[o][i]=(ni[o][i+1]*(i+1))%zs[o];
        for(LL i=1;i<=sqrt(N);i++)//统计组合数
        if(N%i==0)
        {
            x[o]=(x[o]+lucas(N,i,o))%zs[o];
            if(i*i<N) x[o]=(x[o]+lucas(N,N/i,o))%zs[o];
        }
    };
    for(int i=0;i<4;i++)//中国剩余定理
    {
        LL o,p;
        LL M=(mod-1)/zs[i];
        gcd(M,zs[i],o,p);
        e=(e+x[i]*o*M)%(mod-1);
    }
    while(e<=0) e+=mod-1;
    LL ans=1,a=G;
    while(e)
    {
        if(e&1) ans=(ans*a)%mod;
        a=(a*a)%mod;
        e>>=1;
    }
    printf("%lld\n",ans);
    return 0;
}
