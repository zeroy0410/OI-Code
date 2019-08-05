#include<bits/stdc++.h>
int main(){
	freopen("zoo.in","w",stdout);
	srand(time(NULL));
	int n=5;
	printf("%d\n",n);
	for(int i=1;i<=n;i++){
		int len=500;
		for(int j=1;j<=len;j++){
			printf("%c",rand()%26+'a');
		}
		puts("");
	}
	return 0;	
}
