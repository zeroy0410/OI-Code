#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
const int mod=998244353;
int n,m;
LL A[M],B[M];
struct BIT{
	LL C[M];
	void add(int x,LL d){
		x++;
		while(x<=n+1){
			C[x]=(C[x]+d)%mod;
			x+=(x&-x);
		}
	}
	LL sum(int x){
		x++;
		LL res=0;
		while(x){
			res=(res+C[x])%mod;
			x-=(x&-x);
		}
		return res;
	}
}Tr[4];
LL dp[M][5];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&A[i]);
		B[i]=A[i];
	}
	sort(B+1,B+n+1);
	m=unique(B+1,B+n+1)-B-1;
	for(int i=1;i<=n;i++)
		A[i]=lower_bound(B+1,B+m+1,A[i])-B;
	// for(int i=1;i<=n;i++)
	// 	printf("%d\n",A[i]);
	for(int i=1;i<=n;i++)dp[i][0]=1;
	LL ans=0;
	for(int j=1;j<=4;j++){
		for(int i=1;i<=n;i++){
			if(j==1||j==3)
				dp[i][j]=((Tr[j-1].sum(n)-Tr[j-1].sum(A[i]))%mod+mod)%mod;
			else 
				dp[i][j]=Tr[j-1].sum(A[i]-1);
			if(j==4)ans=(ans+dp[i][j])%mod;
			Tr[j-1].add(A[i],dp[i][j-1]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}