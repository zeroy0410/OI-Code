#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
int n,m,p,T;
LL x,A[M],B[M];
struct P100{
	LL qkpow(LL a,LL b){
		LL res=1;
		while(b){
			if(b&1)res=res*a%p;
			a=a*a%p;
			b>>=1;
		}
		return res;
	}
	void solve(){
		LL res1=0,res2=0;
		for(int i=1;i<=n;i++)res1=(res1^A[i]);
		for(int i=1;i<=m;i++)res2=(res2^B[i]);
		if(res1!=res2){
			puts("0");
			return;
		}
		printf("%lld\n",qkpow(qkpow(x+1,m-1),n-1));
	}
}p100;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%lld%d",&n,&m,&x,&p);
		for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
		for(int i=1;i<=m;i++)scanf("%lld",&B[i]);
		p100.solve();
	}
	return 0;
}
