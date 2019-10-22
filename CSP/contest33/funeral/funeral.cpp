#include<bits/stdc++.h>
#define M 100005
using namespace std;
struct YD_tree1{
	struct tr_node{
		int sum[3],l,r,len;
		int mark;
	}tree[M<<2];
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;fa.sum[0]=fa.len=r-l+1;
		fa.mark=-1;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
	}
	void up(int p){
		for(int i=0;i<3;i++)
			fa.sum[i]=lson.sum[i]+rson.sum[i];
	}
	void down(int p){
		if(fa.mark==-1)return;
		lson.mark=rson.mark=fa.mark;
		for(int i=0;i<3;i++){
			lson.sum[i]=(i==fa.mark?lson.len:0);
			rson.sum[i]=(i==fa.mark?rson.len:0);
		}
	}
	int query(int l,int r,int col,int p){
		if(l>r)return 0;
		if(fa.l==l&&fa.r==r)return fa.sum[col];
		int mid=(fa.l+fa.r)>>1;
		down(p);
		if(r<=mid)return query(l,r,col,p<<1);
		else if(l>mid)return query(l,r,col,p<<1|1);
		return query(l,mid,col,p<<1)+query(mid+1,r,col,p<<1|1);
	}
	void update(int l,int r,int col,int p){
		if(fa.l==l&&fa.r==r){
			for(int i=0;i<3;i++)
				fa.sum[i]=(i==col?fa.len:0);
			fa.mark=col;
			return;
		}
		down(p);
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)update(l,r,col,p<<1);
		else if(l>mid)update(l,r,col,p<<1|1);
		else {
			update(l,mid,col,p<<1);
			update(mid+1,r,col,p<<1|1);
		}
		up(p);
	}
}Tr1;
struct POI{ int t,x; };
struct YD_tree2{
	struct tr_node{
		int l,r;
		POI mark,poi;
		void reset(POI x){ if(mark.t<x.t)mark=x; }
		void resetp(POI x){ if(poi.t<x.t)poi=x; }
	}tree[M<<2];
	int tid[M],stk[M<<2],top;
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;
		fa.mark.t=fa.mark.x=0;
		fa.poi.t=fa.poi.x=0;
		if(l==r){tid[l]=p;return;}
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
	}
	void down(int p){
		lson.reset(fa.mark);
		rson.reset(fa.mark);
		lson.resetp(fa.poi);
		rson.resetp(fa.poi);
	}
	void update(int l,int r,POI d,int p){
		if(fa.l==l&&fa.r==r){
			fa.reset(d);
			return;
		}
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)update(l,r,d,p<<1);
		else if(l>mid)update(l,r,d,p<<1|1);
		else {
			update(l,mid,d,p<<1);
			update(mid+1,r,d,p<<1|1);
		}
	}
	void updatep(int l,int r,POI d,int p){
		if(fa.l==l&&fa.r==r){
			fa.resetp(d);
			return;
		}
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)updatep(l,r,d,p<<1);
		else if(l>mid)updatep(l,r,d,p<<1|1);
		else {
			updatep(l,mid,d,p<<1);
			updatep(mid+r,r,d,p<<1|1);
		}
	}
	void changep(int x,POI d){tree[tid[x]].poi=d;}
	POI query(int x){
		for(int p=tid[x]>>1;p;p>>=1)stk[++top]=p;
		while(top)down(stk[top--]);
		return tree[tid[x]].poi;
	}
	POI queryp(int x){
		for(int p=tid[x]>>1;p;p>>=1)stk[++top]=p;
		while(top)down(stk[top--]);
		return tree[tid[x]].poi;
	}
}Tr2;
#undef fa
#undef lson
#undef rson
int n,m,h[M],tt;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int son[M],sz[M],fa[M],dep[M],top[M],tot,L[M],R[M],ln[M];
void dfs(int x,int f,int d){
	dep[x]=d;fa[x]=f;son[x]=0;sz[x]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x,d+1);
		sz[x]+=sz[u];
		if(sz[u]>sz[son[x]])son[x]=u;
	}
}
void dfs_top(int x,int tp){
	top[x]=tp;L[x]=++tot;ln[tot]=x;
	if(son[x])dfs_top(son[x],tp);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==fa[x]||u==son[x])continue;
		dfs_top(u,u);
	}
	R[x]=tot;
}
int LCA(int a,int b){
	while(top[a]!=top[b]){
		if(dep[top[a]]>dep[top[b]])swap(a,b);
		a=fa[top[a]];
	}
	return dep[a]>dep[b]?b:a;
}
int Up(int a,int to){
	while(dep[top[a]]>to)a=fa[top[a]];
	return ln[L[a]-dep[a]+to];
}
POI Max(POI a,POI b){
	if(a.t>b.t)return a;
	return b;
}
int query(int a,int b,int col){
	int ans=0;
	while(top[a]!=top[b]){
		if(dep[top[a]]<dep[top[b]])swap(a,b);
		int d=top[a],t=fa[d];
		ans+=Tr1.query(L[d]+1,L[a],col,1);
		ans+=Max(Tr2.query(L[t]),Tr2.queryp(L[d])).x==col;
		a=t;
	}
	if(dep[a]<dep[b])swap(a,b);
	ans+=Tr1.query(L[b]+1,L[a],col,1);
	return ans;
}
void change(int a,int b,int c1,int c2,int t1,int t2){
	if(son[a])Tr1.update(L[son[a]],L[son[a]],c2,1);
	if(son[b])Tr1.update(L[son[b]],L[son[b]],c2,1);
	while(top[a]!=top[b]){
		if(dep[top[a]]>dep[top[b]])swap(a,b);
		int d=top[a],t=fa[d];
		Tr1.update(L[d]+1,L[a],c1,1);
		Tr1.update(L[son[t]],L[son[t]],c2,1);
		Tr2.update(L[d],L[a],(POI){t2,c2},1);
		Tr2.changep(L[d],(POI){t1,c1});
		a=t;
	}
	if(dep[a]<dep[b])swap(a,b);
	if(b>1)Tr1.update(L[b],L[b],c2,1),Tr2.changep(L[b],(POI){t2,c2});
	Tr1.update(L[b]+1,L[a],c1,1);
	Tr2.update(L[b],L[a],(POI){t2,c2},1);
}
int main(){
	scanf("%d",&n);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	dfs(1,0,0);dfs_top(1,1);
	scanf("%d",&m);
	Tr1.build(1,n,1);Tr2.build(1,n,1);
	for(int i=1,op,x,y,z,c1,c2;i<=m;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d%d",&x,&y,&c1);
			printf("%d\n",query(x,y,c1));
		}
		else if(op==2){
			scanf("%d%d%d%d",&x,&y,&c1,&c2);
			change(x,y,c1,c2,i*2,i*2-1);
		}
		else {
			scanf("%d%d%d",&x,&y,&c1);
			z=LCA(x,y);
			if(x==y)Tr1.update(1,n,c1,1),Tr2.updatep(1,n,(POI){i<<1,c1},1);
			else if(z==y){
				int t=Up(x,dep[z]+1);
				Tr1.update(2,L[t]-1,c1,1);
				Tr1.update(R[t]+1,n,c1,1);
				Tr2.updatep(2,L[t]-1,(POI){i<<1,c1},1);
				Tr2.updatep(R[t]+1,n,(POI){i<<1,c1},1);
			}else Tr1.update(L[y]+1,R[y],c1,1),Tr2.updatep(L[y]+1,R[y],(POI){i<<1,c1},1);
		}
	}
	return 0;
}
