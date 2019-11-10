#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=1e9+7;
int T,n,K,L,A[20];
int dp[20][1<<20];
int cnt[1<<20],nxt[1<<20][20];
int ro[20],rn[20];
LL ans=0;
void Init(){
	for(int i=0;i<1<<n;i++){
		for(int j=1;j<=K;j++){
			nxt[i][j]=0;
			for(int k=1;k<=n;k++){
				ro[k]=ro[k-1]+((i>>(k-1))&1);
				if(A[k]==j)rn[k]=ro[k-1]+1;
				else rn[k]=max(ro[k],rn[k-1]);
				if(rn[k]>rn[k-1])nxt[i][j]|=1<<(k-1);
			}
		}
	}
}
int main(){
	scanf("%d",&T);
	for(int i=1;i<(1<<16);i++)
		cnt[i]=cnt[i&(i-1)]+1;
	while(T--){
		scanf("%d%d%d",&n,&K,&L);
		for(int i=1;i<=n;i++)
			scanf("%d",&A[i]);
		memset(ro,0,sizeof(ro));
		memset(rn,0,sizeof(rn));
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		Init();
		ans=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<1<<n;j++){
				if(!dp[i-1][j])continue;
				for(int k=1;k<=K;k++){
					(dp[i][nxt[j][k]]+=(dp[i-1][j]))%=mod;
				}
			}
		}
		for(int i=0;i<1<<n;i++)
			if(cnt[i]==L)
				(ans+=dp[n][i])%=mod;
		cout<<ans<<endl;
	}
	return 0;
}
