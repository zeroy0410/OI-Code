#include<bits/stdc++.h>
using namespace std;
int n,inf;
struct node{
	int h,t;
	bool operator < (const node& res)const{
		return h>res.h;
	}
}A[75];
int dp[2105][2105],sum[75];
void tomin(int& x,int y){if(y<x)x=y;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&A[i].h,&A[i].t);
	sort(A+1,A+n+1);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+A[i].t;
	memset(dp,0x3f,sizeof(dp));inf=dp[0][0];
	dp[0][0]=0;
	for(int i=2;i<=n;i++)
		for(int j=sum[i];j>=0;j--)
			for(int k=sum[i];k>=0;k--){
				if(A[i].t<j)tomin(dp[j][k],dp[j-A[i].t][k]);
				else if(A[i].t==j)tomin(dp[j][k],dp[0][k]+A[i].h);
				if(A[i].t<k)tomin(dp[j][k],dp[j][k-A[i].t]);
				else if(A[i].t==k)tomin(dp[j][k],dp[j][0]+A[i].h);
			}
	int ans=inf;
	for(int i=1;i<=2100;i++)
		for(int j=1;j<=2100;j++){
			if(dp[i][j]==inf)continue;
			int H=dp[i][j]+A[1].h;
			int W=max(sum[n]-i-j,max(i,j));
			tomin(ans,H*W);
		}
	printf("%d\n",ans);
	return 0;
}
