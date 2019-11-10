#include<bits/stdc++.h>
#define m 20035
#define ll long long
using namespace std;
int n,k,h[m],tt;
struct edge{
	int nxt,to;
}g[m<<1];
void add(int a,int b){
	g[++tt]=(edge){h[a],b};
	h[a]=tt;
}
//struct pshui{
//	int sz[m],mxx,rt;
//	void dfs(int x,int f){
//		sz[x]=1;int mx=0;
//		for(int i=h[x];i;i=g[i].nxt){
//			int u=g[i].to;
//			if(u==f)continue;
//			dfs(u,x);
//			sz[x]+=sz[u];
//			if(sz[u]>mx)mx=sz[u];
//		}
//		mx=max(mx,n-sz[x]);
//		if(mx<mxx)rt=x,mxx=mx;
//		else if(mx==mxx&&x<rt)rt=x;
//	}
//	void solve(){
//		mxx=1e9;
//		dfs(1,0);
//		printf("%d\n",rt);
//	}
//}pshui;
struct pk1{
	int sz[m],rt;
	ll dp[m];
	void dfs(int x,int f){
		dp[x]=0;sz[x]=1;
		for(int i=h[x];i;i=g[i].nxt){
			int u=g[i].to;
			if(u==f)continue;
			dfs(u,x);
			sz[x]+=sz[u];
			dp[x]+=dp[u]+sz[u];
		}
	}
	void solve(){
		rt=0;dp[0]=1e18;
		for(int i=1;i<=n;i++){
			dfs(i,0);
			if(dp[i]<dp[rt])rt=i;
		}
		printf("%d\n",rt);
	}
}pk1;
struct p70{
	int ans[m],dis[m],rt;
	void dfs(int x,int f,int d){
		dis[d]++;
		for(int i=h[x];i;i=g[i].nxt){
			int u=g[i].to;
			if(u==f)continue;
			dfs(u,x,d+1);
		}
	}
	bool cmp(){
		for(int i=n+20;i>=1;i--){
			if(dis[i]<ans[i])return 1;
			if(dis[i]>ans[i])return 0;
		}
		return 0;
	}
	void solve(){
		rt=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n+20;j++)dis[j]=0;
			dfs(i,0,0);
			for(int j=1;j<=n+20;j++){
				if(dis[j]>=k){
					dis[j+1]+=dis[j]/k;
					dis[j]%=k;
				}
			}
			if(rt==0){
				rt=i;
				for(int j=1;j<=n+20;j++)ans[j]=dis[j];
			}
			else if(cmp()){
				rt=i;
				for(int j=1;j<=n+20;j++)ans[j]=dis[j];
			}
		}
		printf("%d\n",rt);
	}
}p70;
int sz[m],mx[m];
int mark[m];
bool cmp1(int& a,int& b){
	return mx[a]<mx[b];
}
struct p100{
	int ans[m],dis[m],rt;
	void dfsinit(int x,int f){
		sz[x]=1;
		for(int i=h[x];i;i=g[i].nxt){
			int u=g[i].to;
			if(u==f)continue;
			dfsinit(u,x);
			sz[x]+=sz[u];
			if(sz[u]>mx[x])mx[x]=sz[u];
		}
		mx[x]=max(mx[x],n-sz[x]);
	}
	void dfs(int x,int f,int d){
		dis[d]++;
		for(int i=h[x];i;i=g[i].nxt){
			int u=g[i].to;
			if(u==f)continue;
			dfs(u,x,d+1);
		}
	}
	bool cmp(){
		for(int i=n+20;i>=1;i--){
			if(dis[i]<ans[i])return 1;
			if(dis[i]>ans[i])return 0;
		}
		return 0;
	}
	void solve(){
		rt=0;
		for(int i=1;i<=n;i++)mark[i]=i;
		sort(mark+1,mark+n+1,cmp1);
		for(int r=1;r<=10000000/n;r++){
			int i=mark[r];
			for(int j=1;j<=n+20;j++)dis[j]=0;
			dfs(i,0,0);
			for(int j=1;j<=n+20;j++){
				if(dis[j]>=k){
					dis[j+1]+=dis[j]/k;
					dis[j]%=k;
				}
			}
			if(rt==0){
				rt=i;
				for(int j=1;j<=n+20;j++)ans[j]=dis[j];
			}
			else if(cmp()){
				rt=i;
				for(int j=1;j<=n+20;j++)ans[j]=dis[j];
			}
		}
		printf("%d\n",rt);
	}
}p100;
int main(){
	freopen("bigshark.in","r",stdin);
	freopen("bigshark.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		add(a,b);add(b,a);
	}
	if(k==1)pk1.solve();
	else if(n<=500)p70.solve();
	else p100.solve();
	return 0;
}
