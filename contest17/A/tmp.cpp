#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
const LL inf=1e18;
int n,L,P,T,A[M];
char S[35];
LL sum[M];
LL qkpow(LL a,int b){
	LL res=1;
	while(b){
		if(b&1)res=res*a;
		a=a*a;
		b>>=1;	
	}
	return res;
}
struct P30{
	LL dp[M];
	void solve(){
		for(int i=1;i<=n;i++){dp[i]=inf;}
		dp[0]=0;
		for(int i=1;i<=n;i++)
			for(int j=0;j<i;j++){
				LL tmp;tmp=abs(sum[i]-sum[j]+i-j-1-L);
				dp[i]=min(dp[i],dp[j]+qkpow(tmp,P));
			}
		if(dp[n]>1e18)puts("Too hard to arrange");
		else printf("%lld\n",dp[n]);
		puts("--------------------");
	}
}p30;
//struct P50{
//	Num dp[M];
//	struct node{
//		Num x,y;
//	}stk[M];
//	int top;
//	void solve(){
//		for(int i=1;i<=n;i++){dp[i].x=inf;dp[i].f=1;}
//		dp[0].x=0;dp[0].f=0;stk[++top]=(node){dp[0]+Sqr(sum[j]+j)};
//		
//	}
//}p50;
int main(){
//	freopen("poet.in","r",stdin);
//	freopen("poet.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&L,&P);
		for(int i=1;i<=n;i++){
			scanf("%s",S);
			A[i]=strlen(S);
			sum[i]=sum[i-1]+A[i];
		}
		p30.solve();
	}
	return 0;
}
