#include<bits/stdc++.h>
#define M 500005
#define LL long long
using namespace std;
const int mod=1e9+7;
int n,q,A[M];
struct P10{
	LL dp[25][25];
	void solve(){
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=-1e18;
		for(int i=1;i<=n;i++)dp[i][i]=A[i];
		for(int len=2;len<=n;len++)
			for(int i=1;i<=n;i++){
				if(i+len-1>n)break;
				for(int k=i;k<i+len-1;k++)
					dp[i][i+len-1]=max(dp[i][i+len-1],dp[i][k]+2*dp[k+1][i+len-1]);
			}
		while(q--){
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",(dp[l][r]%mod+mod)%mod);
		}
	}
}p10;
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	p10.solve();
	return 0;
}
