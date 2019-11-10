#include<bits/stdc++.h>
using namespace std;
const int maxn=10005,maxe=200005,inf=0x3f3f3f3f;
int n,m,s,t,k;
int lnk[maxn],son[maxe],w[maxe],nxt[maxe],tot=1;
int que[maxn],hed,til,dep[maxn];
bool vis[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-f;ch=getchar();}
	while(ch>=48&&ch<=57) {ret=ret*10+ch-48;ch=getchar();}
	return ret*f;
}
void add_e(int x,int y,int z){w[++tot]=z;son[tot]=y;nxt[tot]=lnk[x];lnk[x]=tot;}
void add(int x,int y,int z){add_e(x,y,z);add_e(y,x,0);}
bool bfs(){
	memset(dep,0,sizeof dep);
	hed=0,til=1;
	vis[s]=1;que[1]=s;dep[s]=1;
	while(hed^til){
		int u=que[++hed];
		for(int j=lnk[u];j;j=nxt[j]){
			int v=son[j];
			if(w[j]&&!dep[v]) dep[v]=dep[u]+1,que[++til]=v;
		}
	}
	return dep[t]>0;
}
int dfs(int u,int minflw){
	if(u==t||!minflw) return minflw;
	int rest=0;
	for(int j=lnk[u];j;j=nxt[j]){
		int v=son[j];
		if(dep[v]==dep[u]+1&&w[j]){
			int nowflw=dfs(v,min(minflw-rest,w[j]));rest+=nowflw; 
			w[j]-=nowflw;w[j^1]+=nowflw;
		}
	}
	if(!rest) dep[u]=0;
	return rest;
}
int dinic(){
	int ans=0;
	while(bfs()){
		int x=0;
		while((x=dfs(s,inf))) ans+=x;
	}
	return ans;
}
int main(){
	k=read();n=read();t=n+k+1;s=0;
	for(int i=1;i<=k;i++){
		int x=read();
		m+=x;
		add(s,i,x);
	}
	for(int i=1;i<=n;i++){
		int x=read();
		for(int j=1;j<=x;j++){
			int p=read();
			add(p,i+k,1);
		}
		add(i+k,t,1);
	}
	if(dinic()==m){
		for(int i=1;i<=k;i++){
			printf("%d: ",i);
			for(int j=lnk[i];j;j=nxt[j]) if(son[j]&&!w[j]) printf("%d ",son[j]-k);
			printf("\n");
		}
	}
	else printf("No Solution!\n");
	return 0;
}