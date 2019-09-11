#include<bits/stdc++.h>
#define M 30005
using namespace std;
int n,m,h[M],tot;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tot]=(edge){h[a],b};
	h[a]=tot;
}
struct Node{int a,b;}A[M];
void tomax(int &x,int y){if(y>x)x=y;}
struct node{
	int l,r;
	int f[2][2][2];
	int ds[2][2];
	node operator + (const node& res){
		node tmp;
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				tmp.f[0][i][j]=0;
				if(f[0][i][0]&&res.f[0][0][j])tomax(tmp.f[0][i][j],f[0][i][0]+res.f[0][0][j]);
				if(f[0][i][1]&&res.f[0][1][j])tomax(tmp.f[0][i][j],f[0][i][1]+res.f[0][1][j]);
			}
			tmp.ds[0][i]=ds[0][i];
			if(f[0][i][0])tomax(tmp.ds[0][i],f[0][i][0]+res.ds[0][0]);
			if(f[0][i][1])tomax(tmp.ds[0][i],f[0][i][1]+res.ds[0][1]);
		}
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				tmp.f[1][i][j]=0;
				if(res.f[1][i][0]&&f[1][0][j])tomax(tmp.f[1][i][j],res.f[1][i][0]+f[1][0][j]);
				if(res.f[1][i][1]&&f[1][1][j])tomax(tmp.f[1][i][j],res.f[1][i][1]+f[1][1][j]);
			}
			tmp.ds[1][i]=res.ds[1][i];
			if(res.f[1][i][0])tomax(tmp.ds[1][i],res.f[1][i][0]+ds[1][0]);
			if(res.f[1][i][1])tomax(tmp.ds[1][i],res.f[1][i][1]+ds[1][1]);
		}
		tmp.l=l;tmp.r=res.r;
		return tmp;
	}
	void reset(int d1,int d2){
		for(int i=0;i<2;i++){
			f[i][0][0]=d1;
			f[i][1][1]=d2;
			f[i][0][1]=(d1&&d2)*2;
			f[i][1][0]=(d1&&d2)*2;
		}
		ds[0][0]=max(f[0][0][0],f[0][0][1]);
		ds[0][1]=max(f[0][1][0],f[0][1][1]);
		ds[1][0]=max(f[1][0][0],f[1][0][1]);
		ds[1][1]=max(f[1][1][0],f[1][1][1]); 
	}
}tree[M<<2];
int ln[M];
struct P100{
	#define fa tree[p]
	#define lson tree[p<<1]
	#define rson tree[p<<1|1]
	struct YD_tree{
		void up(int p){
			fa=lson+rson;
		}
		void build(int l,int r,int p){
			fa.l=l;fa.r=r;
			if(l==r){
				fa.reset(A[ln[l]].a,A[ln[l]].b);
				return;
			}
			int mid=(l+r)>>1;
			build(l,mid,p<<1);
			build(mid+1,r,p<<1|1);
			up(p);
		}
		void update(int x,int d1,int d2,int p){
			if(x==fa.l&&x==fa.r){fa.reset(d1,d2);return;}
			int mid=(fa.l+fa.r)>>1;
			if(x<=mid)update(x,d1,d2,p<<1);
			else update(x,d1,d2,p<<1|1);
			up(p);
		}
		node query(int l,int r,int p){
			if(fa.l==l&&fa.r==r)return fa;
			int mid=(fa.l+fa.r)>>1;
			if(r<=mid)return query(l,r,p<<1);
			else if(l>mid)return query(l,r,p<<1|1);
			return query(l,mid,p<<1)+query(mid+1,r,p<<1|1);
		}
		#undef fa
		#undef lson
		#undef rson
	}Tr;
	node ask(int u,int v){
		node tmp;
		bool f=0;
		while(top[u]!=top[v]){
			if(dep[top[u]]>dep[top[v]]){
				if(!f){tmp=Tr.query(ID[top[u]],ID[u],1);f=1;}
				else tmp=Tr.query(ID[top[u]],ID[u],1)+tmp;
				u=fa[top[u]][0];
			}
			else {
				if(!f){tmp=Tr.query(ID[top[v]],ID[v],1);f=1;} 
				else tmp=Tr.query(ID[top[v]],ID[v],1)+tmp;
				v=fa[top[v]][0];
			}
		} 
		if(dep[u]>dep[v]){
			if(!f){tmp=Tr.query(ID[v],ID[u],1);f=1;}
			else tmp=Tr.query(ID[v],ID[u],1)+tmp;
		}
		else {
			if(!f){tmp=Tr.query(ID[u],ID[v],1);f=1;}
			else tmp=Tr.query(ID[u],ID[v],1)+tmp;
		}
		return tmp;
	}
	int sz[M],fa[M][17],son[M],dep[M],top[M],ID[M],tt;
	void dfs(int x,int f,int d){
		fa[x][0]=f;dep[x]=d;sz[x]=1;son[x]=0;
		for(int i=1;i<=16;i++)
			fa[x][i]=fa[fa[x][i-1]][i-1];
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to;
			if(u==f)continue;
			dfs(u,x,d+1);
			sz[x]+=sz[u];
			if(sz[u]>sz[son[x]])son[x]=u;
		}
	}
	void dfs_top(int x,int tp){
		top[x]=tp;ID[x]=++tt;ln[tt]=x;
		if(son[x])dfs_top(son[x],tp);
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to;
			if(u==fa[x][0]||u==son[x])continue;
			dfs_top(u,u);
		}
	}
	int LCA(int u,int v){
		while(top[u]!=top[v]){
			if(dep[top[u]]>dep[top[v]])u=fa[top[u]][0];
			else v=fa[top[v]][0];
		} 
		return dep[u]>dep[v]?v:u;
	}
	int jump(int x,int step){
		for(int i=16;i>=0;i--)
			if(step&1<<i)x=fa[x][i];
		return x;
	}
	node merge(node a,node b){
		node tmp;
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				tmp.f[0][i][j]=0;
				if(a.f[1][i][0]&&b.f[0][0][j])tomax(tmp.f[0][i][j],a.f[1][i][0]+b.f[0][0][j]);
				if(a.f[1][i][1]&&b.f[0][1][j])tomax(tmp.f[0][i][j],a.f[1][i][1]+b.f[0][1][j]);
			}
			tmp.ds[0][i]=a.ds[1][i];
			if(a.f[1][i][0])tomax(tmp.ds[0][i],a.f[1][i][0]+b.ds[0][0]);
			if(a.f[1][i][1])tomax(tmp.ds[0][i],a.f[1][i][1]+b.ds[0][1]);
		}
		return tmp;
	}
	void solve(){
		for(int i=1;i<=n;i++){
			char op[5];
			scanf("%s",op);
			A[i].a=(op[0]=='.');
			A[i].b=(op[1]=='.');
		}
		dfs(1,0,0);
		dfs_top(1,1);
		Tr.build(1,n,1);
		for(int i=1,x,y;i<=m;i++){
			char op[5];
			scanf("%s",op);
			if(op[0]=='C'){
				scanf("%d%s",&x,op);
				A[x].a=(op[0]=='.');
				A[x].b=(op[1]=='.');
				Tr.update(ID[x],A[x].a,A[x].b,1);
			}
			else {
				scanf("%d%d",&x,&y);
				int lca=LCA(x,y);
				node t1=ask(x,lca);
				int e,ans=0;
				if(lca!=y){
//					puts("1");
					e=jump(y,dep[y]-dep[lca]-1);
					node t2=ask(e,y);
					node ee=merge(t1,t2);
					tomax(ans,ee.ds[0][0]);
					tomax(ans,ee.ds[0][1]);
				}
				else {
//					puts("2");
					tomax(ans,t1.ds[1][0]);
					tomax(ans,t1.ds[1][1]);
				}
				printf("%d\n",ans);
			}
		}
	}
}p100;
int main(){
	freopen("war.in","r",stdin);
	freopen("war.out","w",stdout); 
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	p100.solve();
	return 0;
}
