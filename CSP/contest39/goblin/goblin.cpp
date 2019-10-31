#include<bits/stdc++.h>
#define M 4205
#define LL long long
using namespace std;
bool mm1;
int n,mod;
struct P20{
	int mark[15];
	void solve(){
		for(int i=1;i<=n;i++)mark[i]=i;
		int ans=0;
		do{
			bool f=(mark[2]>mark[1]);
			bool fl=1;
			for(int i=3;i<=n;i++){
				if((mark[i]>mark[i-1])==f){
					fl=0;
					break;
				}
				f=(mark[i]>mark[i-1]);
			}
			ans+=fl;
		}while(next_permutation(mark+1,mark+n+1));
		printf("%d\n",ans%mod);
	}
}p20;
struct P100{
	LL dp[M][2];
	LL C[M][M];
	void Add(LL &x,LL y){
		x+=y;
		if(x>=mod)x-=mod;
	}
	void Init(){
		C[0][0]=1;
		for(int i=1;i<M;i++){
			C[i][0]=1;
			for(int j=1;j<=i;j++)
				C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	void solve(){
		Init();
		dp[0][0]=dp[0][1]=dp[1][1]=dp[1][0]=dp[2][0]=dp[2][1]=1;
		for(int i=3;i<=n;i++){
			for(int j=0;j<=i-1;j++){
				if(!(j&1))
					Add(dp[i][0],dp[j][0]*dp[i-j-1][1]%mod*C[i-1][j]%mod);
				else 
					Add(dp[i][1],dp[j][1]*dp[i-j-1][1]%mod*C[i-1][j]%mod);
			}
		}
		printf("%lld\n",(dp[n][0]+dp[n][1])%mod);
	}
}p100;
bool mm2;
int main(){
	freopen("goblin.in","r",stdin);
	freopen("goblin.out","w",stdout);
//	printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
	scanf("%d%d",&n,&mod);
	p100.solve();
	return 0;
}
