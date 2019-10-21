#include<bits/stdc++.h>
#define M 300005
using namespace std;
bool vis[M][20];
int n,m,K;
int dp[M],cnt[M],rk[M],tot,base;
int main(){
	//	freopen("set.in","r",stdin);
	//	freopen("set.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1,x;i<=m;i++){
		scanf("%d",&x);
		for(int j=0;j<n;j++)
			if(x&1<<j)
				vis[x][j]=1;
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<1<<n;j++)
			if(vis[j][i])
				for(int k=0;k<n;k++)
					if(!(j&1<<k))
						vis[j|1<<k][i]=1;
	memset(dp,-1,sizeof(dp));dp[0]=0;
	for(int i=0;i<1<<n;i++){
		cnt[i]=cnt[i>>1]+(i&1);
		if(dp[i]!=-1){
			for(int j=0;j<n;j++){
				if(!(i&1<<j)){
					if(!(K&1<<cnt[i])&&vis[i|1<<j][j])continue;
					dp[i|1<<j]=j;
				}
			}
		}
	}
	if(dp[(1<<n)-1]==-1){puts("-1");return 0;}
	tot=n-1;base=(1<<n)-1;
	while(base){
		rk[dp[base]]=tot--;
		base^=(1<<dp[base]);
	}
	base=(1<<n)-1;
	for(int i=1;i<=base;i++){
		tot=0;
		for(int j=0;j<n;j++)
			if(i&1<<j)
				tot=max(tot,rk[j]);
		printf("%d",(K&1<<tot)>0);
	}
	return 0;
}
