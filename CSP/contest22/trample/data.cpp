#include<bits/stdc++.h>
using namespace std;
const int md=1e9;
int main(){
	srand(time(NULL));
	int n=30;
	cout<<n<<endl;
	for(int i=1;i<=n;i++){
		printf("%d %d %d\n",rand()%md+1,rand()%md+1,rand()%md+1);
	}
	return 0;
}
