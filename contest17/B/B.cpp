#include<bits/stdc++.h>
#define M 75
using namespace std;
int n,K,tmp[M],sum[M];
struct node{
	int d,v,f;
	bool operator < (const node& res)const{
		return d<res.d;
	}
}A[M];
int dp[M][M][M];
int dfs(int l,int r,int w){
	if(l>r)return 0;
	if(~dp[l][r][w])return dp[l][r][w];
	int &res=dp[l][r][w];res=1e9;
	for(int i=l;i<=r;i++){
		res=min(res,dfs(l,i-1,w)+dfs(i+1,r,w)+sum[r]-sum[l-1]+K);
		if(w<=A[i].v)res=min(res,dfs(l,i-1,A[i].v)+dfs(i+1,r,A[i].v)+sum[r]-sum[l-1]);
	}
	return res;
}
int main(){
	freopen("treapmod.in","r",stdin);
	freopen("treapmod.out","w",stdout);
	memset(dp,-1,sizeof(dp));
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++)scanf("%d",&A[i].d);
	for(int i=1;i<=n;i++)scanf("%d",&A[i].v),tmp[i]=A[i].v;
	for(int i=1;i<=n;i++)scanf("%d",&A[i].f);
	sort(tmp+1,tmp+n+1);
	for(int i=1;i<=n;i++)A[i].v=lower_bound(tmp+1,tmp+n+1,A[i].v)-tmp;
	sort(A+1,A+n+1);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+A[i].f;
	printf("%d\n",dfs(1,n,1));
	return 0;
}
