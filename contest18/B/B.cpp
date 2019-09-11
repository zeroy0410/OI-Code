#include<bits/stdc++.h>
#define M 505
using namespace std;
const int mod=1024523;
int n,m;
char A[M],B[M];
int dp[2][M][M];
void Add(int &x,int y){
	x+=y;
	if(x>=mod)x-=mod;	
}
int main(){
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout); 
	scanf("%d%d%s%s",&n,&m,A+1,B+1);
	dp[0][0][0]=1;
	for(int i=0;i<=n;i++){
		int cur=(i&1);
		memset(dp[!cur],0,sizeof(dp[!cur]));
		for(int j=0;j<=m;j++){
			for(int x=0;x<=n;x++){
				int &tmp=dp[cur][j][x];
				if(!tmp)continue;
				int y=i+j-x;
				if(A[i+1]==A[x+1])
					Add(dp[!cur][j][x+1],tmp);
				if(A[i+1]==B[y+1])
					Add(dp[!cur][j][x],tmp);
				if(B[j+1]==A[x+1])
					Add(dp[cur][j+1][x+1],tmp);
				if(B[j+1]==B[y+1])
					Add(dp[cur][j+1][x],tmp);
			}
		}
	}
	printf("%d",dp[n&1][m][n]);
	return 0;
}
