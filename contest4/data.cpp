#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	freopen("plan.in","w",stdout);
	int n=200000,m=200000;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++){
		printf("%d ",rand());	
	}
	puts("");
	for(int i=1;i<=m;i++){
		int op=rand()%2+1;
		if(op==1)printf("%d %d\n",op,rand());
		else printf("%d %d %d\n",op,rand()%n+1,rand()); 
	}
	return 0;	
}
