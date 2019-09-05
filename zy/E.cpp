#include<bits/stdc++.h>
#define M 1005
using namespace std;
int T,n,A[M],dp[M];
int main(){
	scanf("%d",&T);
	while(T--){
		memset(dp,60,sizeof(dp));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&A[i]);
		sort(A+1,A+n+1);
		if(n==1){printf("%d\n",A[1]);continue;}
		dp[2]=A[2];
		for(int i=3;i<=n;i++)
			dp[i]=min(dp[i],dp[i-1]+A[i]+A[1]),
			dp[i]=min(dp[i],dp[i-2]+A[i]+A[1]+A[2]*2);
		printf("%d\n",dp[n]);
	}
	return 0;
}
