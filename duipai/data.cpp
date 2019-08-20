#include<bits/stdc++.h>
using namespace std;
int in[1000005],a[1000005],b[1000005];
int main(){
	srand(time(NULL));
	int n=50;
	printf("%d\n",n);
	for(int i=1;i<=n;i++){
		long long b=1LL*rand()*rand()%((long long)1e8);
		printf("%lld\n",b);
	}
	return 0;	
}
