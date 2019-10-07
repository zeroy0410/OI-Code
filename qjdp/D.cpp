#include<bits/stdc++.h>
#define M 55
using namespace std;
int n,dp[M][M][2];
char S[M];
bool check(int l,int r){
	int mid=(l+r)/2;
	for(int i=1;i<=mid-l+1;i++)if(S[l+i-1]!=S[mid+i])return 0;
	return 1;
}
int dfs(int l,int r,int f){
	if(dp[l][r][f]!=-1)return dp[l][r][f];
	dp[l][r][f]=r-l+1;
	int& res=dp[l][r][f];
	for(int i=l;i<r;i++){
		if(f==1)res=min(res,min(dfs(l,i,0),dfs(l,i,1))+1+min(dfs(i+1,r,0),dfs(i+1,r,1)));
		else res=min(res,dfs(l,i,0)+r-i);
		if((r-l+1)%2==0&&check(l,r)&&f==0)res=min(res,dfs(l,(l+r)>>1,0)+1);
	}
	return res;
}
int main(){
	scanf("%s",S+1);
	n=strlen(S+1);
	memset(dp,-1,sizeof(dp));
	printf("%d\n",min(dfs(1,n,0),dfs(1,n,1)));
	return 0;
}