#include<bits/stdc++.h>
#define M 1000005
#define LL long long
const int mod=998244353;
const int base=97;
using namespace std;
int n,m,h[M],tt;
struct edge{
	int nxt,to,co;
}G[M];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
int in[M];
queue<int>Q;
int dis[M];
LL ans[M],fa[M][21],key[M][21],pw[M];
int main(){
//	freopen("number.in","r",stdin);
//	freopen("number.out","w",stdout);
	pw[0]=1;
	for(int i=1;i<M;i++)pw[i]=pw[i-1]*base%mod;
	scanf("%d%d",&n,&m);
	for(int i=1,a,b,c;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(b,a,c);in[a]++;
	}
	for(int i=1;i<=n;i++)
		if(in[i]==0)Q.push(i);
	memset(ans,-1,sizeof(ans));
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		if(fa[x][0])ans[x]=(ans[fa[x][0]]+key[x][0])%mod*29%mod;
		else ans[x]=0;
		for(int i=1;i<=20;i++){
			fa[x][i]=fa[fa[x][i-1]][i-1];
			key[x][i]=(key[x][i-1]+pw[1<<(i-1)]*key[fa[x][i-1]][i-1]%mod)%mod;
		}
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to,co=G[i].co;
			if(dis[u]<dis[x]+1){
				dis[u]=dis[x]+1;
				fa[u][0]=x;
				key[u][0]=co;
			}
			else if(dis[u]==dis[x]+1){
				if(key[u][0]>co){
					fa[u][0]=x;
					key[u][0]=co;
				}
				else if(key[u][0]==co){
					int a=fa[u][0],b=x;
					for(int j=20;j>=0;j--){
						if(!fa[a][j]||!fa[b][j])continue;
						if(key[a][j]==key[b][j])
							a=fa[a][j],b=fa[b][j];
					}
					if(key[a][0]>key[b][0])fa[u][0]=x;
				}
			}
			in[u]--;
			if(in[u]==0)Q.push(u);
		}
	}
	for(int i=1;i<=n;i++){
		if(ans[i]==-1)puts("Infinity");
		else printf("%lld\n",ans[i]);
	}
	return 0;
}
