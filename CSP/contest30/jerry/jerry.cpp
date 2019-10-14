#include<bits/stdc++.h>
#define LL long long
#define M 200005
using namespace std;
int T,n;
LL A[M];
char op[5];
int fh[M];
LL dp[M][2][2],a[10];
void calc(int i,bool f){
	if(i&1){
		if(!f){
			dp[i][0][f]=dp[i+1][0][f]+A[i];
			dp[i][1][f]=dp[i+1][1][f]+A[i];
		}
		else {
			dp[i][0][f]=max(dp[i+1][0][f],dp[i+1][0][!f])+A[i];
			dp[i][1][f]=min(dp[i+1][1][f],dp[i+1][1][!f])+A[i];
		}
	}
	else {
		if((fh[i]==1&&!f)||(fh[i]==-1&&f)){
			if(!f){
				dp[i][0][f]=dp[i+1][0][f];
				dp[i][1][f]=dp[i+1][1][f];
			}
			else {
				dp[i][0][f]=max(dp[i+1][0][f],dp[i+1][0][!f]);
				dp[i][1][f]=min(dp[i+1][1][f],dp[i+1][1][!f]);
			}
		}
		else {
			if(i==2*n-2){
				dp[i][0][f]=-A[i+1];
				dp[i][1][f]=-A[i+1];
				return;
			}
			a[0]=dp[i+2][0][f];
			a[1]=dp[i+2][1][f];
			a[2]=-dp[i+2][0][f];
			a[3]=-dp[i+2][1][f];
			a[4]=dp[i+2][0][!f];
			a[5]=dp[i+2][1][!f];
			a[6]=-dp[i+2][0][!f];
			a[7]=-dp[i+2][1][!f];
			sort(a,a+8);
			dp[i][0][f]=a[7]-A[i+1];
			dp[i][1][f]=a[0]-A[i+1];
		}
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=2*n-1;i++){
			if(i&1)scanf("%lld",&A[i]);
			else {
				scanf("%s",op+1);
				if(op[1]=='+')fh[i]=1;
				else fh[i]=-1;
			}
		}
		for(int r=0;r<2;r++)
			dp[2*n-1][0][r]=dp[2*n-1][1][r]=A[2*n-1];
		for(int i=2*n-2;i>=1;i--)
			calc(i,0);calc(i,1);
		printf("%lld\n",dp[1][0][0]);
	}
	return 0;
}
