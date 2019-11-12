#include<bits/stdc++.h>
using namespace std;
const int M=1e5+5,S=70;
int n,m;
int h[M],nx[M<<1],to[M<<1],v[M<<1],tot;
void add(int a,int b,int c){
	to[++tot]=b;v[tot]=c;
	nx[tot]=h[a];h[a]=tot;
}
int fa[M][18],dep[M],dis[M];
void dfs(int x){
	for(int i=1;i<18;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=h[x];i;i=nx[i]){
		int y=to[i];
		if(y==fa[x][0])continue;
		fa[y][0]=x,dep[y]=dep[x]+1,dis[y]=dis[x]+v[i];
		dfs(y);
	}
}
int lca(int a,int b){
	if(dep[a]<dep[b])swap(a,b);
	int d=dep[a]-dep[b];
	for(int i=0;i<18;i++)
		if(d&(1<<i))a=fa[a][i];
	if(a==b)return a;
	for(int i=17;i>=0;i--)
		if(fa[a][i]!=fa[b][i])
			a=fa[a][i],b=fa[b][i];
	return fa[a][0];
}
struct P1{
	int solve(int x,int y,int p){
		int l=lca(x,y),ans=0;
		while(dis[x]-dis[l]>=p){
			int d=dis[x];
			for(int i=17;i>=0;i--)
				if(fa[x][i]&&d-dis[fa[x][i]]<=p)x=fa[x][i];
			ans++;
		}
		while(dis[y]-dis[l]>=p){
			int d=dis[y];
			for(int i=17;i>=0;i--)
				if(fa[y][i]&&d-dis[fa[y][i]]<=p)y=fa[y][i];
			ans++;
		}
		return ans+(dis[x]+dis[y]-(dis[l]<<1)+p-1)/p;
	}
}p1;
struct P2{
	int fa[S+1][M][18];
	void init(){
		for(int p=2;p<=S;p++){
			int (*Fa)[18]=fa[p];
			for(int i=1;i<=n;i++){
				int d=dis[i],x=i;
				for(int j=17;j>=0;j--)
					if(::fa[x][j]&&d-dis[::fa[x][j]]<=p)x=::fa[x][j];
				Fa[i][0]=x;
			}
		}
		for(int p=2;p<=S;p++){
			int (*Fa)[18]=fa[p];
			for(int j=1;j<18;j++)
				for(int i=1;i<=n;i++){
					Fa[i][j]=Fa[Fa[i][j-1]][j-1];
				}
		}
	}
	int solve(int x,int y,int p){
		int l=lca(x,y),ans=0,(*Fa)[18]=fa[p];
		for(int i=17;i>=0;i--)
			if(Fa[x][i]&&dep[Fa[x][i]]>dep[l])ans+=1<<i,x=Fa[x][i];
		for(int i=17;i>=0;i--)
			if(Fa[y][i]&&dep[Fa[y][i]]>dep[l])ans+=1<<i,y=Fa[y][i];
		return ans+(dis[x]+dis[y]-(dis[l]<<1)+p-1)/p;
	}	
}p2;
int main(){
	scanf("%d",&n);
	for(int a,b,c,i=1;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);add(b,a,c);
	}
	dfs(1);
	p2.init();
	scanf("%d",&m);
	while(m--){
		int a,b,p;
		scanf("%d%d%d",&a,&b,&p);
		if(p>S)printf("%d\n",p1.solve(a,b,p));
		else printf("%d\n",p2.solve(a,b,p));
	}
	return 0;
}


