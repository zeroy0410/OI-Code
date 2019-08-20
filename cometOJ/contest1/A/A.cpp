#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=1e9+7;
LL n;
struct P70{
	LL dp[1000005];
	void solve(){
		dp[1]=1;dp[2]=2;dp[3]=3;dp[4]=4;dp[5]=6;dp[6]=9;
		for(int i=7;i<=n;i++){
			if((i-6)%3==0)dp[i]=dp[i-3]*3%mod;
			else dp[i]=dp[i-2]*2%mod;
		}
		printf("%lld\n",dp[n]);
	}
}p70;
struct P100{
	struct Matrix{
		LL a[3][3];
		void clear(){memset(a,0,sizeof(a));}
		Matrix operator *(const Matrix &_)const{
			Matrix res;
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					res.a[i][j]=0;
					for(int k=0;k<3;k++){
						res.a[i][j]=(res.a[i][j]+a[i][k]*_.a[k][j]%mod)%mod;
					}
				}
			}
			return res;
		}
	}Ma,F_d;
	Matrix qkpow(Matrix a,LL b){
		Matrix res;res.clear();
		for(int i=0;i<3;i++)res.a[i][i]=1;
		while(b){if(b&1)res=res*a;a=a*a;b>>=1;}
		return res;
	}
	void solve(){
		Ma.a[1][0]=2;
		Ma.a[2][1]=2;
		Ma.a[2][2]=3;
		F_d.a[0][0]=4;F_d.a[0][1]=6;F_d.a[0][2]=9;
		// F_d=F_d*Ma*Ma;
		LL ned=n-6;
		if(n%3==0)ned=ned/3;
		else ned=ned/3+1;
		Ma=qkpow(Ma,ned);
		F_d=F_d*Ma;
		int pos=(n-1)%3;
		printf("%lld\n",F_d.a[0][pos]);
	}
}p100;
int main(){
	scanf("%lld",&n);
	if(n<=1000000)p70.solve();
	else p100.solve();
	return 0;
}