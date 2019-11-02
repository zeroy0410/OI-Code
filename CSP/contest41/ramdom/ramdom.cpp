#include<bits/stdc++.h>
#define M 5005
using namespace std;
const int mod=998244353;
int n,K,h[M],tt;
struct edge{
	int nxt,to;
}G[M];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
struct P20{
	int dp[1<<20],bin[1<<20];
	int sta[20];
	void Add(int &x,int y){
		x+=y;
		if(x>=mod)x-=mod;
	}
	void dfs(int x,int st){
		sta[x-1]=st;
		st|=(1<<(x-1));
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to;
			dfs(u,st);
		}
	}
	void solve(){
		dfs(1,0);
		dp[0]=1;
		int base=(1<<n)-1;
		for(int i=0;i<20;i++)bin[1<<i]=i;
		for(int i=0;i<n;i++){
			for(int j=base;j>=0;j--){
				if(!dp[j])continue;
				int t=base^j;
				while(t){
					int k=bin[t&-t];
					if((sta[k]&j)==sta[k])Add(dp[j|1<<k],1LL*dp[j]*K%mod);
					else Add(dp[j|1<<k],dp[j]);
					t-=(t&-t);
				}
				dp[j]=0;
			}
		}
		printf("%d\n",dp[base]);
	}
}p20;
//struct P60{
//	int dp[M][M];
//	void solve(){
//		
//	}
//}p60;
int main(){
	freopen("ramdom.in","r",stdin);
	freopen("ramdom.out","w",stdout);
	scanf("%d%d",&n,&K);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);
	}
	p20.solve();
	return 0;
}
