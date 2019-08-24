#include<bits/stdc++.h>
#define LL long long
#define M 1000005
using namespace std;
const int mod=998244353;
int n,A[M],cnt[M];
int pr[M],pc,ed;
bool mark[M];
void Init(){
	for(int i=2;i<=ed;i++){
		if(!mark[i])pr[++pc]=i;
		for(int j=1;j<=pc&&pr[j]*i<=ed;j++){
			mark[pr[j]*i]=1;
			if(i%pr[j]==0)break;
		}
	}
}
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int main(){
	ed=1e6;
	Init();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),cnt[A[i]]++;
	LL ans=1;
	for(int i=1;i<=pc;i++){
		for(LL k=pr[i];k<=ed;k*=pr[i]){
			LL res=0;
			for(int j=k;j<=ed;j+=k)
				res+=cnt[j];
//			if(res!=0)cout<<k<<' '<<res<<endl;
			ans=ans*qkpow(pr[i],res*(res-1)/2)%mod;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
