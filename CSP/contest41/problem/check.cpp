#include<bits/stdc++.h>
#define M 1005
using namespace std;
int n,A[M];
bool mark[M][M];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){
		for(int j=1;j<=n;j++)
			scanf("%d",&A[j]);
		for(int j=1;j<=n/2;j++){
			int a=A[2*j-1],b=A[2*j];
			mark[a][b]=mark[b][a]=1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			if(!mark[i][j]){puts("WA");return 0;}
		}
	}
	puts("AC");
	return 0;
}
