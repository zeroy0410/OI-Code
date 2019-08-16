#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,K,P;
struct P50{
	LL fib[55];
	void solve(){
		fib[1]=fib[2]=1;
	    for(int i=3;i<=n;i++){
	    	fib[i]=fib[i-1]+fib[i-2];
	    	if(fib[i]%K==1)fib[i]--;
	    }
	    printf("%lld\n",fib[n]%P);
	}
}p50;
int main(){
//    freopen("rabbits.in","r",stdin);
//    freopen("rabbits.out","w",stdout);
    scanf("%lld%lld%lld",&n,&K,&P);
    if(n<=50)p50.solve();
    return 0;
}
