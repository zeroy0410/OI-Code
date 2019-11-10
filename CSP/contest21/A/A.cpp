#include<iostream>
#include<cstdio>
#define M 100005
using namespace std;
int n,m,A[M];
bool mark[M];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d",&A[i]),mark[A[i]]=1;
	int cur=1;
	for(int i=1;i<=n;i++){
		if(!mark[i]){
			while(A[cur]<i&&cur<=m)printf("%d\n",A[cur]),cur++;
			printf("%d\n",i);
		}
	}
	while(cur<=m)printf("%d\n",A[cur]),cur++;
	return 0;
}
