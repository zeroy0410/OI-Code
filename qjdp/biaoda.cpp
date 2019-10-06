#include<bits/stdc++.h>
using namespace std;
char s[55];
int n;
int dp[55][55],val[55][55];
bool equ(int i,int j,int len){
	for(int q=0;q<len;q++)
		if(s[i+q]!=s[j+q])return 0;
	return 1;
}
int Get(int l,int r){
	if(l==r)return 1;
	if(val[l][r]!=-1)return val[l][r];
	int dp[55];
	for(int i=l;i<=r;i++)dp[i]=2e9;
	dp[l]=1;
	for(int i=l+1;i<=r;i++){
		dp[i]=min(dp[i],dp[i-1]+1);
		int len=i-l;
		if(i+len-1<=r&&equ(l,i,len))dp[i+len-1]=min(dp[i+len-1],dp[i-1]+1);
	}
	return val[l][r]=dp[r];
}
int dfs(int l,int r){
	if(l==r)return 1;
	if(dp[l][r]!=-1)return dp[l][r];
	dp[l][r]=Get(l,r);
	for(int i=l;i<r;i++)
		dp[l][r]=min(dp[l][r],dfs(l,i)+dfs(i+1,r)+1);
	return dp[l][r];
}
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	memset(dp,-1,sizeof(dp));
	memset(val,-1,sizeof(val));
	cout<<dfs(1,n)<<endl;
	return 0;
}
