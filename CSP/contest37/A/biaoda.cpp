#include<bits/stdc++.h>
using namespace std;
const int M=4e5+5;
int n;
int h[M],nx[M<<1],to[M<<1],v[M<<1],tot=1;
void add(int a,int b,int c){
	to[++tot]=b;v[tot]=c;
	nx[tot]=h[a];h[a]=tot;
}
struct P30{
	int mx[M];
	int gcd(int a,int b){
		return !b?a:gcd(b,a%b);
	}
	void dfs(int x,int f,int d,int w){
		mx[d]=max(mx[d],w);
		for(int i=h[x];i;i=nx[i]){
			int y=to[i];
			if(y==f)continue;
			dfs(y,x,d+1,gcd(w,v[i]));
		}
	}
	void solve(){
		for(int i=1;i<=n;i++)
			dfs(i,0,0,0);
		for(int i=1;i<=n;i++)printf("%d\n",mx[i]);
	}
}p30;
int mxe;
struct Px{
	struct node{int u,v,w;}a[M<<1];
	int H[M],NX[M<<1],TO[M<<1],TOT;
	bool mark[M];
	int mx[M];
	void ADD(int a,int b){
		TO[++TOT]=b;
		NX[TOT]=H[a];
		H[a]=TOT;
	}
	int mxdis;
	int ans[M];
	void dfs(int x){
		mark[x]=1,mx[x]=0;
		int fi=0,se=0;
		for(int i=H[x];i;i=NX[i]){
			int y=TO[i];
			if(mark[y])continue;
			dfs(y);
			if(fi<mx[y]+1)se=fi,fi=mx[y]+1;
			else if(se<mx[y]+1)se=mx[y]+1;
		}
		mxdis=max(mxdis,fi+se);
		mx[x]=fi;
	}
	int vec[M],tp;
	bool vis[M];
	vector<int>P[M*3],son[M*3];
	void solve(){
		for(int i=2;i<=tot;i++)
			a[i]=(node){to[i],to[i^1],v[i]};
		for(int i=2;i<=tot;i++)P[a[i].w].push_back(i);
		for(int i=1;i<=mxe;i++)
			for(int j=i;j<=mxe;j+=i)
				for(int k=0;k<(int)P[j].size();k++)
					son[i].push_back(P[j][k]);
		for(int i=1;i<=mxe;i++){
			tp=0;
			for(int j=0;j<(int)son[i].size();j++){
				int y=son[i][j];
				if(a[y].w%i==0){
					ADD(a[y].u,a[y].v);
					if(!vis[a[y].u])vec[++tp]=a[y].u,vis[a[y].u]=1; 
					if(!vis[a[y].v])vec[++tp]=a[y].v,vis[a[y].v]=1;
				}	
			}
			mxdis=0;
			for(int j=1;j<=tp;j++){
				int y=vec[j];
				if(!mark[y])dfs(y);
			}
			ans[mxdis]=i;
			TOT=0;
			for(int j=1;j<=tp;j++){
				int y=vec[j];
				H[y]=mark[y]=vis[y]=0;
			}
		}
		for(int i=n-1;i>=1;i--)ans[i]=max(ans[i],ans[i+1]);
		for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
	}
}px;
int main(){
	scanf("%d",&n);
	for(int a,b,c,i=1;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);add(b,a,c);
		mxe=max(mxe,c);
	}
	if(n<=1000)p30.solve();
	else px.solve();
	return 0;
}

