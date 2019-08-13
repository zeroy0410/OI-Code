#include<bits/stdc++.h>
using namespace std;
int in[1000005],a[1000005],b[1000005];
int main(){
	freopen("data.in","w",stdout);
	srand(time(NULL));
	int n=5,K=2;
	printf("%d %d\n",n,K);
	for(int i=1;i<=n;i++){
		int a=rand()%10+1;
		int b=a+rand()%10+1;
		printf("%d %d\n",a,b);
	}
	return 0;	
}
