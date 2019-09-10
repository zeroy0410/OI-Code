#include<stdio.h>
#define M 1000005
#define LL long long
const int mod=998244353;
int n,P,h[M],tt;
LL rev[M];
struct edge{int nxt,to;}G[M<<1];
void Init(){
	rev[0]=rev[1]=1;
	for(int i=2;i<=n;i++) 
		rev[i]=(mod-mod/i)*rev[mod%i]%mod;
}
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
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
int sz[M];
LL resx=1,resy=1,cnt=0,ansx=0,ansy=1;
LL calc(int x){
	return (x-1+P)*rev[x]%mod;
}
void dfs(int x,int f){
	sz[x]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
		sz[x]+=sz[u];
	}
	int p=calc(sz[x]);
	if(p)resx=resx*p%mod;
	else cnt++;
}
void redfs(int x,int f){
	if(!cnt){
		ansx=(ansx*resy+ansy*resx)%mod;
		ansy=ansy*resy%mod;
	}
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		int q=calc(sz[u]),p=calc(n-sz[u]);
		if(q)resy=resy*q%mod;else cnt--;
		if(p)resx=resx*p%mod;else cnt++;
		redfs(u,x);
		if(q)resx=resx*q%mod;else cnt++;
		if(p)resy=resy*p%mod;else cnt--;
	}
}
int main(){
	scanf("%d%d",&n,&P);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	Init();
	dfs(1,0);
	redfs(1,0);
	printf("%lld\n",ansx*qkpow(ansy,mod-2)%mod*rev[n]%mod);
	return 0;
}
