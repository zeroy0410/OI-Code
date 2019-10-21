#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,m,h[M],tt;
struct edge{
	int nxt,to;
}G[M<<1];
struct Edge{
	int a,b,c;
}E[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
struct P15{
	int fa[M],L[M],R[M],tot;
	bool mark[1005];
	void dfs(int x,int f){
		fa[x]=f;L[x]=++tot;
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to;
			if(u==f)continue;
			dfs(u,x);
		}
		R[x]=tot;
	}
	void solve(){
		scanf("%d",&m);
		while(m--){
			int op,x,y,col1,col2,rt,col;
			scanf("%d",&op);
			if(op==1){
				scanf("%d%d%d",&x,&y,&col);
				dfs(x,0);
				memset(mark,0,sizeof(mark));
				while(y!=fa[x]){
					mark[y]=1;
					y=fa[y];
				}
				int ans=0;
				for(int i=1;i<n;i++)
					if(mark[E[i].a]&&mark[E[i].b]&&E[i].c==col)ans++;
				printf("%d\n",ans);
			}
			else if(op==2){
				scanf("%d%d%d%d",&x,&y,&col1,&col2);
				dfs(x,0);
				memset(mark,0,sizeof(mark));
				while(y!=fa[x]){
					mark[y]=1;
					y=fa[y];
				}
				for(int i=1;i<n;i++){
					if(mark[E[i].a]&&mark[E[i].b])E[i].c=col1;
					else if(mark[E[i].a]||mark[E[i].b])E[i].c=col2;
				}
			}
			else {
				scanf("%d%d%d",&rt,&x,&col);
				tot=0;
				dfs(rt,0);
				for(int i=1;i<n;i++){
					if(L[E[i].a]>=L[x]&&L[E[i].a]<=R[x]&&
							L[E[i].b]>=L[x]&&L[E[i].b]<=R[x])
						E[i].c=col;
				}
			}
		}
	}
}p15;
//struct P50{
//	struct Tree{
//		struct node{
//			int l,r,s[3];
//			int mark;
//			int len(){
//				return r-l+1;
//			}
//		}tree[M<<2];
//#define fa tree[p]
//#define lson tree[p<<1]
//#define rson tree[p<<1|1]
//		void up(int p){
//			for(int i=0;i<3;i++)
//				fa.s[i]=lson.s[i]+rson.s[i];
//		}
//		void down(int p){
//			if(fa.mark!=-1){
//				for(int i=0;i<3;i++){
//					if(i==mark){
//						lson.s[i]=lson.len();
//						rson.s[i]=rson.len();
//					}
//					else {
//						lson.s[i]=0;
//						rson.s[i]=0;
//					}
//				}
//				lson.mark=fa.mark;
//				rson.mark=fa.mark;
//				fa.mark=-1;
//			}
//		}
//		void build(int l,int r,int p){
//			fa.l=l;fa.r=r;fa.s[0]=r-l+1;fa.s[1]=fa.s[2]=0;
//			if(l==r)return;
//			int mid=(l+r)>>1;
//			build(l,mid,p<<1);
//			build(mid+1,r,p<<1|1);
//		}
//		void update(int l,int r,int d,int p){
//			if(fa.l==l&&fa.r==r){
//				fa.s[d]=fa.len();
//				if(d!=0)fa.s[0]=0;
//				if(d!=1)fa.s[1]=0;
//				if(d!=2)fa.s[2]=0;
//				fa.mark=d;
//				return;
//			}
//			int mid=(fa.l+fa.r)>>1;
//			down(p);
//			if(r<=mid)update(l,r,d,p<<1);
//			else if(l>mid)update(l,r,
//	int fa[M],sz[M],top[M],ID[M],tot;
//	
//	void dfs(int x,int f,
//	void solve(){
//
//	}
//}p50;
struct P30{
	int dep[M],fa[M][20];
	void dfs(int x,int f,int d){
		fa[x][0]=f;dep[x]=d;
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to;
			if(u==f)continue;
			dfs(u,x,d+1);
		}
	}
	int LCA(int a,int b){
		if(dep[a]>dep[b])swap(a,b);
		int step=dep[b]-dep[a];
		for(int i=19;i>=0;i--)
			if(step&1<<i)
				b=fa[b][i];
		if(a==b)return a;
		for(int i=19;i>=0;i--)
			if(fa[a][i]!=fa[b][i])
				a=fa[a][i],b=fa[b][i];
		return fa[a][0];
	}
	void solve(){
		dfs(1,0,0);
		for(int j=1;j<=19;j++)
			for(int i=1;i<=n;i++)
				fa[i][j]=fa[fa[i][j-1]][j-1];
		scanf("%d",&m);
		while(m--){
			int op,x,y,col;
			scanf("%d%d%d%d",&op,&x,&y,&col);
			if(op==1){
				if(col==1||col==2)puts("0");
				else {
					int lca=LCA(x,y);
					printf("%d\n",dep[x]-dep[lca]+dep[y]-dep[lca]);
				}
			}
		}
	}
}p30;
int main(){
	freopen("funeral.in","r",stdin);
	freopen("funeral.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
		E[i]=(Edge){a,b,0};
	}
	if(n<=1000)p15.solve();
	else p30.solve();
	return 0;
}
