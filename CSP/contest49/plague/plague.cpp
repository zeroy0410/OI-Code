#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,m,h[M],tt;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int L[M],R[M],dep[M],sz[M],son[M],fa[M],top[M],ln[M],tot;
void dfs(int x,int f,int d){
	dep[x]=d;sz[x]=1;son[x]=0;fa[x]=f;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x,d+1);
		sz[x]+=sz[u];
		if(sz[u]>sz[son[x]])son[x]=u;
	}
}
void dfs_top(int x,int tp){
	L[x]=++tot;ln[tot]=x;top[x]=tp;
	if(son[x])dfs_top(son[x],tp);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==fa[x]||u==son[x])continue;
		dfs_top(u,u);
	}
	R[x]=tot;
}
struct node{
	int l,r,sum,mx;
	node operator + (const node& res)const{
		return (node){l,res.r,sum+res.sum,max(mx+res.sum,res.mx)};
	}
	void reset(){mx=sum=0;}
}tree[M<<2];
struct YD_tree{
	bool lz[M<<2];
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
	void up(int p){ fa=lson+rson; }
	void down(int p){
		if(lz[p]){
			lz[p<<1]=lz[p<<1|1]=1;
			lson.reset();
			rson.reset();
			lz[p]=0;
		}
	}
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;fa.mx=fa.sum=0;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
		up(p);
	}
	void clear(int l,int r,int p){
		if(fa.l==l&&fa.r==r){
			lz[p]=1;
			fa.reset();
			return;
		}
		down(p);
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)clear(l,r,p<<1);
		else if(l>mid)clear(l,r,p<<1|1);
		else {
			clear(l,mid,p<<1);
			clear(mid+1,r,p<<1|1);
		}
		up(p);
	}
	void update(int x,int d,int p){
		if(fa.l==x&&fa.r==x){
			fa.sum+=d;
			fa.mx=fa.sum+dep[ln[x]];
			return;
		}
		down(p);
		int mid=(fa.l+fa.r)>>1;
		if(x<=mid)update(x,d,p<<1);
		else update(x,d,p<<1|1);
		up(p);
	}
	node query(int l,int r,int p){
		if(l==fa.l&&r==fa.r){
			return fa;
		}
		down(p);
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)return query(l,r,p<<1);
		else if(l>mid)return query(l,r,p<<1|1);
		return query(l,mid,p<<1)+query(mid+1,r,p<<1|1);
	}
#undef fa
#undef lson
#undef rson
}Tr;
int query(int x){
	node res=(node){0,0};
	while(x) {
		res=Tr.query(L[top[x]],L[x],1)+res,x=fa[top[x]];
	}
	return res.mx;
}
int main(){
//	freopen("plague.in","r",stdin);
//	freopen("plague.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=2,x;i<=n;i++){
		scanf("%d",&x);
		Add(i,x);Add(x,i);
	}
	dfs(1,0,0);
	dfs_top(1,1);
	Tr.build(1,n,1);
	for(int i=1,op,x;i<=m;i++){
		scanf("%d%d",&op,&x);
		if(op==1)Tr.update(L[x],1,1);
		else if(op==2){
			Tr.clear(L[x],R[x],1);
			int mx=query(x);
			if(mx>dep[x])Tr.update(L[x],dep[x]-mx,1);
		}
		else puts(query(x)>dep[x]?"Yes":"No");
	}
	return 0;
}
