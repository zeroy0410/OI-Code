#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	freopen("necklace.in","w",stdout);
	int n=5,c=5;
	cout<<n<<' '<<c<<endl;
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%c+1);
	puts("");
	int q=10;
	printf("%d\n",q);
	while(q--){
		int op=rand()%6;
//		while(op==5)op=rand()%6;
		if(op==0){
			printf("R %d\n",rand()%(n-1)+1);	
		}
		else if(op==1){
			printf("F\n");
		}
		else if(op==2){
			printf("S %d %d\n",rand()%n+1,rand()%n+1);
		}
		else if(op==3){
			printf("P %d %d %d\n",rand()%n+1,rand()%n+1,rand()%c+1);
		}
		else if(op==4){
			printf("C\n");
		}
		else {
			printf("CS %d %d\n",rand()%n+1,rand()%n+1);	
		}
	}
	return 0;
}
