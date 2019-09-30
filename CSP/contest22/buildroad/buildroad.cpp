#include<cstdio>
#include<string.h>
#include<algorithm>
#define M 15
#define LL long long
using namespace std;
int n,m,S,h[M],tt;
struct edge{
	int nxt,to,co;
}G[M];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
struct node{
	int a,b,c;
}E[M*M];
struct P30{
	int cnt[1<<10],dis[6],in[6];
	bool vis[10];
	void dfs(int x,int f,int d){
		dis[x]=d;vis[x]=1;
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to,v=G[i].co;
			if(u==f||vis[u])continue;
			dfs(u,x,d+v);
		}
	}
	void solve(){
		LL ans=1e18,ct=0;
		for(int i=0;i<1<<m;i++){
			int c=0;
			for(int j=0;j<m;j++)
				if(i&1<<j)c++;
			if(c!=n-1)continue;
			memset(h,0,sizeof(h));tt=0;
			memset(in,0,sizeof(in));
			for(int j=0;j<m;j++)
				if(i&1<<j){
					Add(E[j].a,E[j].b,E[j].c),Add(E[j].b,E[j].a,E[j].c);
					in[E[j].a]++;in[E[j].b]++;
				}
			LL tmp=0;
			for(int j=1;j<=n;j++)
				if(in[j]==1)tmp+=S;
			for(int j=1;j<=n;j++){
				memset(vis,0,sizeof(vis));
				if(j==1){
					bool fl=1;
					dfs(j,0,0);
					for(int k=1;k<=n;k++)
						if(!vis[k]){fl=0;break;}
					if(!fl)break;
				}
				else dfs(j,0,0);
				LL res=tmp;
				for(int k=1;k<=n;k++)
					res+=dis[k];
				if(res<ans){
					ans=res;
					ct=1;
				}
				else if(res==ans)ct++;
			}
		}
		printf("%lld %d\n",ans,ct);
	}
}p30;
int main(){
	freopen("buildroad.in","r",stdin);
	freopen("buildroad.out","w",stdout);
	scanf("%d%d%d",&n,&m,&S);
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&E[i].a,&E[i].b,&E[i].c);
	}
	if(n<=5)p30.solve();
	return 0;
}
