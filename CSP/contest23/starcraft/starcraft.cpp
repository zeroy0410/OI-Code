#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
int n,m,T,K;
struct P30{
	double dp[M][25];
	void solve(){
		for(int c=m;c>=n;c--){
			for(int x=T;x>=0;x--){
				if(x==T)dp[x][c]=0;
				else if(c==m)dp[x][c]=dp[x+1][c];
				else {
					double p=1.0/T*(int)(T/(x+1));
					dp[x][c]=(dp[x+1][c+1]+(T-x-1)*K)*p+dp[x+1][c]*(1-p);
				}
			}
		}
		printf("%.6lf",dp[0][n]+T*n*K);
	}
}p30;
int main(){
	freopen("starcraft.in","r",stdin);
	freopen("starcraft.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&T,&K);
	p30.solve();
	return 0;
}
