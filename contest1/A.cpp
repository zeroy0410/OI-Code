#include<bits/stdc++.h>
#define M 500005
#define LL long long
using namespace std;
const LL INF=1e18;
struct node{
	int x;LL ds;
	bool operator < (const node& res) const{
		return ds>res.ds; 
	}	
};
int A[15];
priority_queue<node>Q;
LL dis[M];bool vis[M];
int n,h[M],tot;
struct edge{int nxt,to,co;}G[M<<1];
void Add(int a,int b,int c){
	G[++tot]=(edge){h[a],b,c};
	h[a]=tot;	
}
LL dij(int s,int t){
	memset(vis,0,sizeof(vis));
	fill(dis+1,dis+A[5]+1,INF);dis[s]=0;
	Q.push((node){s,0});
	while(!Q.empty()){
		node e=Q.top();Q.pop();
		if(vis[e.x])continue;
		vis[e.x]=1;
		for(int i=h[e.x];i;i=G[i].nxt){
			int u=G[i].to,v=G[i].co;
			if(dis[u]>dis[e.x]+v){
				dis[u]=dis[e.x]+v;
				Q.push((node){u,dis[u]});
			}
		}
	}
	return dis[t];
}
int main(){
	A[0]=1;
	for(int i=1;i<=5;i++)scanf("%d",&A[i]),A[i]+=A[i-1];
	scanf("%d",&n);
	for(int i=1,l,r;i<=n;i++){
		scanf("%d%d",&l,&r);
		Add(l,r+1,r-l+1);
		Add(r+1,l,r-l+1);
	}
	LL ans=INF;
	ans=min(ans,dij(A[1],A[2])+dij(A[3],A[4]));
	ans=min(ans,dij(A[1],A[3])+dij(A[2],A[4]));
	ans=min(ans,dij(A[1],A[4])+dij(A[2],A[3]));
	printf("%lld\n",ans==INF?-1:ans);
	return 0;
}
