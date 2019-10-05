#include<bits/stdc++.h>
#define M 300005
#define LL long long
using namespace std;
const int mod=998244353;
int n,m,p,h[M],tt=1;
struct edge{
	int nxt,to,co;
}G[M<<2];
struct Edge{
	int a,b,c;
	bool operator < (const Edge& res)const{
		return c>res.c;
	}
}E[M<<2];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
struct P20{
	int fa[M];
	LL sum1[M],sum2[M],ans;
	int getfa(int x){
		return fa[x]==x?x:fa[x]=getfa(fa[x]);
	}
	void solve(){
		for(int i=1;i<=n;i++)sum2[i]=qkpow(p,1LL*(i-1)*n),sum1[i]=qkpow(p,i),fa[i]=i;
		sort(E+1,E+m+1);
		ans=0;
		for(int i=1;i<=m;i++){
			int a=E[i].a,b=E[i].b,c=E[i].c;
			int rt1=getfa(a),rt2=getfa(b);
			ans=(ans+1LL*c*((sum1[rt1]*sum2[rt2]%mod+sum1[rt2]*sum2[rt1]%mod)%mod)%mod)%mod;
			sum1[rt1]+=sum1[rt2];sum1[rt1]%=mod;
			sum2[rt1]+=sum2[rt2];sum2[rt1]%=mod;
			fa[rt2]=rt1;
		}
		printf("%lld\n",ans);
	}
}p20;
//struct P40{
//	LL s2;
//	bool vis[M];
//	int dep[M];
//	void dfs(int x,int f,int d){
//		dep[x]=d;vis[x]=1;
//		for(int i=h[x];i;i=G[i].nxt){
//			int u=G[i].to;
//			if((i^1)==f||dep[u]>dep[x])continue;
//			if(vis[u]){
//				s2=(s2+1LL*(dep[x]-dep[u]+1)*(dep[x]-dep[u])%mod)%mod;
//			}
//			else dfs(u,i,d+1);
//		}
//	}
//	void solve(){
//		s2=0;
//		dfs(1,0,0);
//		LL ans=(1LL*n*(n-1)%mod+s2)%mod;
//		printf("%lld\n",ans);
//	}
//}p40;
struct P60{
	edge bg[105<<2];
	int bh[105];
	int dep[105],inf,s,t,ans;
	bool vis[105];
	LL Ans;
	queue<int>Q;
	bool bfs(){
		memset(dep,0x3f,sizeof(dep));inf=dep[0];
		memset(vis,0,sizeof(vis));
		dep[s]=0;Q.push(s);
		while(!Q.empty()){
			int e=Q.front();Q.pop();
			vis[e]=0;
			for(int i=h[e];i;i=G[i].nxt){
				int u=G[i].to,c=G[i].co;
				if(dep[u]<=dep[e]+1||!c)continue;
				dep[u]=dep[e]+1;
				if(!vis[u]){
					vis[u]=1;
					Q.push(u);
				}
			}
		}
		if(dep[t]!=inf)return 1;
		return 0;
	}
	int dfs(int x,int mi){
		int rlow=0;
		if(x==t)return mi;
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to,c=G[i].co;
			if(dep[u]!=dep[x]+1||!c)continue;
			if(rlow=dfs(u,min(mi,c))){
				G[i].co-=rlow;
				G[i^1].co+=rlow;
				return  rlow;
			}
		}
		return 0;
	}
	void Dinic(){
		int tmp;
		while(bfs()){
			while(tmp=dfs(s,inf))ans+=tmp;
		}
	}
	void solve(){
		Ans=0;
		for(int i=1;i<=n;i++)bh[i]=h[i];
		for(int i=2;i<=tt;i++)bg[i]=G[i];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i==j)continue;
				for(int k=1;k<=n;k++)h[k]=bh[k];
				for(int k=2;k<=tt;k++)G[k]=bg[k];
				s=i;t=j;ans=0;
				Dinic();
				Ans=(Ans+1LL*ans*qkpow(p,(s-1)*n+t)%mod)%mod;
			}
		}
		printf("%lld\n",Ans);
	}
}p60;
int main(){
	freopen("sakura.in","r",stdin);
	freopen("sakura.out","w",stdout);
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1,a,b,c;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
		E[i]=(Edge){a,b,c};
	}
	if(m==n-1)p20.solve();
	else p60.solve();
	return 0;
}
