#include<stdio.h>
#include<algorithm>
#define M 100005
#define LL long long
using namespace std;
const int mod=998244353;
int T,n,m,K;
LL A[M],tmp[M];
int pre(int x){if(x==1)return n;else return x-1;}
int nxt(int x){if(x==n)return 1;else return x+1;}
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
struct P30{
	bool mark[M];
	int wk[M];
	LL tot,ans;
	void dfs(int x){
		if(x>m){
			for(int i=1;i<=n;i++)tmp[i]=A[i];
			for(int i=1;i<=m;i++){
				tmp[pre(wk[i])]+=tmp[wk[i]];
				tmp[nxt(wk[i])]+=tmp[wk[i]];
				tmp[wk[i]]=0;
			}
			if(tmp[1]>=K)ans++;
			tot++;
			return;
		}
		for(int i=1;i<=n;i++){
			if(!mark[i]){
				mark[i]=1;
				wk[x]=i;
				dfs(x+1);
				mark[i]=0;
			}
		}
	}
	void solve(){
		ans=tot=0;
		dfs(1);
		printf("%lld\n",ans*qkpow(tot,mod-2)%mod);
	}
}p30;
struct P50{
	void solve(){

	}
}p50;
struct P70{
	LL fac[M],Ifac[M];
	void Init(){
		fac[0]=1;Ifac[0]=Ifac[1]=1;
		for(int i=1;i<M;i++)fac[i]=fac[i-1]*i%mod;
		for(int i=2;i<M;i++)Ifac[i]=Ifac[i-1]*qkpow(i,mod-2)%mod;
	}
	void solve(){
		Init();
		LL tot=fac[n]*Ifac[n-m]%mod;
		LL ans=fac[n-1]*Ifac[n-m-1]%mod;
		for(int i=1;i<=m;i++){
			ans=(ans+fac[n-2]*Ifac[n-m]%mod*(m-i)%mod*2%mod)%mod;
			ans=((ans-fac[n-3]*Ifac[n-m]%mod*(m-i)%mod*(m-i-1)%mod)%mod+mod)%mod;
		}
		printf("%lld\n",ans*qkpow(tot,mod-2)%mod);
	}
}p70;
int main(){
	freopen("fake.in","r",stdin);
	freopen("fake.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&K);
		for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
		if(n<=9||m==1)p30.solve();
		else if(n==99998)p50.solve();
		else if(n==99999)p70.solve();
	}
	return 0;
}
