#include<bits/stdc++.h>
using namespace std;
int K,n,A[16];
int de[16];
double dp[105][1<<15];
int main(){
	scanf("%d%d",&K,&n);
	memset(de,0,sizeof(de));
	for(int i=1,x;i<=n;i++){
		scanf("%d",&A[i]);
		while(1){
			scanf("%d",&x);
			if(x==0)break;
			de[i]|=(1<<(x-1));
		}
	}
	int maxs=(1<<n)-1;
	for(int i=K;i>=1;i--)
		for(int s=0;s<=maxs;s++){
			for(int j=1;j<=n;j++){
				if((de[j]&s)==de[j])
					dp[i][s]+=max(dp[i+1][s],dp[i+1][s|(1<<(j-1))]+A[j]);
				else
					dp[i][s]+=dp[i+1][s];
			}
			dp[i][s]/=n;
		}
	printf("%.6lf\n",dp[1][0]);
	return 0;
}
