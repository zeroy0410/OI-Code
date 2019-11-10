#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	int n=5,q=3;
	cout<<n<<' '<<q<<endl;
	for(int i=1;i<=q;i++){
		int x=rand()%5+1;
		int op=rand()%2?1:-1;
		cout<<x*op<<endl;
	}
	return 0;
}
