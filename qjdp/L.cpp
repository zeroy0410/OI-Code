#include<bits/stdc++.h>
#define M 2005
using namespace std;
int n,A[M],dp[M][M];
struct node{
	int pos,x;
}Q[M][M],Q2[M][M];
int l[M],r[M],l2[M],r2[M];
int main(){
	scanf("%d",&n);
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),dp[i][i]=A[i],dp[i][i-1]=0;
	for(int i=1;i<=n;i++)l[i]=l2[i]=0,r[i]=r2[i]=-1;
	for(int i=n;i>=1;i--){
		int las=i;
		for(int j=i+1;j<=n;j++){
			bool fl=0;
			for(int k=las;k<=j;k++){
				if(dp[i][k-1]>dp[k+1][j]){
					las=k;fl=1;
					break;
				}
			}
			if(fl==0)las=j+1;
			int ls=las-1;
			//[i,las[j]]   dp[k+1][j]+A[k]
			//[las[j]+1,j] dp[i][k-1]+A[k]
			while(l[j]<=r[j]&&Q[j][l[j]].pos>ls)l[j]++;
			while(l[j]<=r[j]&&Q[j][r[j]].x>dp[i+1][j]+A[i])r[j]--;
			Q[j][++r[j]]=(node){i,dp[i+1][j]+A[i]};
			while(l2[i]<=r2[i]&&Q2[i][l2[i]].pos<ls+1)l2[i]++;
			while(l2[i]<=r2[i]&&Q2[i][r2[i]].x>dp[i][j-1]+A[j])r2[i]--;
			Q2[i][++r2[i]]=(node){j,dp[i][j-1]+A[j]};
			if(Q[j][l[j]].pos<=ls)dp[i][j]=min(dp[i][j],Q[j][l[j]].x);
			if(Q2[i][l2[i]].pos>ls)dp[i][j]=min(dp[i][j],Q2[i][l2[i]].x);
//			cout<<i<<' '<<j<<' '<<dp[i][j]<<' '<<ls<<endl;
		}
	}
	printf("%d\n",dp[1][n]);
	return 0;
}
