#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	int n=1e6;
	cout<<n<<endl;
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%n+1);
	return 0;
}
