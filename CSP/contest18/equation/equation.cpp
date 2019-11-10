#include<stdio.h>
#include<algorithm>
#define LL long long
using namespace std;
const int mod=998244353;
LL l1,l2,r1,r2,m;
struct P30{
	void solve(){
		LL ans=0;
		for(LL i=l1;i<=r1;i++){
			for(LL j=l2;j<=r2;j++)
				if((i^j)%m==0)ans++;
		}
		printf("%lld\n",ans);
	}
}p30;
struct P100{
	LL calc(LL l,LL r){
		if(l==0)return r/m+1;
		return r/m-(l-1)/m;
	}
	LL query(LL l,LL r){
		LL ans=0;
		for(LL i=l;i;i-=(i&-i)){
			for(LL j=r;j;j-=(j&-j)){
				LL mx=max(i&-i,j&-j);
				LL mi=min(i&-i,j&-j);
				LL L=i&(i-1),R=j&(j-1);
				LL res=(L^R)&(~(mx-1));
				ans=(ans+calc(res,res+mx-1)%mod*(mi%mod))%mod;
			}
		}
		return ans;
	}
	void solve(){
		r1++;r2++;
		printf("%lld\n",(query(r1,r2)-query(r1,l2)-query(l1,r2)+query(l1,l2)+mod+mod)%mod);
	}
}p100;
int main(){
	scanf("%lld%lld%lld%lld%lld",&l1,&r1,&l2,&r2,&m);
	p100.solve();
	return 0;
}
