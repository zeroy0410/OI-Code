#include<bits/stdc++.h>
#define M 200005
using namespace std;
const int mod=998244353;
char S[M];
int n;
struct P30{
	bool mark[60005];
	int ans;
	int get(){
		int res=0;
		for(int i=1;i<=n;i++)
			res=res*3+S[i];
		return res;
	}
	void dfs(){
		int cod=get();
		if(mark[cod])return;
		mark[cod]=1;ans++;
		for(int i=1;i<=n-1;i++){
			if(S[i]!=S[i+1]){
				int to=3-S[i]-S[i+1];
				char a=S[i],b=S[i+1];
				S[i]=to;S[i+1]=to;
				dfs();
				S[i]=a;S[i+1]=b;
			}
		}
	}
	void solve(){
		dfs();
		printf("%d\n",ans);
	}
}p30;
int qkpow(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=1LL*res*a%mod;
		a=1LL*a*a%mod;
		b>>=1;
	}
	return res;
}
int dp[M][3][3];
void Add(int& x,int y){
	x+=y;
	if(x>=mod)x-=mod;
}
int main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	scanf("%s",S+1);
	n=strlen(S+1);
	for(int i=1;i<=n;i++)
		S[i]-='a';
	bool fl1=1;
	for(int i=2;i<=n;i++)
		if(S[i]!=S[i-1])fl1=0;
	if(fl1)puts("1");
	else if(n<=3)p30.solve();
	else {
		int ca=0;
		for(int i=1;i<=n;i++)
			ca=(ca+S[i])%3;
		memset(dp,0,sizeof(dp));
		for(int i=0;i<3;i++)
			dp[1][i][i]=1;
		for(int i=2;i<=n;i++){
			for(int j=0;j<3;j++){
				for(int k=0;k<3;k++){
					if(k==j)continue;
					for(int r=0;r<3;r++){
						Add(dp[i][j][(r+j)%3],dp[i-1][k][r]);
					}
				}
			}
		}
		int tot=qkpow(3,n-1),ans=0;
		for(int i=0;i<3;i++)
			Add(ans,dp[n][i][ca]);
		bool fl=1;
		for(int i=2;i<=n;i++)
			if(S[i]==S[i-1])fl=0;
		ans=(tot-ans+fl+mod)%mod;
		printf("%d\n",ans);
	}
	return 0;
}
