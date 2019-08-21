#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define LL rt<<1
#define RR rt<<1|1
#define lson l,m,LL
#define rson m+1,r,RR
const int maxn  =  44444;
int col[maxn<<2],sum[maxn<<2];
int lbd[maxn<<2],rbd[maxn<<2];
struct node{
    char op[5];
    int l,r;
}q[22222];
int x[maxn];
void pushup(int rt,int l,int r){
    if(col[rt]){
        sum[rt]=0;
        lbd[rt]=rbd[rt]=1;
        return;
    }
    if(l==r){
        lbd[rt]=rbd[rt]=0;
        sum[rt]=1;
        return;
    }
    lbd[rt]=lbd[LL];
    rbd[rt]=rbd[RR];
    sum[rt]=sum[LL]+sum[RR]-(!rbd[LL]&&!lbd[RR]);
}
void build(int l,int r,int rt){
    sum[rt]=1;
    col[rt]=lbd[rt]=rbd[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(lson);
    build(rson);
}
void update(int L,int R,int c,int l,int r,int rt){
    if(L<=l&&r<=R) {
        col[rt]+=c;
        pushup(rt,l,r);
        return ;
    }
    int m=(l+r)>>1;
    if(L<=m) update(L,R,c,lson);
    if(R>m) update(L,R,c,rson);
    if(col[rt]) return;
    pushup(rt,l,r);
}
int main(){
    int n,i,j,t,num,ca=1;
    scanf("%d",&t);
    while(t--){
        int cnt=0;
        scanf("%d%d",&num,&n);
        for(i=0;i<n;i++){
            scanf("%s%d%d",q[i].op,&q[i].l,&q[i].r);
            x[cnt++]=q[i].l;x[cnt++]=q[i].r;
        }
        x[cnt++]=0;x[cnt++]=num-1;
        sort(x,x+cnt);
        int m=1;
        for(i=1;i<cnt;i++)   if(x[i]!=x[i-1]) x[m++]=x[i];
        for(i=m-1;i>=1;i--)  if(x[i]!=x[i-1]+1) x[m++]=x[i-1]+1;
        sort(x,x+m);
        build(0,m-1,1);
        printf("Case #%d:\n",ca++);
        for(i=0;i<n;i++){
            int l=lower_bound(x,x+m,q[i].l)-x;
            int r=lower_bound(x,x+m,q[i].r)-x;
            int c=q[i].op[0]=='p'?1:-1;
            update(l,r,c,0,m-1,1);
            printf("%d\n",sum[1]);
        }
    }
    return 0;
}