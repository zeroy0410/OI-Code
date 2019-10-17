#include<bits/stdc++.h>
#define M 3005
using namespace std;
int n,q,tot,p[M],l[M],r[M],x[3*M],pos[M];
long long dp[M][3*M],ans;
bool cmp(int a,int b) {
	if(p[a]==p[b])return l[a]<l[b];
	return p[a]<p[b];
}
int main() {
	freopen("bug.in","r",stdin);
	freopen("bug.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		scanf("%d%d%d",&p[i],&l[i],&r[i]);
		x[++tot]=p[i];
		x[++tot]=p[i]-l[i];
		x[++tot]=p[i]+r[i];
	}
	sort(x+1,x+tot+1);
	q=unique(x+1,x+tot+1)-x-1;
	for(int i=1; i<=n; i++) {
		r[i]=lower_bound(x+1,x+q+1,p[i]+r[i])-x;
		l[i]=lower_bound(x+1,x+q+1,p[i]-l[i])-x;
		p[i]=lower_bound(x+1,x+q+1,p[i])-x;
	}
	for(int i=1;i<=n;i++)pos[i]=i;
	sort(pos+1,pos+n+1,cmp);
	for(int i=1;i<=n;i++){
		int t=pos[i];
		dp[i][p[t]]=max(dp[i][p[t]],dp[i-1][l[t]]+x[p[t]]-x[l[t]]);
		dp[i][r[t]]=max(dp[i][r[t]],dp[i-1][p[t]]+x[r[t]]-x[p[t]]);
		int mx=p[t];
		for(int j=i-1;j>=0;j--){
			dp[i][mx]=max(dp[i][mx],x[mx]-x[l[t]]+dp[j][l[t]]);
			mx=max(mx,r[pos[j]]);
		}
		for(int j=q;j>=2;j--)dp[i][j-1]=max(dp[i][j-1],dp[i][j]-(x[j]-x[j-1]));
		for(int j=1;j<=q;j++)dp[i][j]=max(dp[i][j-1],max(dp[i][j],dp[i-1][j]));
	}
	for(int i=1;i<=n;i++)
		for(int j=1; j<=q; j++)ans=max(ans,dp[i][j]);
	printf("%lld\n",ans);
	return 0;
}
