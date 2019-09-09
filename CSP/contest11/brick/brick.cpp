#include<stdio.h>
#include<algorithm>
#include<cstring>
#define M 1000005
using namespace std;
int n,c,A[M];
int dp[1005][1005],mx;//pos,height
struct Pbl{
	struct BIT1{
		int C[1005];
		void clear(){
			memset(C,60,sizeof(C));
		}
		void add(int x,int d){
			x++;
			while(x<=mx+1){
				C[x]=min(C[x],d);
				x+=(x&-x);
			}
		}
		int sum(int x){
			x++;int res=1e9;
			while(x){
				res=min(res,C[x]);
				x-=(x&-x);
			}
			return res;
		}
	}T1;
	struct BIT2{
		int C[1005];
		void clear(){
			memset(C,60,sizeof(C));
		}
		void add(int x,int d){
			x++;
			while(x){
				C[x]=min(C[x],d);
				x-=(x&-x);
			}
		}
		int sum(int x){
			x++;int res=1e9;
			while(x<=mx+1){
				res=min(res,C[x]);
				x+=(x&-x);
			}
			return res;
		}
	}T2;
	void solve(){
		mx=0;
		memset(dp,60,sizeof(dp));
		for(int i=1;i<=n;i++)
			mx=max(mx,A[i]);
		T1.clear();T2.clear();
		for(int i=0;i<=mx;i++){
			dp[0][i]=0;
			T1.add(i,dp[0][i]-c*i);
			T2.add(i,dp[0][i]+c*i);
		}
		int ans=1e9;
		for(int i=1;i<=n;i++){
			for(int j=A[i];j<=mx;j++){
				dp[i][j]=min(dp[i][j],T1.sum(j)+c*j+(j-A[i])*(j-A[i]));
				dp[i][j]=min(dp[i][j],T2.sum(j)-c*j+(j-A[i])*(j-A[i]));
				if(i==n)
					ans=min(ans,dp[i][j]);
			}
			T1.clear();T2.clear();
			for(int j=A[i];j<=mx;j++){
				T1.add(j,dp[i][j]-c*j);
				T2.add(j,dp[i][j]+c*j);
			}
		}
		printf("%d\n",ans);
	}
}pbl;
int main(){
	freopen("brick.in","r",stdin);
	freopen("brick.out","w",stdout);
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	pbl.solve();
	return 0;
}
