#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int n,m;
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
LL calc(LL x,LL y){
	return x*qkpow(y,mod-2)%mod;
}
struct P50{
	LL _isone[3015];//此区间内的值是1的概率  
	LL* isone;
	void solve(){
		isone=_isone+3;
		for(int i=1,op,l,r;i<=m;i++){
			scanf("%d%d%d",&op,&l,&r);
			if(op==1){
				for(int k=l;k<=n;k++){
					LL p=calc(min(k-l+1,r-l+1),r-l+1);
					isone[k]=((1LL-isone[k]+mod)*p%mod+isone[k]*(1LL-p+mod)%mod)%mod;
				}
			}
			else {
				LL yb1=isone[r]*(1LL-isone[l-1]+mod)%mod+isone[l-1]*(1LL-isone[r]+mod)%mod;
				LL yb0=(isone[r]*isone[l-1]%mod+(1LL-isone[l-1]+mod)*(1LL-isone[r]+mod)%mod)%mod;
				LL xz1=isone[r-1]*(1LL-isone[l-2]+mod)%mod+isone[l-2]*(1LL-isone[r-1]+mod)%mod;
				LL xz0=(isone[r-1]*isone[l-2]%mod+(1LL-isone[l-2]+mod)*(1LL-isone[r-1]+mod)%mod)%mod;
				cout<<yb1<<' '<<yb2<<' '<<
				printf("%lld\n",(yb1*xz1%mod+yb0*xz0%mod)%mod);
			}
		}
	}
}p50;
int main(){
	freopen("bit.in","r",stdin);
	freopen("bit.out","w",stdout); 
	scanf("%d%d",&n,&m);
	p50.solve();
	return 0;
}
