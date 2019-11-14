#include<bits/stdc++.h>
#define M 5005
using namespace std;
const int mod=1e9+7;
int n,m,K,h[M],tt=1,in[M];
struct edge{
	int nxt,to;
}G[M<<2];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
struct P100{
	int dp[M][35],dfn[M],low[M],fa[M],fb[M],tmp[M],tot;
	bool is[M<<2],mark[M<<2],istop[M];
	int pre[M][35],las[M][35],f[M][35];
	int ans,Q[M],qc;
	void Ad(int &x,int y){
		x+=y;
		if(x>=mod)x-=mod;
	}
	void tarjan(int x,int f,int fe){
		fa[x]=f;fb[x]=fe;
		dfn[x]=low[x]=++tot;
		for(int i=h[x];i;i=G[i].to){
			if((i^1)==fe)continue;
			int u=G[i].to;
			if(!dfn[u]){
				tarjan(u,x,i);
				low[x]=min(low[x],low[u]);
			}
			else {
				low[x]=min(low[x],dfn[u]);
				if(dfn[x]>dfn[u]){
					is[i]=is[i^1]=1;mark[i]=mark[i^1]=1;
					int t=x;
					while(t!=u){
						mark[fb[t]]=1;
						mark[fb[t]^1]=1;
						t=fa[t];
					}
					istop[u]=1;
				}
			}
		}
	}
	void solve_lop(int u,int x){
		qc=0;
		while(x!=fa[u]){
			Q[++qc]=x;
			x=fa[x];
		}
		//ignore u
		f[0][0]=1;
		for(int i=1;i<qc;i++){
			memset(tmp,0,sizeof(tmp));
			for(int a=
		}
	}
	void dfs(int x){
		dp[x][1]=1;
		for(int i=h[x];i;i=G[i].nxt){
			if(i==fb[x])continue;
			if(is[i])solve_lop(G[i].to,x);
			if(mark[i])continue;
			int u=G[i].to;
			dfs(u);
			memset(tmp,0,sizeof(tmp));
			for(int a=1;a<=K;a++)
				for(int b=1;a+b<=K;b++)
					tmp[a+b]=(tmp[a+b]+1LL*dp[x][a]*dp[u][b]%mod)%mod;
			for(int j=1;j<=K;j++)
				dp[x][j]=tmp[x][j];
		}
		if(!istop[x]){
			for(int j=1;j<=K;j++)
				Ad(ans,dp[x][j]);//must choose x
		}
	}
	void solve(){
		tarjan(1,0,-2);
		dfs(1,0);
		printf("%d\n",ans);
	}
}p100;
int main(){
//	freopen("cactus.in","r",stdin);
//	freopen("cactus.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
		in[a]++;in[b]++;
	}
	p100.solve();
	return 0;
}
