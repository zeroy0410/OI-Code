#include<bits/stdc++.h>
#define M 1005
using namespace std;
const int mod=19650827;
int n,A[M],dp[M][M][2];
void Add(int &x,int y){
	x+=y;
	if(x>=mod)x-=mod;
}
int dfs(int l,int r,int s){
	if(l==r)return s;
	if(dp[l][r][s]!=-1)return dp[l][r][s];
	dp[l][r][s]=0;
	if(s==0){
		if(A[l]<A[l+1])Add(dp[l][r][s],dfs(l+1,r,s));
		if(A[l]<A[r])Add(dp[l][r][s],dfs(l+1,r,!s));
	}
	else {
		if(A[r]>A[r-1])Add(dp[l][r][s],dfs(l,r-1,s));
		if(A[r]>A[l])Add(dp[l][r][s],dfs(l,r-1,!s));
	}
	return dp[l][r][s];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	memset(dp,-1,sizeof(dp));
	printf("%d\n",(dfs(1,n,0)+dfs(1,n,1))%mod);
	return 0;
}
