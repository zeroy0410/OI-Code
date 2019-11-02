#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	int n=20,K=20;
	cout<<n<<' '<<K<<endl;
	for(int i=2;i<=n;i++)
		printf("%d %d\n",rand()%(i-1)+1,i);
	return 0;
}
