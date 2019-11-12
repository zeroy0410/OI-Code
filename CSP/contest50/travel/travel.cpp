#include<bits/stdc++.h>
#define M 100005
using namespace std;
const int S=70;
int n,m,h[M],tt;
struct edge{
	int nxt,to,co;
}G[M<<1];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
int fa[M][18],dep[M],fd[M][18],dis[M];
void dfs(int x,int f,int d,int fdd,int ds){
	fa[x][0]=f;dep[x]=d;fd[x][0]=fdd;dis[x]=ds;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x,d+1,G[i].co,ds+G[i].co);
	}
}
int Fa[S+5][M][18];
int Jump(int x,int p){
	for(int i=17;i>=0;i--){
		if(fd[x][i]<=p){
			p-=fd[x][i];
			x=fa[x][i];
		}
	}
	return x;
}
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
int main(){
//	freopen("travel.in","r",stdin);
//	freopen("travel.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,a,b,c;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
	}
	dfs(1,0,1,0,0);
	for(int j=1;j<=17;j++){
		for(int i=1;i<=n;i++){
			fa[i][j]=fa[fa[i][j-1]][j-1];
			fd[i][j]=fd[i][j-1]+fd[fa[i][j-1]][j-1];
		}
	}
	for(int k=2;k<=S;k++){
		for(int i=1;i<=n;i++)
			Fa[k][i][0]=Jump(i,k);
		for(int j=1;j<=17;j++)
			for(int i=1;i<=n;i++)
				Fa[k][i][j]=Fa[k][Fa[k][i][j-1]][j-1];
	}
	scanf("%d",&m);
	for(int _=1;_<=m;_++){
		int u,v,p;
		scanf("%d%d%d",&u,&v,&p);
		int lca=LCA(u,v);
		if(p>S){
			int ans=0;
			while(1){
				int t=Jump(u,p);
				if(dep[t]>dep[lca])u=t,ans++;
				else break;
			}
			while(1){
				int t=Jump(v,p);
				if(dep[t]>dep[lca])v=t,ans++;
				else break;
			}
			int Dis=dis[u]+dis[v]-2*dis[lca];
			if(Dis==0);
			else if(Dis<=p)ans++;
			else ans+=2;
			printf("%d\n",ans);
		}
		else {
			int ans=0;
			for(int i=17;i>=0;i--){
				if(dep[Fa[p][u][i]]>dep[lca]){
					ans+=1<<i;
					u=Fa[p][u][i];
				}
			}
			for(int i=17;i>=0;i--){
				if(dep[Fa[p][v][i]]>dep[lca]){
					ans+=1<<i;
					v=Fa[p][v][i];
				}
			}
			int Dis=dis[u]+dis[v]-2*dis[lca];
			if(Dis==0);
			else if(Dis<=p)ans++;
			else ans+=2;
			printf("%d\n",ans);
		}
	}
	return 0;
}
