#include<bits/stdc++.h>
using namespace std;
const int M=1e5+5;
int n,Q;
int h[M],nx[M<<1],to[M<<1],tot;
void add(int a,int b){
	to[++tot]=b;
	nx[tot]=h[a];
	h[a]=tot;
}
struct P30{
	int fa[M];
	bool mark[M];
	void dfs(int x){
		if(!mark[x]){mark[x]=1;return;}
		for(int i=h[x];i;i=nx[i])dfs(to[i]);
	}
	void dfs1(int x){
		mark[x]=0;
		for(int i=h[x];i;i=nx[i])dfs1(to[i]);
	}
	void solve(){
		while(Q--){
			int a,b;
			scanf("%d%d",&a,&b);
			if(a==1)dfs(b);
			else if(a==2)dfs1(b);
			else puts(mark[b]?"Yes":"No");
		} 
	}
}p30;
struct P0{
	int fa[M],dep[M],sz[M],son[M],top[M],L[M],R[M],id[M],T;
	void dfs(int x){
		sz[x]=1;
		for(int i=h[x];i;i=nx[i]){
			int y=to[i];
			fa[y]=x,dep[y]=dep[x]+1;
			dfs(y);
			sz[x]+=sz[y];
			if(sz[son[x]]<sz[y])son[x]=y;
		}
	}
	void dfs_top(int x,int tp){
		id[L[x]=++T]=x;
		top[x]=tp;
		if(son[x])dfs_top(son[x],tp);
		for(int i=h[x];i;i=nx[i]){
			int y=to[i];
			if(y==son[x])continue;
			dfs_top(y,y);
		}
		R[x]=T;
	}
	struct node{
		int sum,mx;
		node operator +(const node &_)const{
			return (node){sum+_.sum,max(mx+_.sum,_.mx)};
		}
	}tr[M<<2];
	bool lz[M<<2];
	void up(int p){
		tr[p]=tr[p<<1]+tr[p<<1|1];
	}
	void modi(int p){
		lz[p]=1;
		tr[p]=(node){0,0};
	}
	void down(int p){
		if(!lz[p])return;
		modi(p<<1);
		modi(p<<1|1);
		lz[p]=0;
	}
	void update(int l,int r,int x,int d,int p){
		if(l==r){
			tr[p].sum+=d,tr[p].mx=tr[p].sum+dep[id[l]];
			return;
		}
		down(p);
		int mid=(l+r)>>1;
		if(x<=mid)update(l,mid,x,d,p<<1);
		else update(mid+1,r,x,d,p<<1|1);
		up(p);
		cout<<tr[p].mx<<' '<<tr[p].sum<<endl;
	}
	void clear(int l,int r,int ll,int rr,int p){
		if(ll<=l&&rr>=r){modi(p);return;}
		down(p);
		int mid=(l+r)>>1;
		if(ll<=mid)clear(l,mid,ll,rr,p<<1);
		if(rr>mid)clear(mid+1,r,ll,rr,p<<1|1);
		up(p);
	}
	node query(int l,int r,int ll,int rr,int p){
		if(ll==l&&rr==r){
			return tr[p];
		}
		down(p);
		int mid=(l+r)>>1;
		if(rr<=mid)return query(l,mid,ll,rr,p<<1);
		else if(ll>mid)return query(mid+1,r,ll,rr,p<<1|1);
		else return query(l,mid,ll,mid,p<<1)+query(mid+1,r,mid+1,rr,p<<1|1);
	}
	int query(int x){
		node res=(node){0,0};
		while(x){
			res=query(1,n,L[top[x]],L[x],1)+res,x=fa[top[x]];
		}
		return res.mx;
	}
	void solve(){
		dfs(1);
		dfs_top(1,1);
		while(Q--){
			int a,b;
			scanf("%d%d",&a,&b);
			if(a==1)update(1,n,L[b],1,1);
			else if(a==2){
				clear(1,n,L[b],R[b],1);
				int mx=query(b);
				if(mx>dep[b])update(1,n,L[b],dep[b]-mx,1);
			}
			else puts(query(b)>dep[b]?"Yes":"No");
		}
	}
}p0;
int main(){
	scanf("%d%d",&n,&Q);
	for(int f,i=2;i<=n;i++){
		scanf("%d",&f);
		add(f,i);
	}
	p0.solve();
	return 0;
}

