#include<bits/stdc++.h>
#define M 100005
#define LL long long 
#define db double
using namespace std;
bool __1;
int n,L,R;
struct edge{
	int to,fr;LL co;
}E[M<<1];
int lst[M],tote;
void addedge(int a,int b,int c){
	E[++tote]=(edge){b,lst[a],c};
	lst[a]=tote;
}
namespace P2{
	const int SZ=5005;
	LL dis[SZ];
	int dep[SZ];
	int fa[SZ][13];
	void dfs(int v,int f){
		dep[v]=dep[f]+1;
		fa[v][0]=f;
		for(int i=lst[v];i;i=E[i].fr){
			int u=E[i].to;
			if(u==f)continue;
			dis[u]=dis[v]+E[i].co;
			dfs(u,v);
		}
	}
	void Up(int &x,int stp){
		for(int i=0;i<13;i++)
			if((1<<i)&stp)
				x=fa[x][i];
	}
	int LCA(int a,int b){
		if(dep[a]<dep[b])swap(a,b);
		Up(a,dep[a]-dep[b]);
		if(a==b)return a;
		for(int i=12;i>=0;i--)
			if(fa[a][i]!=fa[b][i])
				a=fa[a][i],b=fa[b][i];
		return fa[a][0];
	}
	void solve(){
		dfs(1,0);
		for(int i=1;i<13;i++)
			for(int j=1;j<=n;j++)	
				fa[j][i]=fa[fa[j][i-1]][i-1];
		db ans=0;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++){
				int c=LCA(i,j);
				int d=dep[i]+dep[j]-dep[c]*2;
				if(d>=L&&d<=R)
					ans=max(ans,(db)(dis[i]+dis[j]-dis[c]*2)/d);
			}
		printf("%.3lf\n",ans);
	}
}
namespace P5{
	int deg[M];
	bool check(){
		for(int i=1;i<=n;i++)
			for(int j=lst[i];j;j=E[j].fr)
				deg[E[j].to]++;
		int c=0;
		for(int i=1;i<=n;i++)c+=deg[i]==1;
		return c<=2;
	}
	int V[M],len;
	void dfs(int v,int f){
		for(int i=lst[v];i;i=E[i].fr){
			int u=E[i].to;
			if(u==f)continue;
			V[++len]=E[i].co;
			dfs(u,v);
		}
	}
	LL sum[M];
	struct Poi{
		LL x,y;
	};
	struct Seg{
		struct Tree{
			int L,R;
			vector<Poi>x;
			
		}T[M<<2];
		void Merge(vector<Poi>&c,vector<Poi>&a,vector<Poi>&b){
			c.clear();
			int r=a.size()-1;
			for(int i=0;i<=r;i++)c.push_back(a[i]);
			for(int i=0,ed=b.size();i<ed;i++){
				while(r&&1.0*(b[i].y-c[r-1].y)*(c[r].x-c[r-1].x)<1.0*(c[r].y-c[r-1].y)*(b[i].x-c[r-1].x))r--,c.pop_back();
				c.push_back(b[i]);r++;
			}
		}
		void Up(int p){
			Merge(T[p].x,T[p<<1].x,T[p<<1|1].x);
		}
		void Build(int l,int r,int p){
			T[p].L=l,T[p].R=r;
			if(l==r){
				T[p].x.push_back((Poi){l,sum[l]});
				return;
			}
			int mid=(l+r)>>1;
			Build(l,mid,p<<1);
			Build(mid+1,r,p<<1|1);
			Up(p);
		}
		db find(vector<Poi>&x,Poi p){
			int l=0,r=x.size()-2,res=r+1;
			while(l<=r){
				int mi=(l+r)>>1;
				if(1.0*(p.y-x[mi].y)*(x[mi+1].x-x[mi].x)<1.0*(x[mi+1].y-x[mi].y)*(p.x-x[mi].x))res=mi,r=mi-1;
				else l=mi+1;
			}
			return (db)(p.y-x[res].y)/(p.x-x[res].x);
		}
		db Query(int l,int r,Poi c,int p){
			if(T[p].L==l&&r==T[p].R)return find(T[p].x,c);
			int mid=(T[p].L+T[p].R)>>1;
			if(mid>=r)return Query(l,r,c,p<<1);
			else if(mid<l)return Query(l,r,c,p<<1|1);
			else return max(Query(l,mid,c,p<<1),Query(mid+1,r,c,p<<1|1));
		}
	}Tr;
	void solve(){
		for(int i=1;i<=n;i++)
			if(deg[i]==1){
				dfs(i,0);
				break;
			}
		db ans=0;
		for(int i=1;i<=len;i++)sum[i]=sum[i-1]+V[i];
		Tr.Build(0,len,1);
		for(int i=L;i<=len;i++)ans=max(ans,Tr.Query(max(0,i-R),i-L,(Poi){i,sum[i]},1));
		printf("%.3lf\n",ans);
	}
}
namespace Px{
	const LL oo=2e18;
	struct Seg{
		struct Tree{
			int L,R;
			LL x;
		}T[M<<2];
		int TID[M];
		void Up(int p){
			T[p].x=min(T[p<<1].x,T[p<<1|1].x);
		}
		void Build(int l,int r,int p){
			T[p].L=l,T[p].R=r;
			T[p].x=oo;
			if(l==r){
				if(l==0)T[p].x=0;
				TID[l]=p;
				return;
			}
			int mid=(l+r)>>1;
			Build(l,mid,p<<1);
			Build(mid+1,r,p<<1|1);
			Up(p);
		}
		void Update(int x,LL y){
			bool f=0;int p=TID[x];
			if(y==oo)T[p].x=oo,f=1;
			else if(y<T[p].x)f=1,T[p].x=y;
			if(!f)return;
			for(p>>=1;p;p>>=1)Up(p);
		}
		LL Query(int l,int r,int p){
			if(T[p].L==l&&r==T[p].R)return T[p].x;
			int mid=(T[p].L+T[p].R)>>1;
			if(mid>=r)return Query(l,r,p<<1);
			else if(mid<l)return Query(l,r,p<<1|1);
			else return min(Query(l,mid,p<<1),Query(mid+1,r,p<<1|1));
		}
	}Tr;
	
