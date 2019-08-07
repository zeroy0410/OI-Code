#include<bits/stdc++.h>
using namespace std;
int in[1000005],a[1000005],b[1000005];
int main(){
	freopen("data.in","w",stdout);
	srand(time(NULL));
	int n=5000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++){
		printf("%d %d\n",rand()%100000+1,rand()%100000+1);
	}
	return 0;	
}
