#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=9990017;
LL n,m,B;
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
struct P10{
	LL C[1005][1005];
	void Init(){
		C[0][0]=1;
		for(int i=1;i<=1000;i++){
			C[i][0]=1;
			for(int j=1;j<=i;j++)
				C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	void solve(){
		Init();
		int ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				ans=(ans+C[gcd(i,j)][B])%mod;
		printf("%d\n",ans);
	}
}p10;
struct P100{
	void solve(){
		
	}
}p100;
int main(){
	freopen("fuwafuwatime.in","r",stdin);
	freopen("fuwafuwatime.out","w",stdout);
	scanf("%lld%lld%lld",&n,&m,&B);
	p10.solve();
	return 0;
}
