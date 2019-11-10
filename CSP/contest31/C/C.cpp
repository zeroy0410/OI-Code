#include<bits/stdc++.h>
#define M 3005
#define LL long long
using namespace std;
int n;
struct node{
	int l,r,p;
}A[M];
int B[M],bc;
LL dp[M][M];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&A[i].p,&A[i].l,&A[i].r);
		B[++bc]=A[i].p-A[i].l;
		B[++bc]=A[i].p+A[i].r;
	}
	sort(B+1,B+bc+1);
	bc=unique(B+1,B+bc+1)-B-1;
	for(int i=1;i<=n;i++){
		A[i].l=lower_bound(B+1,B+bc+1,A[i].p-A[i].l);
		A[i].r=lower_bound(B+1,B+bc+1,A[i].p+A[i].r);
		A[i].p=lower_bound(B+1,B+bc+1,A[i].p);
	}
	return 0;
}
