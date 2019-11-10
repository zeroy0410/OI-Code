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
int fa[M],Fa[M],id[M],dep[M];
bool used[M<<2],mark[M<<2];
LL sum1[M],sum2[M],ans;
void dfs(int x,int f,int d){
	Fa[x]=f;dep[x]=d;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to,Id=G[i].co;
		if(u==f)continue;
		id[u]=Id;
		dfs(u,x,d+1);
	}
}
int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
void solve(){
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)sum2[i]=qkpow(p,1LL*(i-1)*n),sum1[i]=qkpow(p,i),fa[i]=i;
	sort(E+1,E+m+1);
	ans=0;
	for(int i=1;i<=m;i++){
		int a=E[i].a,b=E[i].b,c=E[i].c;
		if(c==-12138)break;
		int rt1=getfa(a),rt2=getfa(b);
		ans=(ans+1LL*c*((sum1[rt1]*sum2[rt2]%mod+sum1[rt2]*sum2[rt1]%mod)%mod)%mod)%mod;
		sum1[rt1]+=sum1[rt2];sum1[rt1]%=mod;
		sum2[rt1]+=sum2[rt2];sum2[rt1]%=mod;
		fa[rt2]=rt1;
	}
	printf("%lld\n",ans);
}
int main(){
	freopen("sakura.in","r",stdin);
	freopen("sakura.out","w",stdout);
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1,a,b,c;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		E[i]=(Edge){a,b,c};
		int r1=getfa(a),r2=getfa(b);
		if(r1!=r2){
			fa[r1]=r2;
			used[i]=1;
			Add(a,b,i);Add(b,a,i);
		}
	}
	dfs(1,0,0);
	for(int i=1;i<=m;i++){
		if(!used[i]){
			int a=E[i].a,b=E[i].b;
			int p=i,mi=E[i].c;
			if(dep[a]<dep[b])swap(a,b);
			while(dep[a]>dep[b]){
				if(E[id[a]].c<mi)mi=E[id[a]].c,p=id[a];
				a=Fa[a];
			}
			while(a!=b){
				if(E[id[a]].c<mi)mi=E[id[a]].c,p=id[a];
				if(E[id[b]].c<mi)mi=E[id[b]].c,p=id[b];
				a=Fa[a];b=Fa[b];
			}
			E[p].c=-12138;
			if(p!=i)E[i].c+=mi;
			a=E[i].a,b=E[i].b;
			if(dep[a]<dep[b])swap(a,b);
			while(dep[a]>dep[b]){
				if(id[a]!=p)E[id[a]].c+=mi;
				a=Fa[a];
			}
			while(a!=b){
				if(id[a]!=p)E[id[a]].c+=mi;
				if(id[b]!=p)E[id[b]].c+=mi;
				a=Fa[a];b=Fa[b];
			}
		}
	}
	solve();
	return 0;
}
