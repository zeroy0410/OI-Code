#include<bits/stdc++.h>
#define LL long long
#define M 10005
using namespace std;
bool mm1;
int n,W,K;
struct node{int a,b;}A[M];
struct P30{
	int dp[2][5005];
	void solve(){
		int ans=1e9;
		for(int i=1;i<=n;i++){
			int cur=0;
			memset(dp[cur],60,sizeof(dp[cur]));int inf=dp[cur][0];
			dp[cur][0]=0;
			for(int j=i;j<=n;j++){
				cur=!cur;
				for(int k=0;k<=W;k++)dp[cur][k]=dp[!cur][k];
				for(int k=0;k<=W-A[j].a;k++)
					if(dp[!cur][k]!=inf)
						dp[cur][k+A[j].a]=min(dp[cur][k+A[j].a],dp[!cur][k]+A[j].b);
				if(dp[cur][W]<=K){
					ans=min(ans,j-i+1);
					break;
				}
			}
		}
		if(ans==1e9)puts("-1");
		else printf("%d\n",ans);
	}
}p30;
struct P100{
	int dp[10005][5005];
	int DP[5005];
	int ans;
	void calc(int l,int r){
		if(l==r){
			if(A[l].a==W)ans=1;
			return;
		}
		int mid=(l+r)>>1;
		memset(dp[mid+1],60,sizeof(dp[mid+1]));int inf=dp[mid+1][0];
		dp[mid+1][0]=0;
		for(int i=mid;i>=l;i--){
			for(int k=0;k<=W;k++)dp[i][k]=dp[i+1][k];
			for(int k=0;k<=W-A[i].a;k++)
				if(dp[i+1][k]!=inf)
					dp[i][k+A[i].a]=min(dp[i][k+A[i].a],dp[i+1][k]+A[i].b);
		}
		int cur=l;
		memset(DP,60,sizeof(DP));
		DP[0]=0;
		for(int i=mid+1;i<=r;i++){
			for(int k=W;k>=A[i].a;k--)
				DP[k]=min(DP[k],DP[k-A[i].a]+A[i].b);
			while(cur<=mid){
				bool fl=0;
				for(int k=0;k<=W;k++){
					if(DP[W-k]==inf||dp[cur][k]==inf)continue;
					if(dp[cur][k]+DP[W-k]<=K){
						ans=min(ans,i-cur+1);
						fl=1;
						break;
					}
				}
				if(fl)cur++;
				else break;
			}
		}
		calc(l,mid);calc(mid+1,r);
	}
	void solve(){
		ans=1e9;
		calc(1,n);
		if(ans==1e9)puts("-1");
		else printf("%d\n",ans);
	}
}p100;
bool mm2;
int main(){
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
//	printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
	cin>>n>>W>>K;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&A[i].a,&A[i].b);
	p100.solve();
	return 0;
}
