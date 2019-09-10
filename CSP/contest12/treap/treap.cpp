#include<bits/stdc++.h>
using namespace std;
#define M 1000005
#define LL long long
const int mod=998244353;
int n,P,h[M],tt;
struct edge{
	int nxt,to;
}G[M<<1];
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
	}return res;
}
struct P10{
	int A[15],mi[15],res,ans,tot;
	void dfs(int x,int f){
		mi[x]=A[x];
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to;
			if(u==f)continue;
			dfs(u,x);
			if(mi[u]<mi[x])mi[x]=mi[u];
		}
		if(mi[x]==A[x])res++;
	}
	void solve(){
		for(int i=1;i<=n;i++)A[i]=i;
		do{
			for(int i=1;i<=n;i++){
				res=0;
				dfs(i,0);
				ans+=qkpow(P,res);
			}
			tot+=n;
		}while(std::next_permutation(A+1,A+n+1));
		printf("%lld\n",ans*qkpow(tot,mod-2)%mod);
	}
}p10;
int main(){
	freopen("treap.in","r",stdin);
	freopen("treap.out","w",stdout);
	scanf("%d%d",&n,&P);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	if(P==1){puts("1");return 0;}
	p10.solve();
	return 0;
}
