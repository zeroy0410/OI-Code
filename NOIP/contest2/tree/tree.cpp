#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n,m,h[M],tt,dep[M],sz[M],fa[M],top[M],son[M],id[M],dfn,A[M],R[M],flip[2];
struct BIT{
	LL C[M];
	void Add(int x,LL d){
		x++;
		while(x<=n+1){
			C[x]+=d;
			x+=(x&-x);
		}
	}
	LL sum(int x){
		x++;LL res=0;
		while(x){
			res+=C[x];
			x-=(x&-x);
		}
		return res;
	}
	LL query(int l,int r){
		if(l>r)return 0;
		return sum(r)-sum(l-1);
	}
}sum[2][2],cnt[2][2];
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
void dfs(int x,int f,int d){
	dep[x]=d;sz[x]=1;fa[x]=f;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x,d+1);
		sz[x]+=sz[u];
		if(sz[u]>sz[son[x]])son[x]=u;
	}
}
void dfs_top(int x,int tp){
	top[x]=tp;id[x]=++dfn;
	if(son[x])dfs_top(son[x],tp);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==fa[x]||u==son[x])continue;
		dfs_top(u,u);
	}
	R[x]=dfn;
}
void Update(int x,int c){
	int a=(dep[x]&1),b=A[x];
	cnt[a][b].Add(id[x],c);
	while(x){
		sum[a][b].Add(id[x],c*x);
		x=fa[top[x]];
	}
}
LL Query(int x){
	int del=0;
	LL ans=0;
	while(x){
		ans+=sum[0][flip[0]].query(id[top[x]],id[x]-1)+sum[1][flip[1]].query(id[top[x]],id[x]-1);
		ans+=(cnt[0][flip[0]].query(id[x],R[x])+cnt[1][flip[1]].query(id[x],R[x])-del)*x;
		x=top[x];
		del=cnt[0][flip[0]].query(id[x],R[x])+cnt[1][flip[1]].query(id[x],R[x]);
		x=fa[x];
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	dfs(1,0,1);
	dfs_top(1,1);
	flip[0]=flip[1]=1;
	for(int i=1;i<=n;i++)Update(i,1);
	while(m--){
		int op,x;
		scanf("%d%d",&op,&x);
		if(op==1)
			flip[!(dep[x]&1)]^=1;
		else if(op==2){
			Update(x,-1);
			A[x]^=1;
			Update(x,1);
		}
		else printf("%lld\n",Query(x));
	}
	return 0;
}
