#include<bits/stdc++.h>
using namespace std;
int main(){
	while(1){
		system("./data.exe");
		system("./test.exe");
		system("./biaoda.exe");
		if(system("diff 1.ans 2.ans"))break;
		puts("AC");	
	}
	puts("WA");
	return 0;
}
