#include<bits/stdc++.h>
#define M 100005
#define LL long long
#pragma GCC optimize(3)
using namespace std;
int n,m,q,h[M],tot;
int x[M],y[M];
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tot]=(edge){h[a],b};
	h[a]=tot;
}
struct node{
	int X,Y,X2,Y2,S,sm;
	node operator + (const node& res){
		return (node){X+res.X,Y+res.Y,X2+res.X2,Y2+res.Y2,S+res.S,sm+res.sm};
	}
	node operator - (const node& res){
		return (node){X-res.X,Y-res.Y,X2-res.X2,Y2-res.Y2,S-res.S,sm-res.sm};
	}
	void reset(int x,int y){
		X+=x;Y+=y;X2+=x*x;Y2+=y*y;S+=x*y;sm++;
	}
}c[M];
int fa[M][22],tt,dep[M],clo[M];
int stk[M],top;
int qq[M];
int mark[M];
void dfs(int xx,int f,int d){
	if(mark[xx]){
		for(int i=mark[xx];i<=top;i++)qq[++qq[0]]=stk[i];
		return;
	}
	stk[++top]=xx;dep[xx]=d;mark[xx]=top;
	fa[xx][0]=f;c[xx]=c[f];c[xx].reset(x[xx],y[xx]);
	for(int j=1;j<22;j++)fa[xx][j]=fa[fa[xx][j-1]][j-1];
	for(int i=h[xx];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		else dfs(u,xx,d+1);
	}
	mark[xx]=0;
	top--;
}
int LCA(int a,int b){
	if(dep[a]>dep[b])swap(a,b);
	int step=dep[b]-dep[a];
	for(int i=21;i>=0;i--)
		if(step&1<<i)b=fa[b][i];
	if(a==b)return a;
	for(int i=21;i>=0;i--)
		if(fa[a][i]!=fa[b][i])
			a=fa[a][i],b=fa[b][i];
	return fa[a][0];
}
double calc(node res){
	double X=res.X,Y=res.Y,X2=res.X2,Y2=res.Y2,S=res.S,sm=res.sm;
	double Xb=X/sm,Yb=Y/sm;
    double A=X2+sm*Xb*Xb-2*X*Xb;
    double B=2*X*Yb-2*sm*Xb*Yb-2*S+2*Xb*Y;
    double C=Yb*Yb*sm-2*Y*Yb+Y2;
    double ai=-4,bi=4*(A+C),ci=B*B-4*A*C;
    return (-bi+sqrt(bi*bi-4*ai*ci))/2/ai;
}
struct Ptree{
	void solve(){
		scanf("%d",&q);
		while(q--){
			int u,v;
			scanf("%d%d",&u,&v);
			int lca=LCA(u,v);
			node res=c[u]+c[v]-c[fa[lca][0]]-c[lca];
			printf("%.5lf\n",calc(res));
		}
	}
}ptree;
node sum[M];
struct Ploop{
	int rt;
	void dfs_clo(int xx,int f,int d){
		clo[xx]=rt;dep[xx]=d;
		fa[xx][0]=f;c[xx]=c[f];c[xx].reset(x[xx],y[xx]);
		for(int j=1;j<22;j++)fa[xx][j]=fa[fa[xx][j-1]][j-1];
		for(int i=h[xx];i;i=G[i].nxt){
			int u=G[i].to;
			if(u==f||mark[u]==2333333)continue;
			dfs_clo(u,xx,d+1);
		}
	}
	void solve(){
		for(int i=1;i<=qq[0];i++)mark[qq[i]]=2333333;
		sum[0].X=sum[0].Y=sum[0].X2=sum[0].Y2=sum[0].sm=0;
		int to=0;
		for(int i=1;i<=qq[0];i++){
			if(i!=1&&qq[i]==qq[1]){to=i-1;break;}
			rt=i;
			dfs_clo(qq[i],0,0);
			sum[i]=sum[i-1];
			sum[i].reset(x[qq[i]],y[qq[i]]);
		}
		scanf("%d",&q);
		while(q--){
			int u,v;
			scanf("%d%d",&u,&v);
			if(clo[u]==clo[v]){
				int lca=LCA(u,v);
				node res=c[u]+c[v]-c[fa[lca][0]]-c[lca];
				printf("%.5lf\n",calc(res));
			}
			else {
				if(clo[u]>clo[v])swap(u,v);
//				cout<<u<<' '<<v<<' '<<clo[u]<<' '<<clo[v]<<endl;
				node res1=c[u]+c[v]+sum[clo[v]-1]-sum[clo[u]];
				node res2=c[u]+c[v]+sum[to]-sum[clo[v]]+sum[clo[u]-1];
				printf("%.5lf\n",min(calc(res1),calc(res2)));
			}
		}
	}
}ploop;	
int main(){
	freopen("inv6.in","r",stdin);
	freopen("inv.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%d",&x[i],&y[i]);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	dfs(1,0,0);
	if(m==n-1)ptree.solve();
	else ploop.solve();
	return 0;
}
