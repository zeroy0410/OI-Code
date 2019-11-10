#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
void tomin(LL &x,LL y){if(x>y)x=y;}
int n,m,h[M],tt,A[M];
char op[15];
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
struct node{
	LL a[2][2];
	node(){a[0][0]=a[1][1]=a[0][1]=a[1][0]=1e13;}
}dp[M][18];
node merge(node x,node y){
	node res;
	for(int a=0;a<2;a++)
		for(int b=0;b<2;b++)
			for(int k=0;k<2;k++)
				tomin(res.a[a][b],x.a[a][k]+y.a[k][b]);
	return res;
}
LL f[M][2],g[M][2],dep[M];
int fa[M][18];
void dfs(int x,int ff,int d){
	f[x][0]=0;f[x][1]=A[x];fa[x][0]=ff;
	dep[x]=d;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==ff)continue;
		dfs(u,x,d+1);
		f[x][0]+=f[u][1];
		f[x][1]+=min(f[u][0],f[u][1]);
	}
}
void redfs(int x,int ff,LL t0,LL t1){
	g[x][0]=f[x][0]+t1;
	g[x][1]=f[x][1]+min(t0,t1);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==ff)continue;
		redfs(u,x,g[x][0]-f[u][1],g[x][1]-min(f[u][0],f[u][1]));
	}
	if(ff){
		dp[x][0].a[0][0]=1e13;
		dp[x][0].a[1][0]=f[ff][0]-f[x][1];
		dp[x][0].a[0][1]=f[ff][1]-min(f[x][0],f[x][1]);
		dp[x][0].a[1][1]=f[ff][1]-min(f[x][0],f[x][1]);
	}
}
int up(int x,int step){
	for(int i=17;i>=0;i--)
		if(step&1<<i)x=fa[x][i];
	return x;
}
int LCA(int a,int b){
	if(dep[a]>dep[b])swap(a,b);
	int step=dep[b]-dep[a];
	b=up(b,step);
	if(a==b)return a;
	for(int i=17;i>=0;i--)
		if(fa[a][i]!=fa[b][i])
			a=fa[a][i],b=fa[b][i];
	return fa[a][0];
}
LL Print(LL x){
	if(x>=1e13)return -1;
	return x;
}
int main(){
//	freopen("defense.in","r",stdin);
//	freopen("defense.out","w",stdout);
	scanf("%d%d%s",&n,&m,op+1);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	dfs(1,0,0);redfs(1,0,0,0);
	for(int j=1;j<=17;j++)
		for(int i=1;i<=n;i++)
			fa[i][j]=fa[fa[i][j-1]][j-1];
	for(int j=1;j<=17;j++)
		for(int i=1;i<=n;i++)
			dp[i][j]=merge(dp[i][j-1],dp[fa[i][j-1]][j-1]);
	for(int i=1,x,a,y,b;i<=m;i++){
		scanf("%d%d%d%d",&x,&a,&y,&b);
		if(dep[x]>dep[y])swap(x,y),swap(a,b);
		int lca=LCA(x,y);
		int tx=x,ty=y;
		if(x==lca){
			int step=dep[y]-dep[x]-1;
			node res;res.a[0][0]=-1;
			for(int j=17;j>=0;j--){
				if(step&1<<j){
					if(res.a[0][0]==-1)res=dp[y][j];
					else res=merge(res,dp[y][j]);
					y=fa[y][j];
				}
			}
			if(res.a[0][0]==-1){
				res.a[0][0]=res.a[1][1]=0;
				res.a[1][0]=res.a[0][1]=1e13;
			}
			LL tmp[3];
			tmp[0]=g[x][0]-f[y][1];
			tmp[1]=g[x][1]-min(f[y][0],f[y][1]);
			if(a==0)printf("%lld\n",Print(f[ty][b]+res.a[b][1]+tmp[a]));
			else printf("%lld\n",Print(f[ty][b]+min(res.a[b][0],res.a[b][1])+tmp[a]));
		}
		else {
			node res1,res2;res1.a[0][0]=-1;res2.a[0][0]=-1;
			int step=dep[y]-dep[lca]-1;
			for(int j=17;j>=0;j--){
				if(step&1<<j){
					if(res2.a[0][0]==-1)res2=dp[y][j];
					else res2=merge(res2,dp[y][j]);
					y=fa[y][j];
				}
			}
			step=dep[x]-dep[lca]-1;
			for(int j=17;j>=0;j--){
				if(step&1<<j){
					if(res1.a[0][0]==-1)res1=dp[x][j];
					else res1=merge(res1,dp[x][j]);
					x=fa[x][j];
				}
			}
			if(res1.a[0][0]==-1){
				res1.a[0][0]=0;
				res1.a[1][1]=0;
				res1.a[1][0]=res1.a[0][1]=1e13;
			}
			if(res2.a[0][0]==-1){
				res2.a[0][0]=0;
				res2.a[1][1]=0;
				res2.a[1][0]=res2.a[0][1]=1e13;
			}
			LL tmp[3];
			tmp[0]=g[lca][0]-f[y][1]-f[x][1];
			tmp[1]=g[lca][1]-min(f[y][0],f[y][1])-min(f[x][0],f[x][1]);
			LL ans=1e18;
			ans=min(ans,res1.a[a][1]+res2.a[b][1]+tmp[0]);
			ans=min(ans,min(res1.a[a][0],res1.a[a][1])+min(res2.a[b][0],res2.a[b][1])+tmp[1]);
			ans+=f[tx][a]+f[ty][b];
			printf("%lld\n",Print(ans));
		}
	}
	return 0;
}
