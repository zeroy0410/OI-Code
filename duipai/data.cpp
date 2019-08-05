#include<bits/stdc++.h>
using namespace std;
int in[1000005],a[1000005],b[1000005];
int main(){
	freopen("data.in","w",stdout);
	srand(time(NULL));
	int m=20,n=20;
	printf("%d %d\n",m,n);
	for(int i=1;i<=m;i++){
		printf("%d ",rand()%10+1);
		int c=rand()%n;
		for(int j=1;j<=c;j++)
			printf("%d ",rand()%n+1);
		puts("");
	}
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%10+1);
	puts("");
	return 0;	
}
