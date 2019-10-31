#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n,m,K,h[M],wk[M],tt;
struct edge{
	int nxt,to,co;
}G[M*20];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
struct Pshui{
	LL dis[M];
	bool vis[M],mark[M];
	struct node{
		int x;
		LL v;
		bool operator < (const node& res)const{
			return v>res.v;
		}
	};
	priority_queue<node>Q;
	void solve(){
		memset(dis,0x3f,sizeof(dis));LL inf=dis[0];
		for(int i=1;i<=K;i++){
			dis[wk[i]]=0;
			for(int j=h[wk[i]];j;j=G[j].nxt){
				int u=G[j].to,co=G[j].co;
				Q.push((node){u,co});
			}
		}
		while(!Q.empty()){
			node e=Q.top();Q.pop();
			if(!mark[e.x]){mark[e.x]=1;continue;}
			if(dis[e.x]!=inf)continue;
			dis[e.x]=e.v;
			for(int i=h[e.x];i;i=G[i].nxt){
				int u=G[i].to,co=G[i].co;
				if(dis[u]>dis[e.x]+co)
					Q.push((node){u,dis[e.x]+co});
			}
		}
		printf("%lld\n",dis[0]);
	}
}pshui;
int main(){
	freopen("tiger.in","r",stdin);
	freopen("tiger.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1,a,b,c;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
	}
	for(int i=1;i<=K;i++)scanf("%d",&wk[i]);
	pshui.solve();
	return 0;
}
