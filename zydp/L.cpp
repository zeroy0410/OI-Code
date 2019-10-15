#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=1000000007;
int n,m,K;
LL dp[35][35][1<<9|5][9];
void Add(LL &x,LL y){
	x+=y;
	if(x>=mod)x-=mod;
}
int main(){
	scanf("%d%d%d",&n,&m,&K);
	dp[1][0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int k=0;k<1<<(K+1);k++){
				for(int l=0;l<K;l++){
					if(dp[i][j][k][l]){
						Add(dp[i][j][k][l+1],dp[i][j][k][l]);
						if(j+1<=m&&i-K+l>=1)
							Add(dp[i][j+1][k^(1<<K)^(1<<l)][l],dp[i][j][k][l]);
					}
				}
				if((!(k&1))&&dp[i][j][k][K])
					dp[i+1][j][k>>1][0]=dp[i][j][k][K]%mod;
			}
		}
	}
	printf("%lld\n",dp[n+1][m][0][0]);
	return 0;
}
