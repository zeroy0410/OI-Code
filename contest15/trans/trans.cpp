#include<bits/stdc++.h>
#define M 65 
using namespace std;
int n,m,h[M],tt;
double k,dp[M][M][M],K[M],C[M];
int fa[M],D;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;	
}
void dfs(int x){
	for(int d=0;d<=n;d++)
		for(int i=0;i<=m;i++)
			dp[x][i][d]=C[x]*K[d];
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		dfs(u);
		for(int d=0;d<=n;d++){
			for(int c=m;c>=0;c--){
				double res=-1e18;
				for(int cc=0;cc<=c-1;cc++)res=max(res,dp[x][cc][d]+dp[u][c-cc-1][1]);
				for(int cc=0;cc<=c;cc++)res=max(res,dp[x][cc][d]+dp[u][c-cc][d+1]);
				dp[x][c][d]=res;
			}
		}
	}
	if(x==fa[1])for(int d=0;d<=n;d++)if(d!=D)for(int c=0;c<=m;c++)dp[x][c][d]=-1e18;
}
int main(){
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	scanf("%d%d%lf",&n,&m,&k);K[0]=1;
	for(int i=1;i<=n;i++)K[i]=K[i-1]*k;
	for(int i=1;i<=n;i++){
		scanf("%d",&fa[i]);
		if(i!=1)Add(fa[i],i);
	}
	for(int i=1;i<=n;i++)scanf("%lf",&C[i]);
	double ans=-1e18;
	for(D=1;D<=n-1;D++){
		dfs(1);
		double res=0;
		for(int i=0;i<=m;i++)res=max(res,dp[1][i][0]);
		ans=max(ans,res/(1.0-K[D+1]));
	}
	printf("%.2f\n",ans);
	return 0;
}
