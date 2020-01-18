#include<iostream>
#include<cstdio>
using namespace std;
#define MAX 100100
#define MOD 998244353
#define inv2 499122177
#define lson (now<<1)
#define rson (now<<1|1)
inline int read()
{
    int x=0;bool t=false;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=true,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return t?-x:x;
}
int n,m,pw=1,f[MAX<<3],g[MAX<<3],mul[MAX<<3],pls[MAX<<3],s[MAX<<3];
void Build(int now,int l,int r)
{
    mul[now]=1;if(l==r)return;
    int mid=(l+r)>>1;
    Build(lson,l,mid);Build(rson,mid+1,r);
}
void pushup(int now){s[now]=((s[lson]+s[rson])%MOD+f[now])%MOD;}
void upd(int now){f[now]=1ll*inv2*(f[now]+g[now])%MOD;pushup(now);}
void puttag(int now,int m,int p)
{
    cerr<<g[now]<<' '<<mul[now]<<' '<<pls[now]<<endl;
    g[now]=(1ll*g[now]*m+p)%MOD;
    mul[now]=1ll*mul[now]*m%MOD;
    pls[now]=(1ll*pls[now]*m+p)%MOD;
}
void pushdown(int now)
{
    if(mul[now]==1&&pls[now]==0)return;
    puttag(lson,mul[now],pls[now]);
    puttag(rson,mul[now],pls[now]);
    mul[now]=1;pls[now]=0;
}
void Modify(int now,int l,int r,int L,int R)
{
    if(L==l&&r==R)
    {
        f[now]=1ll*inv2*(f[now]+1)%MOD;
        puttag(now,inv2,inv2);pushup(now);return;
    }
    int mid=(l+r)>>1;pushdown(now);
    f[now]=1ll*inv2*f[now]%MOD;
    g[now]=1ll*inv2*g[now]%MOD;
    if(R<=mid)Modify(lson,l,mid,L,R),upd(rson);
    else if(L>mid)Modify(rson,mid+1,r,L,R),upd(lson);
    else Modify(lson,l,mid,L,mid),Modify(rson,mid+1,r,mid+1,R);
    pushup(now);
}
int main()
{
    n=read();m=read();
    while(m--)
    {
        int opt=read(),l,r;
        if(opt==1)l=read(),r=read(),Modify(1,1,n,l,r),pw=(pw+pw)%MOD;
        else printf("%lld\n",1ll*pw*s[1]%MOD);
    }
    return 0;
}