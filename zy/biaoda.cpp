#include<bits/stdc++.h>
using namespace std;
const int P=1e9+7;
int a[20];
int nxt[1<<16][20];
int rn[20],ro[20];
int dp[20][1<<16];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n,K,L;
		scanf("%d%d%d",&n,&K,&L);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=0;i<(1<<n);i++)
			for(int j=1;j<=K;j++){
				nxt[i][j]=0;
				for(int k=1;k<=n;k++){
					ro[k]=ro[k-1]+((i>>(k-1))&1);
					if(a[k]==j)rn[k]=ro[k-1]+1;
					else rn[k]=max(ro[k],rn[k-1]);
					if(rn[k]>rn[k-1])nxt[i][j]|=1<<(k-1);
				}
			}
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		for(int i=1;i<=n;i++)
			for(int j=0;j<(1<<n);j++){	
				if(!dp[i-1][j])continue;
				for(int k=1;k<=K;k++){
					(dp[i][nxt[j][k]]+=dp[i-1][j])%=P;
					cout<<j<<' '<<k<<' '<<nxt[j][k]<<endl;
				}
			}
		int ans=0;
		for(int i=0;i<(1<<n);i++)
			if(__builtin_popcount(i)==L)
				(ans+=dp[n][i])%=P;
		printf("%d\n",ans);
	}
	return 0;
}//
