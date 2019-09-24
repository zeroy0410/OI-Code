#include<cstdio>
#include<algorithm>
#define LL long long
using namespace std;
LL mod=1e9+7;const int N=110;
LL dp[N][N];LL c[N][N];
LL siz[N];int n;LL res;
char mde[N];
void dfs(int x){
	for(int v=2*x;v<=min(n,2*x+1);v++){
		dfs(v);
		if(mde[v]=='>'){
			for(int k=siz[x]+siz[v];k>=1;k--){
				LL sum=0;
				for(int i=1;i<=min(siz[x],(LL)k);i++){
					for(int j=k-i+1;j<=siz[v];j++){
						LL a=(dp[x][i]*dp[v][j])%mod;
						LL b=(c[i-1][k-1]*c[siz[x]-i][siz[x]+siz[v]-k])%mod;
						a=(a*b)%mod;
						sum=(sum+a)%mod;
					}
				}
				dp[x][k]=sum;
			}
		}
		else{
			for(int k=siz[x]+siz[v];k>=1;k--){
				LL sum=0;
				for(int i=1;i<=min(siz[x],(LL)k);i++){
					for(int j=1;j<=min((LL)k-i,siz[v]);j++){
						LL a=(dp[x][i]*dp[v][j])%mod;
						LL b=(c[i-1][k-1]*c[siz[x]-i][siz[x]+siz[v]-k])%mod;
						a=(a*b)%mod;sum=(sum+a)%mod;
					}
				}
				dp[x][k]=sum;
			}
		}
		siz[x]+=siz[v];
	}
}
int main(){
	scanf("%d",&n);
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		c[0][i]=1;c[i][i]=1;
		for(int j=1;j<i;j++)
			c[j][i]=(c[j][i-1]+c[j-1][i-1])%mod;
	}
	scanf("%s",mde+2);
	for(int i=1;i<=n;i++){
		dp[i][1]=1;
		siz[i]=1;
	}
	dfs(1);
	for(int i=1;i<=n;i++)res=(res+dp[1][i])%mod;
	printf("%lld",res);
	return 0;
}
