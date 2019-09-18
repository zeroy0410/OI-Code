#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=5e5+5; 
int n,K;
int h[M],nx[M<<1],to[M<<1],v[M<<1],tot;
void add(int a,int b,int c){
	to[++tot]=b;v[tot]=c;
	nx[tot]=h[a];h[a]=tot;
}
ll dp[M];
int sz[M];
struct node{
	ll fi,se;
	void operator +=(const ll &_){
		if(fi>_)se=fi,fi=_;
		else if(se>_)se=_;
	}
}mn[M];
void dfs(int x,int f){
	for(int i=h[x];i;i=nx[i]){
		int y=to[i];
		if(y==f)continue;
		dfs(y,x);
		sz[x]+=sz[y];
		if(!sz[y])continue;
		dp[x]+=dp[y]+(v[i]<<1);
		mn[x]+=mn[y].fi-v[i];
	}
}
void redfs(int x,int f){
	for(int i=h[x];i;i=nx[i]){
		int y=to[i];
		if(y==f)continue;
		if(mn[x].fi==mn[y].fi-v[i])mn[y]+=mn[x].se-v[i];
		else mn[y]+=mn[x].fi-v[i];
		if(!sz[y])dp[y]=dp[x]+(v[i]<<1);
		else if(sz[y]==K)dp[y]=dp[x]-(v[i]<<1);
		else dp[y]=dp[x];
		redfs(y,x);
	}
}
int main(){
	scanf("%d%d",&n,&K);
	for(int a,b,c,i=1;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);add(b,a,c);
	}
	for(int x,i=1;i<=K;i++)
		scanf("%d",&x),sz[x]++;
	dfs(1,0);
	redfs(1,0);
	for(int i=1;i<=n;i++)printf("%lld\n",dp[i]+mn[i].fi);
	return 0;
}
