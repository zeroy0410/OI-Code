#include<bits/stdc++.h>
using namespace std;
int mp[2005];
void init(){
	mp[10]=0,mp[20]=1,mp[50]=2,mp[100]=3,mp[200]=4,mp[500]=5,mp[2000]=6;
}
void chk(int &x,int y){if(x>y)x=y;}
int a[100005];
int dp[2][8][1<<7];//枚举到第几个，上一位是几，当前已经确定了的二进制。 
int main(){
	init();
	int T;scanf("%d",&T);
	while(T--){
		int n,st=0;scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			a[i]=mp[a[i]];
			st|=1<<a[i];
		}
		memset(dp,63,sizeof(dp));
		dp[0][7][0]=0;
		for(int i=1;i<=n;i++){
			memset(dp[i&1],63,sizeof(dp[i&1]));
			for(int j=0;j<=7;j++)
				for(int k=0;k<(1<<7);k++){
					chk(dp[i&1][j][k],dp[~i&1][j][k]+(j!=a[i]));
					if(!(k&(1<<a[i])))chk(dp[i&1][a[i]][k|(1<<a[i])],dp[~i&1][j][k]);
				} 
		}
		int ans=1e9;
		for(int i=0;i<7;i++)chk(ans,dp[n&1][i][st]);
		printf("%d\n",ans);
	}
	return 0;
} 
