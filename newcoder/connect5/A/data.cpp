#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	int n=10000000,d=1926;
	cout<<n<<' '<<d<<endl;
	for(int i=1;i<=n;i++)
		printf("%d ",1LL*rand()*rand()%(int)1e6);
	return 0;
}
