#include<bits/stdc++.h>
#define M 1005
using namespace std;
int n,P,A[M],dp[M][M][2];
int dfs(int l,int r,int f){
    if(dp[l][r][f]!=-1)return dp[l][r][f];
    int &res=dp[l][r][f];res=2e9;
    int t=n-(r-l);
    if(f==0){
        res=min(res,dfs(l+1,r,0)+(A[l+1]-A[l])*t);
        res=min(res,dfs(l+1,r,1)+(A[r]-A[l])*t);
    }
    else {
        res=min(res,dfs(l,r-1,0)+(A[r]-A[l])*t);
        res=min(res,dfs(l,r-1,1)+(A[r]-A[r-1])*t);
    }
    return res;
}
int main(){
    scanf("%d%d",&n,&P);
    for(int i=1;i<=n;i++)scanf("%d",&A[i]);
    sort(A+1,A+n+1);
    memset(dp,-1,sizeof(dp));
    for(int i=1;i<=n;i++)dp[i][i][0]=dp[i][i][1]=abs(P-A[i])*n;
    printf("%d\n",min(dfs(1,n,1),dfs(1,n,0)));
    return 0;
}
