#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,p;
int main(){
	scanf("%lld%lld",&n,&p);
	for(int i=1;n-i*p>0;i++){
		LL tmp=n-i*p;
		if(__builtin_popcount(tmp)<=i){
			printf("%d\n",i);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
