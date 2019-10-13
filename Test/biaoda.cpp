#include<bits/stdc++.h>
#define For(a,b,c) for(int a=b;a<=c;++a)
#define Dor(a,b,c) for(int a=b;a>=c;--a)
#define LL long long
using namespace std;
const int N=100007;
int n;
LL k,A[N];
int main() {
	scanf("%d%lld",&n,&k);
	For(i,1,n) scanf("%lld",&A[i]);
	sort(A+1,A+1+n);
	for(int i;i>=1,n>>1) {
		int j=n-i+1;
		LL x=(A[i+1]-A[i]+A[j]-A[j-1])*i;
		if(x<=k) k-=x;
		else {
			printf("%lld",A[j]-A[i]-k/i);
			return 0;
		}
	}
	puts("0");
	return 0;
}
