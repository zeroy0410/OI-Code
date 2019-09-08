#include<bits/stdc++.h>
using namespace std;
bool mm1;
int n,R,Q,T;
const double eps=1e-10;
struct P60{
	double dp[10005][25][6];
	double p;
	double dfs(int i,int j,int k){
		if(i==n+1||k==0)return 0;
		if(dp[i][j][k]!=-1)return dp[i][j][k];
		double res=0;
		res+=(dfs(i+1,min(j+1,R),min(Q,k+1))+min(j+1,R))*p;
		res+=dfs(i+1,0,k-1)*(1-p);
		return dp[i][j][k]=res;
	}
	double calc(double mid){
		p=mid;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=R;j++)
				for(int k=0;k<=Q;k++)
					dp[i][j][k]=-1;
		return dfs(1,0,Q);
	}
	void solve(){
		double l=0,r=1,ans=-1;
		for(int _=1;_<=50;_++){
			double mid=(l+r)/2;
			double res=calc(mid);
			if(res>T+eps){ans=r=mid;}
			else l=mid;
		}
		if(ans==-1)puts("Impossible.");
		else printf("%.6lf\n",ans);
	}
}p60;
bool mm2;
int main(){
	freopen("bet.in","r",stdin);
	freopen("bet.out","w",stdout);
//	printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
	scanf("%d%d%d%d",&n,&R,&Q,&T);
	if(n<=10000)p60.solve();
	else puts("Impossible.");
	return 0;
}
