#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	freopen("shortest.in","w",stdout);
	int n=1000;
	cout<<n<<endl;
	for(int i=1;i<=6;i++){
		for(int j=1;j<=n;j++)
			printf("%d ",rand()%10000);
		printf("\n");
	}
	int Q=1000;
	cout<<Q<<endl;
	for(int i=1;i<=Q;i++){
		printf("2 %d %d %d %d\n",rand()%6+1,rand()%n+1,rand()%6+1,rand()%n+1);	
	}
	return 0;	
}
