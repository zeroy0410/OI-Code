#include<bits/stdc++.h>
#define LL long long
#define M 100005
using namespace std;
int n,k,A[M];
struct P100{
    struct node{
        LL x,y;int id;
    }stk[M],P[2][M];
    int top;
    LL dp[M][2],sum[M],Pos[M][205];
    LL calc(int l,int r){
        return sum[r]-sum[l-1];
    }
    void Init(){
        for(int i=1;i<=n;i++)sum[i]=sum[i-1]+A[i];
    }
    void Print(int x,int res){
        if(res==1)return;
        printf("%d ",Pos[x][res]);
        Print(Pos[x][res],res-1);
    }
	bool calcK(node &a,node &b,node &c){
		if(b.x==c.x||b.x==a.x)return c.y>b.y;
		return 1.0*(b.y-a.y)*(c.x-a.x)<=1.0*(c.y-a.y)*(b.x-a.x);
	}
    void solve(){
        Init();
        for(int i=1;i<=n;i++)
            for(int r=0;r<=1;r++)dp[i][r]=-1e18;
        for(int i=1;i<n;i++)dp[i][1]=sum[i]*(sum[n]-sum[i]),P[1][i]=(node){sum[i],dp[i][1],i};
        for(int r=2;r<=k;r++){
			int cur=(r&1);
			for(int i=1;i<n;i++)dp[i][cur]=-1e18;top=0;
            int pos=1,now=1;
            for(int i=1;i<n;i++){
                while(P[!(r&1)][pos].id<i&&pos<n){
                    while(top>1&&calcK(stk[top-1],stk[top],P[!(r&1)][pos]))top--;
                    stk[++top]=P[!(r&1)][pos++];
					if(top<now)now=top;
                }
                if(top){
					while(now<top&&dp[stk[now+1].id][!cur]+calc(stk[now+1].id+1,i)*calc(i+1,n)
							>dp[stk[now].id][!cur]+calc(stk[now].id+1,i)*calc(i+1,n))now++;
                    dp[i][cur]=dp[stk[now].id][!cur]+calc(stk[now].id+1,i)*calc(i+1,n);
                    Pos[i][r]=stk[now].id;
                }
                P[r&1][i]=(node){sum[i],dp[i][cur],i};
            }
        }
        LL ans=0;int mx=0;
        for(int i=1;i<=n;i++){
            if(dp[i][k&1]>ans){
                ans=dp[i][k&1];
                mx=i;
            }
        }
        printf("%lld\n",ans);
        printf("%d ",mx);
        Print(mx,k);
        puts("");
    }
}p100;
int main(){
// 	freopen("sequence.in","r",stdin);
// 	freopen("sequence.out","w",stdout);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&A[i]);
    p100.solve();
    return 0;
}
