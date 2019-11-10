#include<bits/stdc++.h>
#define M 2005
#define LL long long
using namespace std;
int n,K,p,m,A[M];
struct YD_tree{
    struct YD{
        int l,r;
        LL sum;
    }tree[405];
    #define fa tree[p]
    #define lson tree[p<<1]
    #define rson tree[p<<1|1]
    void Up(int p){fa.sum=(lson.sum+rson.sum)%m;}
    void build(int l,int r,int p){
        fa.l=l;fa.r=r;
        if(l==r){
            fa.sum=0;
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,p<<1);
        build(mid+1,r,p<<1|1);
        Up(p);
    }
    void update(int x,LL d,int p){
        if(fa.l==x&&fa.r==x){
            fa.sum=(fa.sum+d)%m;
            return;
        }
        int mid=(fa.l+fa.r)>>1;
        if(x<=mid)update(x,d,p<<1);
        else update(x,d,p<<1|1);
        Up(p);
    }
    LL query(int l,int r,int p){
        if(fa.l==l&&fa.r==r)return fa.sum;
        int mid=(fa.l+fa.r)>>1;
        if(r<=mid)return query(l,r,p<<1);
        else if(l>mid)return query(l,r,p<<1|1);
        return (query(l,mid,p<<1)+query(mid+1,r,p<<1|1))%m;
    }
}Tr[M];
LL dp[M];
int main(){
    while(~scanf("%d%d%d%d",&n,&K,&p,&m)){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){scanf("%d",&A[i]);}
        for(int i=1;i<=n;i++)Tr[i].build(0,100,1);
        LL ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=i;j++){
                if(j>1)dp[j]=Tr[j-1].query(max(0,A[i]-p),min(100,A[i]+p),1);
                else dp[j]=1;
                if(j>=K)ans=(ans+dp[j])%m;
            }
            for(int j=1;j<=i;j++){
                Tr[j].update(A[i],dp[j],1);
            }  
        }
        printf("%lld\n",ans);
    }
    return 0;
}
