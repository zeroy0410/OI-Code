#include<bits/stdc++.h>
#define M 50005
using namespace std;
int n;
struct node{double m,c;int id;}A[M];
bool cmp(node a,node b){return a.c<b.c;}
struct Subtask1{
    int a,b;
    double ans;
    void work(int l,int r,int L,int R){
        if(l>r||L>R)return;
        int mid=(l+r)>>1,po=L;
        double mx=-1;
        for(int i=L;i<=min(mid,R);i++){
            double res=A[mid].m*A[i].m*(A[mid].c-A[i].c);
            if(res>mx)mx=res,po=i;
        }
        if(mx>ans){
            ans=mx;
            a=mid,b=po;
        }
        if(l==r)return;
        work(l,mid-1,L,po);
        work(mid+1,r,po,R);
    }
    void solve(){
        ans=-1;
        sort(A+1,A+n+1,cmp);
        work(1,n,1,n);
        printf("%d %d\n",A[a].id,A[b].id);
    }
}P1;
struct Subtask2{
    struct poi{
        double x,y,k,d;int id;
        bool operator < (const poi& res)const{
            if(k!=res.k)return k<res.k;
            return d<res.d;
        }
    }Q[M];
    bool check(poi c,poi a,poi b){return (c.y-a.y)*(a.x-b.x)>=(a.y-b.y)*(c.x-a.x);}
    int stk[M],top;
    void solve(){
        for(int i=1;i<=n;i++){
            Q[i].x=A[i].m*A[i].c;
            Q[i].y=A[i].m;
            Q[i].id=A[i].id;
        }
        Q[0].x=Q[0].y=1e18;int id=0;
        for(int i=1;i<=n;i++)
            if(Q[i].x<Q[id].x||Q[i].x==Q[id].x&&Q[i].y<Q[id].y)id=i;
        swap(Q[id],Q[1]);
        for(int i=2;i<=n;i++){
            Q[i].k=(Q[i].y-Q[1].y)/(Q[i].x-Q[1].x);
            Q[i].d=(Q[i].y-Q[1].y)*(Q[i].y-Q[1].y)+(Q[i].x-Q[1].x)*(Q[i].x-Q[1].x);
        }
        sort(Q+2,Q+n+1);
        for(int i=1;i<=n;i++){
            while(top>1&&check(Q[i],Q[stk[top-1]],Q[stk[top]]))top--;
            stk[++top]=i;
        }
        printf("%d\n",top);
        for(int i=1;i<=top;i++)printf("%d ",Q[stk[i]].id);
        printf("\n");
    }
}P2;
int main(){
    freopen("efield.in","r",stdin);
    freopen("efield.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf",&A[i].m,&A[i].c),A[i].id=i;
    P1.solve();P2.solve();
    return 0;
}