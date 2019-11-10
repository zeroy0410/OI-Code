#include<stdio.h>
#include<queue>
#include<algorithm>
#include<string.h>
#define M 500005
using namespace std;
const int mod=998244353;
int n,m,h[M],tt,fa[M],deg[M],ans;
struct edge{int nxt,to,co;}G[M<<1];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
void dfs(int x,int f,int v){
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to,v=G[i].co;
		if(u==f)continue;
		dfs(u,x,v);
	}
	if(deg[x])deg[x]^=1,deg[f]^=1,ans=(ans+v)%mod;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1,v=2,a,b;i<=m;i++,v=v*2%mod){
		scanf("%d%d",&a,&b);
		if(getfa(a)!=getfa(b)){
			Add(a,b,v);
			Add(b,a,v);
			fa[getfa(a)]=getfa(b);
		}
		deg[a]^=1;deg[b]^=1;
		ans=(ans+v)%mod;
	}
	dfs(1,0,0);
	printf("%d\n",(ans%mod+mod)%mod);
	return 0;
}
