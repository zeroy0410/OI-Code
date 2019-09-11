#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define MOD 19940417
#define MAX 1000100
inline int read()
{
    int x=0;bool t=false;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=true,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return t?-x:x;
}
struct Data{int x,y;}a[MAX];
bool operator<(Data a,Data b){return a.x<b.x;}
int fac[3]={0,7,2848631};
int jc[3][2848631];
int inv[3][2848631];
void exgcd(int a,int b,int &x,int &y){if(!b){x=1,y=0;return;}exgcd(b,a%b,y,x);y-=a/b*x;}
int Inv(int n,int m){int x,y;exgcd(n,m,x,y);return (x%m+m)%m;}
int C(int n,int m,int p)
{
    if(n<m)return 0;
    return 1ll*jc[p][n]*inv[p][m]%fac[p]*inv[p][n-m]%fac[p];
}
int Lucas(int n,int m,int p)
{
    if(n<p)return C(n,m,p);
    return 1ll*Lucas(n/fac[p],m/fac[p],p)*C(n%fac[p],m%fac[p],p)%fac[p];
}
int C(int n,int m)
{
    int w[3]={0,0,0};if(n<m||n<0||m<0)return 0;
    for(int i=1;i<=2;++i)w[i]=Lucas(n,m,i);
    int x=Inv(fac[1],fac[2]);
    x=1ll*x*(w[2]-w[1]+MOD)%MOD;
    return (1ll*x*fac[1]+w[1])%MOD;
}
int Calc(int n,int m,int b)
{
    int ret=C(n+m,n)-C(n+m,n+b);
    return (ret+MOD)%MOD;
}
int n,K,ans=1,mx;
int main()
{
    n=read();K=read();
    for(int i=1;i<=K;++i)a[i].x=read(),a[i].y=read();
    a[++K]=(Data){0,0};a[++K]=(Data){n,0};
    sort(&a[1],&a[K+1]);
    for(int i=1;i<=2;++i)
    {
        jc[i][0]=inv[i][0]=inv[i][1]=1;
        for(int j=1;j<fac[i];++j)jc[i][j]=1ll*jc[i][j-1]*j%fac[i];
        for(int j=2;j<fac[i];++j)inv[i][j]=1ll*inv[i][fac[i]%j]*(fac[i]-fac[i]/j)%fac[i];
        for(int j=2;j<fac[i];++j)inv[i][j]=1ll*inv[i][j-1]*inv[i][j]%fac[i];
    }
    for(int i=1;i<K;++i)
    {
        int b=a[i].y+1;
        int n=a[i+1].x-a[i].x;
        if(!n)continue;
        int m=a[i+1].y-a[i].y;
        int up=(n+m)/2,dn=(n-m)/2;
        ans=1ll*ans*Calc(up,dn,b)%MOD;
        mx=max(mx,a[i].y+up);
    }
    printf("%d %d\n",ans,mx);
    return 0;
}
