#include<bits/stdc++.h>
#define M 35
using namespace std;
int n,A[M],S;
double h[M],K,C,dp[M][M][M];
double dfs(int l,int r,int d){
	if(dp[l][r][d]!=-1)return dp[l][r][d];
	double& res=dp[l][r][d];res=2e9;
	double dj=K*(d+1)+C;
	for(int i=l;i<=r;i++){
		double tmp=0;
		if(i>l)tmp+=dfs(l,i-1,d+1);
		if(i<r)tmp+=dfs(i+1,r,d+1);
		tmp+=dj*h[i];
		res=min(res,tmp);
	}
	return res;
}
int main(){
	scanf("%d%lf%lf",&n,&K,&C);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),S+=A[i];
	for(int i=1;i<=n;i++)h[i]=1.0*A[i]/S;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=0;k<=n;k++)
				dp[i][j][k]=-1;
	printf("%.3lf\n",dfs(1,n,0));
	return 0;
}
