#include<bits/stdc++.h>
#define M 4005
#define LL long long
using namespace std;
int n;
LL A[M],dp[M][M];
LL dfs(int l,int r){
	if(l>r)return 0;
	if(dp[l][r]!=-1)return dp[l][r];
	if(l==r)return dp[l][r]=A[l];
	if(l+1==r)return dp[l][r]=max(A[l],A[r]);
	LL res=0;
	if(A[l+1]>A[r])res=max(res,A[l]+dfs(l+2,r));
	else res=max(res,A[l]+dfs(l+1,r-1));
	if(A[r-1]>A[l])res=max(res,A[r]+dfs(l,r-2));
	else res=max(res,A[r]+dfs(l+1,r-1));
	return dp[l][r]=res;
}
int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),A[n+i]=A[i];
	LL ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,dfs(i,i+n-1));
	printf("%lld\n",ans);
	return 0;
}
