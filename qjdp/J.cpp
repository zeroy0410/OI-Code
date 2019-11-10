#include<bits/stdc++.h>
#define M 305
using namespace std;
int n,m,P,A[M],dp[M][M][2],ans;
int dfs(int l,int r,int f,int cnt){
    if(dp[l][r][f]!=-1)return dp[l][r][f];
    int &res=dp[l][r][f];res=2e9;
    int t=cnt-(r-l);
    if(f==0){
        res=min(res,dfs(l+1,r,0,cnt)+(A[l+1]-A[l])*t);
        res=min(res,dfs(l+1,r,1,cnt)+(A[r]-A[l])*t);
    }
    else {
        res=min(res,dfs(l,r-1,0,cnt)+(A[r]-A[l])*t);
        res=min(res,dfs(l,r-1,1,cnt)+(A[r]-A[r-1])*t);
    }
    return res;
}
int main(){
    scanf("%d%d",&n,&m);
    P=0;
    for(int i=1;i<=n;i++)scanf("%d",&A[i]);
    sort(A+1,A+n+1);
    for(int k=1;k<=n;k++){
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++)dp[i][i][0]=dp[i][i][1]=abs(P-A[i])*k;
        for(int i=1;i<=n;i++){
            if(i+k-1>n)break;
            ans=max(ans,k*m-min(dfs(i,i+k-1,0,k),dfs(i,i+k-1,1,k)));
        }
    }
    printf("%d\n",ans);
    return 0;
}
