#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	cout<<100000<<endl;
	for(int i=1;i<=100000;i++){
		cout<<1LL*rand()*rand()%1000000<<endl;
	}
	return 0;
}