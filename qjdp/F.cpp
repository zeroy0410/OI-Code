#include<bits/stdc++.h>
#define M 55
using namespace std;
char S[M];
int n;
int dp[M][M];
int main(){
	scanf("%s",S+1);
	n=strlen(S+1);
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;i++)dp[i][i]=1;
	for(int l=1;l<n;l++)
		for(int i=1,j=l+1;j<=n;i++,j++){
			if(S[i]==S[j])
				dp[i][j]=min(dp[i+1][j],dp[i][j-1]);
			else 
				for(int k=i;k<j;k++)
					dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
			}
	printf("%d\n",dp[1][n]);
	return 0;
}
