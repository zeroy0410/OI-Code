#include<bits/stdc++.h>
#define M 105
using namespace std;
const int mod=1e9+7;
int T,n,dp[M][1<<10];
bool mark[15][M];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(mark,0,sizeof(mark));
		for(int i=0,x;i<n;i++){
			char c='a';
			while(c!='\n'){
				scanf("%d",&x);
				mark[i][x]=1;
				c=getchar();
			}
		}
		dp[0][0]=1;
		for(int i=1;i<=100;i++){
			for(int j=0;j<1<<n;j++)dp[i][j]=dp[i-1][j];
			for(int j=0;j<n;j++){
				if(mark[j][i])
					for(int k=(1<<n)-1;k>=0;k--)
						if(k&1<<j)
							dp[i][k]=(dp[i][k]+dp[i-1][k^(1<<j)])%mod;
			}
		}
		printf("%d\n",dp[100][(1<<n)-1]);
	}
	return 0;
}
