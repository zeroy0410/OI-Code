#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
int n,T,A[M],cnt[M<<1],dp[M<<1];
LL ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(dp,0,sizeof(dp));
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++)
			scanf("%d",&A[i]),cnt[A[i]]++,dp[A[i]]++;
		LL ans=0;
		for(int i=1;i<(1<<20);i<<=1){
			for(int j=0;j<(1<<20);j++){
				if(i&j)dp[j]+=dp[i^j];
			}
		}
		for(int i=0;i<=1e6;i++){
			int t=i;
			ans+=cnt[t]*(cnt[t]-1)/2;
			ans+=(dp[t]-cnt[t])*cnt[t];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
