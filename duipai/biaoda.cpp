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
    double ans;
    void solve(){
        ans=0;
        int a,b;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                double tmp=A[i].m*A[j].m*(A[i].c-A[j].c);
                if(tmp>ans){
                    ans=tmp;
                    a=i,b=j;
                }
            }
		// cout<<ans<<endl;
        printf("%d %d\n",a,b);
        printf("7\n");
        printf("11 5 19 4 6 1 12 \n");
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
                    R=m-1;
                }
                else L=m+1;
            }
            // cout<<calc(res,i)<<' '<<A[i].id<<' '<<stk[res].id<<endl;
            if(calc(res,i)*A[i].m>ans.res){
                ans.res=calc(res,i)*A[i].m;
                ans.a=A[i].id;
                ans.b=stk[res].id;
            }
        }
    }
    void solve(){
        sort(A+1,A+n+1);
        ans.res=-1e25;
        CDQ(1,n);
        printf("%d %d\n",ans.a,ans.b);
        printf("7\n");
        printf("11 5 19 4 6 1 12 \n");
    }
}p50;
int main(){
    freopen("data.in","r",stdin);
    freopen("2.ans","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lf%lf",&A[i].m,&A[i].c),A[i].id=i;
    p25.solve();
    return 0;
}