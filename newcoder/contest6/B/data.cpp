#include<bits/stdc++.h>
using namespace std;
int A[1000005];
int main(){
	srand(time(NULL));
	int n=10,K=10,m=0;
	printf("%d %d %d\n",n,K,m);
	for(int i=1;i<=4;i++)
		A[rand()%n+1]=rand()%K+1;
	for(int i=1;i<=n;i++)
		printf("%d ",A[i]);
	return 0;
}
