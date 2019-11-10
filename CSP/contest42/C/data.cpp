#include<bits/stdc++.h>
using namespace std;
bool mark[1005][1005];
int main(){
	srand(time(NULL));
	int n=1000,m=2000;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++)
		printf("1 ");
	puts("");
	for(int i=1;i<=m;i++){
		int a=rand()%n+1,b=rand()%n+1;
		while(a==b||mark[a][b])
			a=rand()%n+1,b=rand()%n+1;
		mark[a][b]=mark[b][a]=1;
		printf("%d %d\n",a,b);
	}
	return 0;
}
