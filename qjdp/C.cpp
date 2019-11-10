#include<bits/stdc++.h>
#define M 205
using namespace std;
int n,A[M],dp[M][M][M],tot;
int col[M],v[M];
int pf(int x){return x*x;}
int dfs(int l,int r,int k){
	if(l==r)return pf(v[r]+k);
	if(dp[l][r][k]!=-1)return dp[l][r][k];
	int res=dfs(l,r-1,0)+pf(v[r]+k);
	for(int i=l;i<r;i++){
		if(col[i]==col[r])
			res=max(res,dfs(l,i,v[r]+k)+dfs(i+1,r-1,0));
	}
//	cout<<l<<' '<<r<<' '<<k<<' '<<res<<endl;
	return dp[l][r][k]=res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	int c=0;A[n+1]=-1;
	for(int i=1;i<=n;i++){
		c++;
		if(A[i]!=A[i+1]){
			col[++tot]=A[i];
			v[tot]=c;
			c=0;
		}
	}
	memset(dp,-1,sizeof(dp));
	printf("%d\n",dfs(1,tot,0));
	return 0;
}
