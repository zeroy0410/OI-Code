#include<bits/stdc++.h>
#define M 1005
using namespace std;
const int mod=1e9+7;
bool mm1;
int n,m,K;
struct Pshui{
	int dp[M][M][8];
	bool mark[1<<7];
	int get(int x){
		int res=0;
		for(int i=0;i<K;i++)
			if(x&1<<i);
			else res|=1<<i;
		return res;
	}
	int nxt[1<<7][9],pp[1<<7][2];
	int S1[9],S2[9];
	bool check(int S,int a,int b){
		for(int i=0;i<b;i++)S1[i]=(S>>i&1);
		for(int i=0;i<a;i++)S2[i]=(S>>i&1);
		S2[a-1]=!S2[a-1];
		for(int i=b-1,j=a-1;i>=0;i--,j--)
			if(S1[i]!=S2[j])return 0;
		return 1;
	}
	bool check2(int S,int t,int b){
		for(int i=0;i<K;i++)S1[i]=(S>>i&1);
		S1[K]=t;
		for(int i=0;i<b;i++)S2[i]=(S>>i&1);
		for(int i=b-1,j=K;i>=0;i--,j--)
			if(S2[i]!=S1[j])return 0;
		return 1;
	}
	void Init(){
		for(int i=0;i<1<<K;i++){
			nxt[i][1]=0;
			for(int j=2;j<=K;j++){
				for(int k=j-1;k>=1;k--){
					if(check(i,j,k)){
						nxt[i][j]=k;
						break;
					}
				}
			}
			for(int op=0;op<=1;op++){
				for(int k=K;k>=0;k--)
					if(check2(i,op,k)){
						pp[i][op]=k;
						break;
					}
			}
		}
	}
	void Add(int &x,int y){
		x+=y;
		if(x>=mod)x-=mod;
	}
	int ans;
	void solve(){
		Init();
		for(int S=0;S<1<<K;S++){
			if(mark[get(S)])continue;
			mark[S]=1;
			memset(dp,0,sizeof(dp));
			dp[0][0][0]=1;
			for(int i=0;i<n-K;i++){
				for(int j=0;j<=m;j++){
					for(int k=0;k<=K;k++){
						if(dp[i][j][k]==0)continue;
						if(k==K){
							if(j==m){
								Add(dp[i+1][j][pp[S][0]],dp[i][j][k]);
								Add(dp[i+1][j][pp[S][1]],dp[i][j][k]);
							}
							else {
								Add(dp[i+1][j+1][pp[S][0]],dp[i][j][k]);
								Add(dp[i+1][j+1][pp[S][1]],dp[i][j][k]);
							}
						}
						else {
							Add(dp[i+1][j][nxt[S][k+1]],dp[i][j][k]);
							Add(dp[i+1][j][k+1],dp[i][j][k]);
						}
					}
				}
			}
			for(int i=0;i<=K;i++)
				Add(ans,dp[n-K][m][i]);
			if(m>0)Add(ans,dp[n-K][m-1][K]);
		}
		printf("%lld\n",1LL*ans*2%mod);
	}
}pshui; 
bool mm2;
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	pshui.solve();
	return 0;
}
