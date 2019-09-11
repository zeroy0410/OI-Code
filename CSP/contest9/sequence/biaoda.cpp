#include<bits/stdc++.h>
using namespace std;
const int M=2005;
const int P=152076289;
int n,m,k;
long long Fact[M],S[M][M],dp[M][M],Sm[M];
void Solve(){
	Fact[0]=1;for(int i=1;i<=n;i++)Fact[i]=Fact[i-1]*i%P;
	S[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=i;j++)
			S[i][j]=(S[i-1][j-1]+S[i-1][j]*j)%P;
	dp[1][0]=1;long long ans=1;
	for(int i=2;i<=n;i++){
		Sm[0]=dp[i-1][0];for(int j=1;j<=m;j++)Sm[j]=(Sm[j-1]+dp[i-1][j])%P;
		for(int j=1;j<=m;j++){
			dp[i][j]=Sm[j-1]-(j-k>=1?Sm[j-k-1]:0);
			ans=(ans+S[n][i]*Fact[i]%P*dp[i][j])%P;
		}
	}
	ans=(ans%P+P)%P;
	printf("%lld\n",ans);
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	Solve();
	return 0;
}
