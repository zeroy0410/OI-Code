#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	freopen("forest.in","w",stdout);
	int n=50,m=1000;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=m;i++){
		printf("%d %d %d %d\n",rand()%n+1,rand()%n+1,rand()%105+1,rand()%105+1);
	}
	return 0;	
}
