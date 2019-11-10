#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
bool mm1;
int n,m;
struct Blo{int l,r;}A[M];
struct Mu{int l,r,h;}B[M];
int L[M<<2],lc;  
LL ans[M];
struct YD_tree{
    struct node{
        int l,r,mx,ad;
    }tree[M<<4];
    #define fa tree[p]
    #define lson tree[p<<1]
    #define rson tree[p<<1|1]
    void down(int p){
        if(B[lson.mx].h<B[fa.mx].h)lson.mx=fa.mx;
        if(B[rson.mx].h<B[fa.mx].h)rson.mx=fa.mx;
        lson.ad+=fa.ad;
        rson.ad+=fa.ad;
        fa.ad=0;
    }
    void build(int l,int r,int p){
        fa.l=l;fa.r=r;fa.mx=fa.ad=0;
        if(l==r)return;
        int mid=(l+r)>>1;
        build(l,mid,p<<1);
        build(mid+1,r,p<<1|1);
    }
    void update(int l,int r,int d,int p){
        if(fa.l==l&&fa.r==r){
            if(B[fa.mx].h<B[d].h)
                fa.mx=d;
            return;
        }
        down(p);
        int mid=(fa.l+fa.r)>>1;
        if(r<=mid)update(l,r,d,p<<1);
        else if(l>mid)update(l,r,d,p<<1|1);
        else {
            update(l,mid,d,p<<1);
            update(mid+1,r,d,p<<1|1);
        }
    }
    void add(int l,int r,int d,int p){
        if(fa.l==l&&fa.r==r){
            fa.ad+=d;
            return;
        }
        down(p);
        int mid=(fa.l+fa.r)>>1;
        if(r<=mid)add(l,r,d,p<<1);
        else if(l>mid)add(l,r,d,p<<1|1);   
        else{
            add(l,mid,d,p<<1);
            add(mid+1,r,d,p<<1|1);
        }
    }
    void query(int x,int p){
        if(fa.l==x&&fa.r==x){
            ans[fa.mx]+=1LL*(L[x+1]-L[x])*fa.ad;
            return;
        }
        down(p);
        int mid=(fa.l+fa.r)>>1;
        if(x<=mid)query(x,p<<1);
        else if(x>mid)query(x,p<<1|1);
    }
}T;
bool mm2;
int main(){
    // printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
    while(~scanf("%d%d",&n,&m)){
        lc=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&A[i].l,&A[i].r);
            L[++lc]=A[i].l;L[++lc]=A[i].r;
        }
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&B[i].l,&B[i].r,&B[i].h);
            L[++lc]=B[i].l;L[++lc]=B[i].r;
        }
        sort(L+1,L+lc+1);
        lc=unique(L+1,L+lc+1)-L-1;
        T.build(1,lc,1);
        for(int i=1;i<=n;i++){
            A[i].l=lower_bound(L+1,L+lc+1,A[i].l)-L;
            A[i].r=lower_bound(L+1,L+lc+1,A[i].r)-L;
            T.add(A[i].l,A[i].r-1,1,1);
        }
        for(int i=1;i<=m;i++){
            B[i].l=lower_bound(L+1,L+lc+1,B[i].l)-L;
            B[i].r=lower_bound(L+1,L+lc+1,B[i].r)-L;
            T.update(B[i].l,B[i].r-1,i,1);
        }
        memset(ans,0,sizeof(ans));
        for(int i=1;i<=lc;i++)T.query(i,1);
        for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
        printf("\n");
    }
    return 0;
}
