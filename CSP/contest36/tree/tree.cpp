#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n,m,h[M],tt;
bool mark[M];
struct edge{
	int nxt,to;
	LL co;
	LL mx;int lca;
}G[M<<1];
void Add(int a,int b,LL c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
LL mx[M];
int fa[M][18],ret[M],dep[M],lca[M];
int LCA(int a,int b){
	if(dep[a]>dep[b])swap(a,b);
	int step=dep[b]-dep[a];
	for(int i=17;i>=0;i--)
		if(step&1<<i)b=fa[b][i];
	if(a==b)return a;
	for(int i=17;i>=0;i--)
		if(fa[a][i]!=fa[b][i])
			a=fa[a][i],b=fa[b][i];
	return fa[a][0];
}
void Add(LL &mxx,int &llca,LL tx,int tl,int rt){
	if(tx>mxx){
		mxx=tx;
		llca=tl;
	}
	else if(tx==mxx)
		llca=rt;
}
void dfs(int x,int f,LL d,int dp){
	if(mark[x])mx[x]=0,lca[x]=x;
	else mx[x]=-1e18;fa[x][0]=f;dep[x]=dp;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		LL c=G[i].co;
		if(u==f)continue;
		dfs(u,x,d+c,dp+1);
		Add(mx[x],lca[x],mx[u]+c,lca[u],x);
	}
//	cout<<x<<' '<<mx[x]<<' '<<lca[x]<<endl;
}
int Q[M],qcnt;
void redfs(int x,LL fmx,int flca){
	LL tmx;int tlca;
//	cout<<x<<' '<<fmx<<' '<<flca<<endl;
	if(mark[x]){
		tmx=fmx;tlca=flca;
		Add(tmx,tlca,mx[x],lca[x],x);
//		cout<<x<<' '<<tlca<<endl;
		if(tlca!=x){
			int tmp=LCA(tlca,x);
			ret[x]++;ret[tlca]++;
			ret[tmp]--;ret[fa[tmp][0]]--;
		}
	}
	qcnt=0;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==fa[x][0])continue;
		Q[++qcnt]=i;
	}
	tmx=-1e18;tlca=0;
	for(int i=qcnt;i>=1;i--){
		G[Q[i]].mx=tmx;G[Q[i]].lca=tlca;
		int u=G[Q[i]].to;LL c=G[Q[i]].co;
		if(u==fa[x][0])continue;
		Add(tmx,tlca,mx[u]+c,lca[u],x);
//		if(x==6)cout<<u<<' '<<tmx<<' '<<tlca<<endl;
	}
	tmx=fmx;tlca=flca;
	if(mark[x])Add(tmx,tlca,0,x,x);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;LL c=G[i].co;
		if(u==fa[x][0])continue;
		LL ttmx=tmx;int ttlca=tlca;
		Add(ttmx,ttlca,G[i].mx,G[i].lca,x);
		redfs(u,ttmx+c,ttlca);
		Add(tmx,tlca,mx[u]+c,lca[u],x);
	}
}
int ct,ans=-1;
void dfs_ans(int x,int f){
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs_ans(u,x);
		ret[x]+=ret[u];
	}
	if(mark[x])return;
	if(ret[x]>ans){ans=ret[x];ct=1;}
	else if(ret[x]==ans){ct++;}
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=m;i++){
		scanf("%d",&x);
		mark[x]=1;
	}
	for(int i=1,a,b,c;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
	}
	dfs(1,0,0,0);
	for(int j=1;j<=17;j++)
		for(int i=1;i<=n;i++)
			fa[i][j]=fa[fa[i][j-1]][j-1];
	redfs(1,-1e18,0);
	dfs_ans(1,0);
	cout<<ans<<' '<<ct<<endl;
	return 0;
}
