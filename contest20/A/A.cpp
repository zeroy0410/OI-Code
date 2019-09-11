#include<bits/stdc++.h>
#define M 50005
using namespace std;
int n,H[M],h[M],tt,tot;
int now[M],ans[M];
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
void dfs(int x,int f){
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
		int mi=min(H[x],H[u]);tot+=mi<<1;
		H[x]-=mi;H[u]-=mi;
		if(H[u])now[x]=u;
	}
}
void redfs(int x,int f){
	ans[x]=tot;int flag;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		if(H[x])flag=1,tot++;
		else if(now[u])flag=2,tot++,H[now[u]]--;
		else flag=3,tot--,H[u]++;
		redfs(u,x);
		if(flag==1)tot--;
		else if(flag==2)tot--,H[now[u]]++;
		else tot++,H[u]--;
	}
}
int main(){
	// freopen("galaxy.in","r",stdin);
	// freopen("galaxy.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&H[i]);	
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);a++;b++;
		Add(a,b);Add(b,a);H[a]--;H[b]--;
		tot+=2;
	}
	dfs(1,0);redfs(1,0);
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}