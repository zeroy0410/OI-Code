#include<bits/stdc++.h>
#define M 100005
using namespace std;
const int mod=1e9+7;
int n,m,h[M],tt,A[M];
struct node{
	int a,b;
	bool operator < (const node& res)const{
		if(a!=res.a)return a<res.a;
		return b<res.b;
	}
};
set<node>S;
bool check(int a,int b){
	if(a>b)swap(a,b);
	if(S.find((node){a,b})!=S.end())return 1;
	return 0;
}
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
void calc(int &x,int y){
	x+=y;
	if(x>=mod)x-=mod;
}
struct Pshui{
	int dep[M];
	int ans,fa[M];
	void dfs(int x,int f,int d){
		dep[x]=d;fa[x]=f;
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to;
			if(u==f)continue;
			if(!dep[u])dfs(u,x,d+1);
			else {
				if(dep[x]-dep[u]==3){
					int t=x;
					while(t!=fa[u]){
						calc(ans,A[t]);
						t=fa[t];
					}
				}
				else if(dep[x]-dep[u]>3){
					int t=fa[x],t2=fa[t];
					if(check(t2,u)){
						calc(ans,A[x]);
						calc(ans,A[t]);
						calc(ans,A[u]);
						calc(ans,A[t2]);
					}
				}
				else {
					int t=fa[x],t2=fa[u];
					if(check(t,t2)){
						calc(ans,A[x]);
						calc(ans,A[t]);
						calc(ans,A[u]);
						calc(ans,A[t2]);
					}
				}
			}
		}
	}
	void solve(){
		ans=0;
		dfs(1,0,1);
		printf("%d\n",ans);
	}
}pshui;
bool mark[1005][1005];
struct Pbl{
	int ans;
	void solve(){
		ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(!mark[i][j])continue;
				for(int k=1;k<=n;k++){
					if(k==i)continue;
					if(!mark[j][k])continue;
					for(int r=1;r<=n;r++){
						if(r==j||r==i)continue;
						if(!mark[k][r])continue;
						if(!mark[r][i])continue;
						calc(ans,(1LL*A[i]+A[j]+A[k]+A[r])%mod);
					}
				}
			}
		}
		printf("%lld\n",1LL*ans*125000001%mod);
	}
}pbl;
struct Phaha{
	int ans;
	void solve(){
		ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(!check(i,j))continue;
				for(int k=1;k<=n;k++){
					if(k==i)continue;
					if(!check(j,k))continue;
					for(int r=1;r<=n;r++){
						if(r==j||r==i)continue;
						if(!check(k,r))continue;
						if(!check(r,i))continue;
						calc(ans,(1LL*A[i]+A[j]+A[k]+A[r])%mod);
					}
				}
			}
		}
		printf("%lld\n",1LL*ans*125000001%mod);
	}
}phaha;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		if(n<=1000)mark[a][b]=mark[b][a]=1;
		if(a>b)swap(a,b);
		S.insert((node){a,b});
		Add(a,b);Add(b,a);
	}
	if(n<=1000)pbl.solve();
	else phaha.solve();
	return 0;
}
