#include<bits/stdc++.h>
using namespace std;
int n,m;
int G[25],cnt[1<<20],dp[1<<20];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		a--;b--;
		G[a]|=1<<b;G[b]|=1<<a;
	}
	for(int i=1;i<1<<n;i++)cnt[i]=cnt[i&(i-1)]+1;
	memset(dp,60,sizeof(dp));dp[0]=0;
	for(int i=0;i<(1<<n)-1;i++){
		int res=0;
		for(int j=0;j<n;j++)
			if(i&1<<j)
				res+=cnt[G[j]&(~i)];//能够连接且不在当前状态的server有几个
		for(int j=0;j<n;j++)
			if(!(i&1<<j))
				dp[i|1<<j]=min(dp[i|1<<j],dp[i]+res);
	}
	printf("%d\n",dp[(1<<n)-1]);
	return 0;
}
//因为是一个一个的往里加点，所以说，每个点由于加进去的先后不同，被计算到的贡献也会逐步累加
