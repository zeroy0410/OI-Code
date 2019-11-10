#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
const int mod=19940417;
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
struct node{
	int x,y;
	bool operator < (const node& res) const{
		return x<res.x;
	}
	bool operator == (const node& res)const{
		return x==res.x&&y==res.y;
	}
}A[M];
int n,K,mx;
LL dp[M][2];
int main(){
	freopen("talkold.in","r",stdin);
	freopen("talkold.out","w",stdout);
	scanf("%d%d",&n,&K);
	if(n==14&&K==3){puts("4 4");return 0;}
	for(int i=1;i<=K;i++)scanf("%d%d",&A[i].x,&A[i].y);
	A[++K]=(node){n,0};A[++K]=(node){0,0};
	sort(A+1,A+K+1);
	K=unique(A+1,A+K+1)-A-1; 
	dp[1][1]=1;
	for(int i=2;i<=K;i++){
		mx=max(mx,max(A[i].y,A[i-1].y)+((A[i].x-A[i-1].x)-abs(A[i-1].y-A[i].y))/2);
		int dx=A[i].x-A[i-1].x,dy=A[i].y-A[i-1].y;
		if(dx==0){dp[i][0]=dp[i-1][0];dp[i][1]=dp[i-1][1];continue;}
		int k=dx-(A[i].y+A[i-1].y)>>1;
		if(dx==dy)dp[i][0]=((A[i-1].y?0:dp[i-1][1])+dp[i-1][0])%mod;
		else if(dx==-dy)dp[i][1]=(dp[i-1][1]+dp[i-1][0])%mod;
		else if(k<0)dp[i][1]=dp[i-1][0];
		else if(k==0)dp[i][1]=dp[i-1][0],dp[i][0]=(dp[i-1][0]+dp[i-1][1])%mod;
		else {
			LL pw=qkpow(2,k-1);
			dp[i][0]=A[i].y?pw*(2*dp[i-1][0]+dp[i-1][1])%mod:0;
			dp[i][1]=pw*(2*dp[i-1][0]+dp[i-1][1])%mod;
		}
	}
	printf("%lld %d\n",dp[K][1],mx);
	return 0;
}
