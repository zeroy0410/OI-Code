#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
const int mod=1e9+7;
int n,A[M];
void Add(LL &x,LL y){
	x+=y;
	if(x>=mod)x-=mod;
	if(x<0)x+=mod;
}
struct P40{
	LL dp[105][105];
	void solve(){
		LL ans=0;
		for(int i=1;i<=A[1];i++){
			memset(dp,0,sizeof(dp));
			dp[1][i]=1;
			for(int j=2;j<=n;j++){
				LL sum=0;
				for(int k=1;k<=A[j-1];k++)
					Add(sum,dp[j-1][k]);
				for(int k=1;k<=A[j];k++){
					dp[j][k]=sum;
					Add(dp[j][k],-dp[j-1][k]);
				}
			}
			for(int k=1;k<=A[n];k++)
				if(k!=i)Add(ans,dp[n][k]);
		}
		printf("%lld\n",ans);
	}
}p40;
struct P60{
	int mi,pos;
	int B[M],bc;
	LL dp[M];
	void solve(){
		mi=2e9;bc=0;
		for(int i=1;i<=n;i++)
			if(A[i]<mi){mi=A[i];pos=i;}
		for(int i=pos;i<=n;i++)B[++bc]=A[i];
		for(int i=1;i<pos;i++)B[++bc]=A[i];
		dp[0]=1;dp[1]=B[1];
		for(int i=2;i<=n;i++){
			mi=B[i];
			for(int j=i-1;j>=0;j--){
				Add(dp[i],dp[j]*mi*(((i-j)&1)?1:-1));
				mi=min(B[j],mi);
			}
		}
		for(int i = 1; i <= n; i++) printf("%lld\n", dp[i]);
		LL ans=0;
		for(int i=2;i<=n;i++){
			Add(ans,dp[i]*(((n-i)&1)?-1:1));
		}
		printf("%lld\n",ans);
	}
}p60;
struct P100{
	int mi,pos;
	int B[M],bc;
	LL dp[M],sum[M];
	struct node{
		int l,r;
		LL x;
	}stk[M];
	int top;
	LL S(int l,int r){
		if(l==0)return sum[r];
		return ((sum[r]-sum[l-1])%mod+mod)%mod;
	}
	LL tmp=0;
	void solve(){
		mi=2e9;bc=0;
		for(int i=1;i<=n;i++)
			if(A[i]<mi){mi=A[i];pos=i;}
		for(int i=pos;i<=n;i++)B[++bc]=A[i];
		for(int i=1;i<pos;i++)B[++bc]=A[i];
		dp[0]=1;dp[1]=B[1];sum[0]=-1;sum[1]=B[1]-1;stk[++top]=(node){0,0,B[1]};tmp=S(0,0)*B[1]%mod;
		for(int i=2;i<=n;i++){
			while(top&&B[i]<stk[top].x){
				Add(tmp,-S(stk[top].l,stk[top].r)*stk[top].x%mod);
				top--;
			}
			int l,r;
			if(top==0)l=1;else l=stk[top].r+1;
			r=i-1;
			Add(tmp,S(l,r)*B[i]%mod);
			stk[++top]=(node){l,r,B[i]};
			dp[i]=((tmp*((i&1)?-1:1))%mod+mod)%mod;
			sum[i]=((sum[i-1]+dp[i]*(i&1?1:-1))%mod+mod)%mod;
		}
		LL ans=0;
		for(int i=2;i<=n;i++){
			Add(ans,dp[i]*(((n-i)&1)?-1:1));
		}
		printf("%lld\n",ans);
	}
}p100;
int main(){
//	freopen("candy.in","r",stdin);
//	freopen("candy.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	p60.solve();
	return 0;
}
