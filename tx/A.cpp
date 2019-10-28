#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n;
int solve(int *A,int *B){
	int now=0,h1=1,h2=1,t1=n,t2=n;
	while(h1<=t1){
		if(A[h1]>B[h2])h1++,h2++,now+=2;
		else if(A[t1]>B[t2])t1--,t2--,now+=2;
		else {
			if(A[h1]==B[t2])now++;
			h1++;t2--;
		}
	}
	return now;
}
int A[M],B[M];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1;i<=n;i++)scanf("%d",&B[i]);
	sort(A+1,A+n+1);sort(B+1,B+n+1);
	printf("%d %d\n",solve(A,B),n+n-solve(B,A));
	return 0;
}
