#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define re register
#define il inline
#define ll long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define fp(i,a,b) for(re int i=a;i<=b;i++)
#define fq(i,a,b) for(re int i=a;i>=b;i--)
using namespace std;
struct node{ll dat,w,v;bool operator < (const node &o) const{return dat<o.dat;}}a[100];
struct pzy{ll w,id;bool operator < (const pzy &o) const{return w<o.w;}}b[100];
ll n,k,o[100],s[100],len,dp[100][100][100];
il ll gi()
{
  re ll x=0,t=1;
  re char ch=getchar();
  while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
  if(ch=='-') t=-1,ch=getchar();
  while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
  return x*t;
}
il ll dfs(re int l,re int r,re int w)
{
    re ll ans=2e9;
    if(dp[l][r][w]!=-1) return dp[l][r][w];
    if(l>r) return dp[l][r][w]=0;
    fp(i,l,r)
    {
        if(a[i].w>=w) ans=min(ans,dfs(l,i-1,a[i].w)+dfs(i+1,r,a[i].w)+s[r]-s[l-1]);
        ans=min(ans,dfs(l,i-1,w)+dfs(i+1,r,w)+s[r]-s[l-1]+k);
    }
    return dp[l][r][w]=ans;
}
int main()
{
    memset(dp,-1,sizeof(dp));
    n=gi();k=gi();
    fp(i,1,n) a[i].dat=gi();fp(i,1,n) a[i].w=gi(),o[i]=a[i].w;fp(i,1,n) a[i].v=gi();
    //len=unique(o+1,o+1+n)-o-1;
    //fp(i,1,n) a[i].w=lower_bound(o+1,o+1+len,a[i].w)-o;
    sort(a+1,a+1+n);
    fp(i,1,n) b[i].w=a[i].w,b[i].id=i;
    sort(b+1,b+1+n);
    fp(i,1,n) a[b[i].id].w=i;
    fp(i,1,n) s[i]=s[i-1]+a[i].v;
    //这里不要预处理dp[l][r][w]=k之类，上面能处理
    printf("%lld\n",dfs(1,n,1));
    return 0;
}
