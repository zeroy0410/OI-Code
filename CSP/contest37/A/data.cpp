#include<bits/stdc++.h>
using namespace std;
int main(){
	int n=400000;
	cout<<n<<endl;
	srand(time(NULL));
	for(int i=2;i<=n;i++)
		printf("%d %d 720720\n",rand()%(i-1)+1,i);
	return 0;
}
