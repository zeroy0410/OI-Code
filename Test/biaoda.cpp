#include<bits/stdc++.h>
#define M 400005
long long dp[1<<20],res;
int n,A[M],cnt[20],sum[20][20];
int main(){
	scanf("%d%*d",&n);
	memset(dp,60,sizeof dp);dp[0]=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]),A[i]--;
	for(int i=1;i<=n;i++){
		for(int j=0;j<20;j++)
			sum[A[i]][j]+=cnt[j];
		cnt[A[i]]++;
	}
	for(int i=0;i<(1<<20);i++)
		for(int j=0;j<20;j++)
			if(!(i&(1<<j))){
				res=0;
				for(int k=0;k<20;k++)
					if(i&(1<<k))res+=sum[k][j];
				dp[i|(1<<j)]=std::min(dp[i|(1<<j)],res+dp[i]);
			}
	printf("%lld\n",dp[(1<<20)-1]);
	return 0;
}
