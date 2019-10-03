#include<bits/stdc++.h>
using namespace std;
const int mod=1e6;
int main(){
	srand(time(NULL));
	int n=5,K=2;
	printf("%d %d\n",n,K);
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%mod);
	return 0;
}
