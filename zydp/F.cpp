#include<bits/stdc++.h>
#define M 20
#define LL long long
using namespace std;
int n,K,A[M];
LL dp[1<<16][16];
int main(){
	scanf("%d%d",&n,&K);
	for(int i=0;i<n;i++)scanf("%d",&A[i]);
	for(int i=0;i<n;i++)dp[1<<i][i]=1;
	for(int i=0;i<1<<n;i++){
		for(int j=0;j<n;j++){
			if(dp[i][j]==0)continue;
			if(!(i&1<<j))continue;
			for(int k=0;k<n;k++){
				if(i&1<<k)continue;
				if(abs(A[k]-A[j])<=K)continue;
				dp[i|1<<k][k]+=dp[i][j];
			}
		}
	}
	LL ans=0;
	for(int i=0;i<n;i++)
		ans+=dp[(1<<n)-1][i];
	printf("%lld\n",ans);
	return 0;
}
