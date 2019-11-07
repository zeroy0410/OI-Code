#include<bits/stdc++.h>
using namespace std;
int A[100005];
int main(){
	srand(time(NULL));
	int n=100000,m=20;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++)A[i]=i;
	random_shuffle(A+1,A+n+1);
	for(int i=1;i<=n;i++)
		printf("%d ",A[i]);
	puts("");
	return 0;
}
