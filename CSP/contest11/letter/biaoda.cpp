#include<bits/stdc++.h>
#define M 200005
#define LL long long
using namespace std;
bool __1;
const LL mod=1e9+7;
int n,m;
char s[M];
LL B;
LL Pow(LL x,int n){
    LL res=1;
    while(n){
        if(n&1)res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }return res;
}
void Add(LL &x,LL y){
    x+=y;
    if(x>=mod)x-=mod;
}
namespace Pbl{
    void solve(){
        char tm[5];
        for(int i=1,op,l,r;i<=m;i++){
            scanf("%d",&op);
            if(op==0){
                scanf("%d%d",&l,&r);
                LL sum=0;
                for(int a=l;a<=r;a++){
                    LL res=0;
                    for(int b=a;b<=r;b++){
                        res=(res*B+s[b])%mod;
                        Add(sum,res);
                    }
                }
                LL len=r-l+1;
                printf("%lld\n",sum*Pow(1LL*len*(len+1)/2%mod,mod-2)%mod);
            }else{
                scanf("%d%s",&l,tm+1);
                s[l]=tm[1]-'a'+1;
            }
        }
    }
}
namespace Px{
    LL base[M],sumb[M];
    struct node{
        int len;
        LL ls,rs,ss,sum;
        node operator +(node a){
            node r;
            r.len=len+a.len;
            r.sum=(sum*base[a.len]+a.sum)%mod;
            r.ss=(ss+a.ss+(rs*sumb[a.len]+a.ls*len))%mod;
            r.rs=(rs*base[a.len]+a.sum*len+a.rs)%mod;
            r.ls=(sum*sumb[a.len]+a.ls+ls)%mod;
            return r;
        }
    };
    struct Seg{
        struct Tree{
            int L,R;
            node x;
        }T[M<<2];
#define lson T[p<<1]
#define rson T[p<<1|1]
        int TID[M];
        void Up(int p){
            T[p].x=lson.x+rson.x;
        }
        void Build(int l,int r,int p){
            T[p].L=l,T[p].R=r;
            if(l==r){
                TID[l]=p;
                node&t=T[p].x;
                t.len=1;
                t.sum=t.rs=t.ls=t.ss=s[l];
                return;
            }
            int mid=(l+r)>>1;
            Build(l,mid,p<<1);
            Build(mid+1,r,p<<1|1);
            Up(p);
        }
        void Upd(int x,int c){
            int p=TID[x];
            node&t=T[p].x;
            t.len=1;
            t.sum=t.rs=t.ls=t.ss=c;
            for(p>>=1;p;p>>=1)Up(p);
        }
        node Query(int l,int r,int p){
            if(T[p].L==l&&T[p].R==r)return T[p].x;
            int mid=(T[p].L+T[p].R)>>1;
            if(mid>=r)return Query(l,r,p<<1);
            else if(mid<l)return Query(l,r,p<<1|1);
            else return Query(l,mid,p<<1)+Query(mid+1,r,p<<1|1);
        }
    }Tr;
    void solve(){
        base[0]=1;
        for(int i=1;i<=n+1;i++)base[i]=base[i-1]*B%mod,sumb[i]=(sumb[i-1]+base[i])%mod;
        Tr.Build(1,n,1);
        char tm[5];
        for(int i=1,op,l,r;i<=m;i++){
            scanf("%d",&op);
            if(op==0){
                scanf("%d%d",&l,&r);
                LL inv=(r-l+1);
                inv=Pow(inv*(inv+1)/2%mod,mod-2);
                printf("%lld\n",(Tr.Query(l,r,1).ss*inv%mod+mod)%mod);
            }else{
                scanf("%d%s",&l,tm+1);
                Tr.Upd(l,tm[1]-'a'+1);
            }
        }
    }
}
bool __2;
int main(){
    scanf("%d%d%lld",&n,&m,&B);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++)s[i]=s[i]-'a'+1;
    if(n<=100)Pbl::solve();
    else Px::solve();
    return 0;
}
