#include<bits/stdc++.h>
#define M 1000005
using namespace std;
int n,m;
struct node{
	int a,b,c;
}A[M];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&A[i].a,&A[i].b,&A[i].c);
		A[i].a++;A[i].b++;
	}
	if(m<=20)p20.solve();
	else p50.solve();
	return 0;
}
