#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	int n=1000000,m=999999;
	cout<<n<<' '<<m<<endl;
	for(int i=2;i<=n;i++){
		printf("%d %d %d\n",rand()%(i-1)+1,i,rand()%100);
	}
	return 0;
}
