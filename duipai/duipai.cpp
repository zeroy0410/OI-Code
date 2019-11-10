#include<bits/stdc++.h>
using namespace std;
int main(){
	while(1){
		system("./data.exe > data.in");
		system("./test.exe < data.in > 1.ans");
		system("./biaoda.exe < data.in > 2.ans");
		if(system("diff 1.ans 2.ans"))break;
		puts("AC");	
	}
	puts("WA");
	return 0;
}
