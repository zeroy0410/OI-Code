#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n;
LL sum,sum2,A[M];
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]),sum+=A[i],sum2+=A[i]*A[i];
	for(int i=1;i<=n;i++)
		printf("%lld ",(sum2-A[i]*A[i])*(n-1)-(sum-A[i])*(sum-A[i]));
	return 0;
}