	int srt,rt,SZ;
	int mn,sz[M],mxd;
	bool mark[M];
	vector<int>son[M];
	LL lim;
	bool dfs(int v,int fa,LL dis,int dep,bool f){
		if(dep>R)return 0;
		if(!f){//Query
			if(Tr.Query(max(0,L-dep),R-dep,1)<=dis-lim*dep)return 1;
		}else//add
			Tr.Update(dep,lim*dep-dis);
		mxd=max(mxd,dep);
		for(int i=lst[v];i;i=E[i].fr){
			int u=E[i].to;
			if(u==fa||mark[u])continue;
			if(dfs(u,v,dis+E[i].co,dep+1,f))return 1;
		}return 0;
	}
	bool Getans(int v){
		mxd=0;
		bool f=0;
		for(int i=lst[v];i;i=E[i].fr){
			int u=E[i].to;
			if(mark[u])continue;
			if(dfs(u,v,E[i].co,1,0)){f=1;break;}
			dfs(u,v,E[i].co,1,1);
		}
		f|=Tr.Query(L,R,1)<=0;
		for(int i=1;i<=mxd;i++)Tr.Update(i,oo);
		return f;
	}
	void dfsrt(int v,int f){
		sz[v]=1;int mx=0;
		for(int i=lst[v];i;i=E[i].fr){
			int u=E[i].to;
			if(u==f||mark[u])continue;
			dfsrt(u,v);
			sz[v]+=sz[u];
			mx=max(mx,sz[u]);
		}
		mx=max(mx,SZ-sz[v]);
		if(mx<mn)mn=mx,rt=v;
	}
	bool dfssolve(int v){
		bool f=Getans(v);mark[v]=1;
		for(int i=lst[v];i;i=E[i].fr){
			int u=E[i].to;
			if(mark[u])continue;
			SZ=sz[u],mn=2e9,dfsrt(u,v);
			son[v].push_back(rt);
			f|=dfssolve(rt);
		}return f;
	}
	bool dfssol(int v){
		if(Getans(v))return 1;mark[v]=1;
		for(int i=0,sz=son[v].size();i<sz;i++)
			if(dfssol(son[v][i]))return 1;
		return 0;
	}
	bool check(db x){
		lim=x;
		memset(mark,0,sizeof(mark));
		if(!srt){
			SZ=n,mn=2e9,dfsrt(1,0);
			srt=rt;
			return dfssolve(rt);
		}else return dfssol(srt);
	}
	void solve(){
		Tr.Build(0,R,1);
		LL l=oo,r=0,res=0;
		for(int i=1;i<=n;i++)
			for(int j=lst[i];j;j=E[j].fr){
				E[j].co*=5000;
				l=min(l,E[j].co);
				r=max(r,E[j].co);
			}
		while(l<=r){
			db mid=(l+r)>>1;
			if(check(mid))l=mid+1,res=mid;
			else r=mid-1;
		}
		printf("%.3lf\n",res/5000.0);
	}
}
bool __2;
int main(){
//	printf("%lf\n",(&__2-&__1)/1024.0/1024);
	freopen("rebuild.in","r",stdin);
	freopen("rebuild.out","w",stdout);
	scanf("%d%d%d",&n,&L,&R);
	for(int i=1,a,b,c;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		addedge(a,b,c);
		addedge(b,a,c);
	}
	if(n<=5000)P2::solve();
	else if(P5::check())P5::solve();
	else Px::solve();
	return 0;
}