#include<bits/stdc++.h>
#define M 3005
using namespace std;
int n,m,T;
struct node{
	int l,r,w;
	bool operator < (const node& res)const{
		if(l!=res.l)return l<res.l;
		return r<res.r;
	}
}A[M];
struct Pshui{
	int dp[M][M],kk[M];
	bool check(int x){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n+1;j++)
				dp[i][j]=0;
		for(int i=1;i<=n;i++){
			if(A[i].w<=x)
				dp[i][i]=A[i].r;
		}
		if(A[n].l==1&&dp[n][n]>=m)return 1;
		for(int i=n-1;i>=1;i--){
			if(A[i].w>x)continue;
			for(int j=i+1;j<=n;j++){
				if(A[j].l==A[i].r+1&&A[j].w<=x&&A[i].w<=x)
					dp[i][j]=max(dp[i][j],dp[j][j]);
				else if(A[j].l<=A[i].r){
					if(A[j].w+A[i].w<=x)
						dp[i][j]=max(dp[i][j],max(A[j].r,dp[j][max(j,kk[i])]));
				}
				else if(A[j].l>A[i].r+1)break;
			}
			for(int j=n-1;j>=i;j--)
				dp[i][j]=max(dp[i][j],dp[i][j+1]);
			if(A[i].l==1&&dp[i][i]>=m)return 1;
		}
		return dp[1][1]>=m;
	}
	void solve(){
		sort(A+1,A+n+1);
		int mx=0;
		for(int i=1;i<=n;i++)
			mx=max(mx,A[i].w);
		if(A[1].l>1){puts("-1");return;}
		memset(kk,0,sizeof(kk));
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++)
				if(A[j].l>A[i].r){
					kk[i]=j;
					break;
				}
			if(kk[i]==0)kk[i]=n+1;
		}
		int l=0,r=mx*2,ans=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)){ans=mid;r=mid-1;}
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
}pshui;
int main(){
//	freopen("intervals.in","r",stdin);
//	freopen("intervals.out","w",stdout);
	scanf("%d",&T);
	for(int _=1;_<=T;_++){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d%d%d",&A[i].l,&A[i].r,&A[i].w);
			A[i].l=max(A[i].l,1);
			A[i].r=min(A[i].r,m);
		}
		pshui.solve();
	}
	return 0;
}
