#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,m,A[M],h[M],tt;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int mi[M],L[M],R[M],tot;
char op[15];
struct cz{int l,r,x;};
vector<cz>wk[M<<1];
void dfs(int x,int f){
	int tmp=mi[x];
	L[x]=++tot;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
		mi[x]=min(mi[x],mi[u]);
	}
	R[x]=tot;
	if(tmp<M*2)
		wk[tmp].push_back((cz){L[x],R[x],A[x]});
}
void redfs(int x,int f){
	if(f!=0){
		if(mi[x]<M*2){
			wk[mi[x]].push_back((cz){L[f],L[x]-1,A[f]});
			wk[mi[x]].push_back((cz){R[x]+1,R[f],A[f]});
		}
	}
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		redfs(u,x);
	}
}
vector<int>Q[M<<1];
struct YD_tree{
	struct node{
		int l,r,mx;
	}tree[M<<2];
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
	void down(int p){
		lson.mx=max(lson.mx,fa.mx);
		rson.mx=max(rson.mx,fa.mx);
	}
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;fa.mx=-1;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
	}
	void update(int l,int r,int d,int p){
		if(fa.l==l&&fa.r==r){
			fa.mx=max(fa.mx,d);
			return;
		}
		down(p);
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)update(l,r,d,p<<1);
		else if(l>mid)update(l,r,d,p<<1|1);
		else {
			update(l,mid,d,p<<1);
			update(mid+1,r,d,p<<1|1);
		}
	}
	int query(int x,int p){
		if(fa.l==x&&fa.r==x)return fa.mx;
		int mid=(fa.l+fa.r)>>1;
		down(p);
		if(x<=mid)return query(x,p<<1);
		return query(x,p<<1|1);
	}
}Tr;
int ans[M<<1],acnt;
int main(){
//	freopen("lca.in","r",stdin);
//	freopen("lca.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
	}
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b); Add(b,a);
	}
	memset(mi,0x3f,sizeof(mi));
	Tr.build(1,n,1);
	for(int i=1,x;i<=m;i++){
		scanf("%s%d",op+1,&x);
		if(op[1]=='M')
			mi[x]=min(mi[x],i);
		else 
			Q[i].push_back(x);
	}
	dfs(1,0);
	redfs(1,0);
	int ct=0;
	for(int i=1;i<=m;i++){
		for(int j=0;j<wk[i].size();j++){
			int l=wk[i][j].l,r=wk[i][j].r,x=wk[i][j].x;
			if(l>r)continue;
			Tr.update(l,r,x,0);
		}
		for(int j=0;j<Q[i].size();j++){
			ct++;
			int u=Q[i][j];
			ans[++acnt]=Tr.query(L[u],1);
		}
	}
	for(int i=1;i<=acnt;i++)
		printf("%d\n",ans[i]);
	return 0;
}
