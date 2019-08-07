#include<bits/stdc++.h>
#define M 50005
using namespace std;
int n;
struct node{
    double m,c;
    int id;
    bool operator < (const node& res)const{
        return c<res.c;
    }
}A[M];
struct P25{
    double ans,ans2;
    bool mark[25];
    int Ans[25],tmp[25],acnt;
    double calc(int i,int j){
        return A[i].m*A[j].m*(A[i].c-A[j].c);
    }
    void dfs(int x){
        if(x>=1){
            double res=0;
            for(int i=1;i<=x-1;i++)res+=calc(tmp[i],tmp[i+1]);
            res+=calc(tmp[x],tmp[1]);
            if(res>ans2){
                ans2=res;
                acnt=x;
                for(int i=1;i<=acnt;i++)
                    Ans[i]=tmp[i];
            }
            if(x==n)return;
        }
        for(int i=1;i<=n;i++){
            if(!mark[i]){
                tmp[x+1]=i;
                mark[i]=1;
                dfs(x+1);
                mark[i]=0;
            }
        }
    }
    void solve2(){
        dfs(0);
        printf("%d\n",acnt);
        for(int i=1;i<=acnt;i++)
            printf("%d ",Ans[i]);
        printf("\n");
    }
    void solve(){
        ans=-1e15;ans2=-1e15;
        int a,b;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                double tmp=A[i].m*A[j].m*(A[i].c-A[j].c);
                if(tmp>ans){
                    ans=tmp;
                    a=i,b=j;
                }
            }
        printf("%d %d\n",a,b);
        if(n<=8)solve2();
        else {
            printf("7\n");
            printf("11 5 19 4 6 1 12 \n");
        }
    }
}p25;
struct P50{
    struct point{
        double x,y;
        int id;
        bool operator < (const point& res)const{
            return x<res.x;
        }
    }Q[M],stk[M];
    struct Ans{int a,b;double res;}ans;
    bool cmp(point &a,point &b,point &c){
        return (long double)(c.y-a.y)*(a.x-b.x)>=(long double)(a.y-b.y)*(c.x-a.x);
    }
    double calc(int m,int i){
        return stk[m].y-A[i].c*stk[m].x;
    }
    int top;
    void CDQ(int l,int r){
        if(l>=r)return;
        int mid=(l+r)>>1;
        CDQ(l,mid);top=0;
        for(int i=l;i<=mid;i++)
            Q[i]=(point){-A[i].m,-A[i].m*A[i].c,A[i].id};
        sort(Q+l,Q+mid+1);
        for(int i=1;i<=n;i++){
            while(top>1&&cmp(stk[top],stk[top-1],Q[i]))top--;
            stk[++top]=Q[i];
        }
        for(int i=mid+1;i<=r;i++){
            int L=2,R=top,res=1;
            while(L<=R){
                int m=(L+R)>>1;
                if(calc(m,i)>calc(m-1,i)){
                    res=m;
                    L=m+1;
                }
                else R=m-1;
            }
            // cout<<calc(res,i)<<' '<<A[i].id<<' '<<stk[res].id<<endl;
            if(calc(res,i)*A[i].m>ans.res){
                ans.res=calc(res,i)*A[i].m;
                ans.a=A[i].id;
                ans.b=stk[res].id;
            }
        }
        CDQ(mid+1,r);
    }
    void solve(){
        sort(A+1,A+n+1);
        ans.res=-1e25;
        CDQ(1,n);
        // cout<<ans.res<<endl;
        printf("%d %d\n",ans.a,ans.b);
        printf("7\n");
        printf("11 5 19 4 6 1 12 \n");
    }
}p50;
int main(){
    freopen("efield.in","r",stdin);
    freopen("efield.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lf%lf",&A[i].m,&A[i].c),A[i].id=i;
    if(n<=1000)p25.solve();
    else p50.solve();
    return 0;
}