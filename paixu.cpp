#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,A[M];
void maopao(){
	for(int i=1;i<=n-1;i++){
		bool fl=0;
		for(int j=1;j<=n-i;j++){
			if(A[j]>A[j+1]){
				swap(A[j],A[j+1]);
				fl=1;
			}
		}
		if(!fl)break;
	}
}
void xuanze(){
	for(int i=1;i<=n;i++){
		int k=i;
		for(int j=i+1;j<=n;j++)
			if(A[j]<A[k])
				k=j;
		for
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	
	return 0;
}
