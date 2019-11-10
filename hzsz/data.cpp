#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("data.in","w",stdout);
	srand(time(NULL));
	for(int i=1;i<=1000;i++){
		printf("%c",rand()%26+'A');
	}
	return 0;
}
