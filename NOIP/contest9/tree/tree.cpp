#include<bits/stdc++.h>
#define M 3000005
#define LL long long
using namespace std;
const LL mod=1e9+7;
const LL inv2=500000004;
void read(int &x){
    char c;
    x=0;
    int f=1;
    while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
    do x=(x<<3)+(x<<1)+(c^48);
    while(c=getchar(),c>='0'&&c<='9');
    x*=f;
}
int n,L,R,h[M],tt;
struct edge{
	int nxt,to;
}G[M];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
LL dp[M];
int dep[M],sz[M];
LL val[M];
LL calc(int x,int y){
	return ((val[x]-1LL*y*(n-y-1)%mod-y)%mod+mod)%mod;
}
void dfs(int x,int d){
	sz[x]=1;dep[x]=d;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		dfs(u,d+1);
		sz[x]+=sz[u];
	}
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		val[x]=(val[x]+1LL*sz[u]*(n-sz[u]-1)%mod)%mod;
	}
	val[x]=(val[x]+1LL*(n-sz[x])*(sz[x]-1)%mod)%mod;
	val[x]=val[x]*inv2%mod;
	val[x]=(val[x]+n-1)%mod;
}
LL ret[M],ans,ret2[M];
void redfs(int x){
	if(dep[x]-L>=1){
		LL res=((ret[dep[x]-L]-ret[max(0,dep[x]-R-1)])%mod+mod)%mod;
		LL nowc=calc(x,n-sz[x]);
		ans=(ans+4*res*nowc%mod)%mod;
		ans=(ans+2*nowc*(dep[x]-L-max(0,dep[x]-R-1))%mod)%mod;
		ans=(ans+2*res%mod)%mod;
	}
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		ret[dep[x]]=(ret[dep[x]-1]+calc(x,sz[u]))%mod;
		redfs(u);
	}
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d%d%d",&n,&L,&R);
	for(int i=2,x;i<=n;i++){
		read(x);
		Add(x,i);
	}
	dfs(1,1);
	redfs(1);
	printf("%lld\n",ans*inv2%mod);
	return 0;
}
