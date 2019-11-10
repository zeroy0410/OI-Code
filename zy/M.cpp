#include<bits/stdc++.h>
#define M 100005
using namespace std;
int T,n,A[M];
int dp[2][8][1<<7];
int mp[2005],st;
void Init(){
	mp[10]=0,mp[20]=1,mp[50]=2,mp[100]=3,mp[200]=4,mp[500]=5,mp[2000]=6;
}
void tomin(int &x,int y){if(x>y)x=y;}
int main(){
	Init();
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);st=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&A[i]);
			A[i]=mp[A[i]];
			st|=1<<A[i];
		}
		memset(dp,63,sizeof(dp));
		dp[0][7][0]=0;
		for(int i=1;i<=n;i++){
			memset(dp[i&1],63,sizeof(dp[i&1]));
			for(int j=0;j<=7;j++)
				for(int k=0;k<(1<<7);k++){
					tomin(dp[i&1][j][k],dp[~i&1][j][k]+(j!=A[i]));
					if(!(k&(1<<A[i])))tomin(dp[i&1][A[i]][k|(1<<A[i])],dp[~i&1][j][k]);
				} 
		}
		int ans=1e9;
		for(int i=0;i<7;i++)tomin(ans,dp[n&1][i][st]);
		printf("%d\n",ans);
	}
	return 0;
}
