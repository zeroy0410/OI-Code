#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#define N 55
#define For(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

int n,color[N],nxt[N],dp[N][N],v[N];

int f(int x){return x*x;}
void dfs(int l,int r,int color_sum,int &ans,int sum_dp)
{
    ans=f(color_sum)+dp[l+1][r]+sum_dp;int t=0;
    for(int j=nxt[l];j&&j<=r;j=nxt[j])
    {   
        dfs(j,r,color_sum+v[j],t,sum_dp+dp[l+1][j-1]);
        ans=max(ans,t);
    }

}
int main()
{
    scanf("%d",&n);
    For(i,1,n)scanf("%d",&color[i]);
    For(i,1,n)scanf("%d",&v[i]);
    For(i,1,n)For(j,i+1,n)
    if(color[j]==color[i]){nxt[i]=j;break;}
    For(i,1,n)dp[i][i]=v[i]*v[i];
    For(k,1,n)
        For(i,1,n-k)
            dfs(i,i+k,v[i],dp[i][i+k],0);
    printf("%d",dp[1][n]);

}
