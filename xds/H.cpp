#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define M 100005
#define LL long long
using namespace std;
int T,n;
struct node{
    int t,p;
    bool operator < (const node& res)const{
        return t<res.t;
    }
}A[M];
struct YD_tree{
    struct YD{
        int l,r,sum;
        LL pos[4];
    }tree[M<<2];
    #define fa tree[p]
    #define lson tree[p<<1]
    #define rson tree[p<<1|1]
    void up(int p){
        fa.sum=lson.sum+rson.sum;
        for(int i=1;i<=3;i++){
            fa.pos[i]=lson.pos[i]+rson.pos[(i+lson.sum-1)%3+1];
        }
    }
    void build(int l,int r,int p){
        fa.l=l;fa.r=r;fa.sum=0;
        memset(fa.pos,0,sizeof(fa.pos));
        if(l==r)return;
        int mid=(l+r)>>1;
        build(l,mid,p<<1);
        build(mid+1,r,p<<1|1);
    }
    void update(int x,int p){
        if(fa.l==fa.r&&fa.l==x){
            fa.sum=1;
            for(int i=1;i<=3;i++)
                fa.pos[i]=1LL*i*A[x].p;
            return;
        }
        int mid=(fa.l+fa.r)>>1;
        if(x<=mid)update(x,p<<1);
        else update(x,p<<1|1);
        up(p);
    }
}Tr;
struct que{
    int w,id;
    bool operator < (const que& res)const{
        return w<res.w;
    }
}B[M];
double answ,ans;
int main(){
    scanf("%d",&T);
    while(T--){
        ans=-1e9;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",&A[i].p);
        for(int i=1;i<=n;i++)scanf("%d",&A[i].t);
        sort(A+1,A+n+1);A[0].t=0;
        Tr.build(1,n,1);
        for(int i=1;i<=n;i++)
            B[i]=(que){A[i].t-A[i-1].t,i};
        sort(B+1,B+n+1);
        B[n+1].w=-1;
        for(int i=1;i<=n;i++){
            Tr.update(B[i].id,1);
            if(B[i].w!=B[i+1].w){
                double tmp=1.0*Tr.tree[1].pos[1]/Tr.tree[1].sum;
                if(tmp>ans){
                    answ=B[i].w;
                    ans=tmp;
                }
            }
        }
        printf("%.6lf %.6lf\n",answ,ans);
    }
    return 0;
}