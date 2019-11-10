#include<bits/stdc++.h>
using namespace std;
int mark[17];
int main(){
	srand(time(NULL));
	int n=3,m=3;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=n*m;i++)mark[i]=i;
	random_shuffle(mark+1,mark+n*m+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			printf("%d ",mark[(i-1)*m+j]);
		puts("");
	}
	return 0;
}
