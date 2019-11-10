#include<bits/stdc++.h>
#define M 2005
#define LL long long
using namespace std;
const int mod=998244353;
int n,p[M][5],w[5][5];
LL pre[M][M],las[M][M],ans[M];
int main(){
	//	freopen("revolution.in","r",stdin);
	//	freopen("revolution.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=4;j++)
			scanf("%d",&p[i][j]);
	}
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			scanf("%d",&w[i][j]);
	for(int mx=1;mx<=4;mx++){
		memset(pre,0,sizeof(pre));
		memset(las,0,sizeof(las));
		pre[0][0]=1;las[n+1][0]=1;
		for(int i=1;i<=n;i++)
			for(int j=0;j<=i;j++){
				if(j==0)pre[i][j]=(pre[i-1][j]*(1-p[i][mx])%mod+mod)%mod;
				else pre[i][j]=((pre[i-1][j-1]*p[i][mx]%mod+pre[i-1][j]*(1-p[i][mx])%mod)%mod+mod)%mod;
			}
		for(int i=n;i>=1;i--)
			for(int j=0;j<=n-i+1;j++){
				if(j==0)las[i][j]=(las[i+1][j]*(1-p[i][mx])%mod+mod)%mod;
				else las[i][j]=((las[i+1][j-1]*p[i][mx]%mod+las[i+1][j]*(1-p[i][mx])%mod)%mod+mod)%mod;
			}
		for(int i=1;i<=n;i++)
			for(int j=n-i;j>=0;j--)
				las[i][j]=(las[i][j]+las[i][j+1])%mod;
		for(int i=1;i<=n;i++)
			for(int j=0;j<i;j++)
				for(int k=1;k<=4;k++)
					ans[i]=(ans[i]+pre[i-1][j]*p[i][k]%mod*w[mx][k]%mod*las[i+1][max(0,n/2+1-j-(mx==k))]%mod)%mod;
	}
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
