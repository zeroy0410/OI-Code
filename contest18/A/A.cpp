#include<stdio.h>
#include<queue>
#define M 605
using namespace std;
int n,m,h[M],tt=1,S,T;
int id[25][35],A[M];
const int inf=1e9;
struct edge{
	int nxt,to,co;
}G[M*M*10];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
vector<int>H[M];
int Q[M*M];
bool mark[M],vis[M];
int in[M];
int dep[M],cur[M],ans;
bool bfs(){
    for(int i=1;i<=n*m+2;i++){
        vis[i]=0;dep[i]=inf;
        cur[i]=h[i];
    }
	int l=0,r=0;
    dep[S]=0;Q[r++]=S;vis[S]=1;
    while(l<r){
        int x=Q[l++];
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co;
            if(vis[u]||!c)continue;
            dep[u]=dep[x]+1;
			vis[u]=1;
			Q[r++]=u;
			if(u==T)return 1;
        }
    }
    return 0;
}
int dfs(int x,int mi){
    int rlow=0;
    if(x==T||!mi)return mi;
    int used=0;
    for(int &i=cur[x];i;i=G[i].nxt){
        int u=G[i].to,c=G[i].co;
        if(dep[u]!=dep[x]+1||!c)continue;
        if(rlow=dfs(u,min(mi-used,c))){
            used+=rlow;
            G[i].co-=rlow;
            G[i^1].co+=rlow;
            if(used==mi)return used;
        }
    }
    return used;
}
void Dinic(){
    while(bfs())
        ans-=dfs(S,inf);
}
int main(){
	freopen("pvz.in","r",stdin);
	freopen("pvz.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			id[i][j]=(i-1)*m+j;
	for(int i=1;i<=n;i++)
		for(int j=1,c;j<=m;j++){
			scanf("%d",&A[id[i][j]]);
			scanf("%d",&c);
			for(int k=1,x,y;k<=c;k++){
				scanf("%d%d",&x,&y);x++;y++;
				H[id[i][j]].push_back(id[x][y]);
				in[id[x][y]]++;
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
			H[id[i][j+1]].push_back(id[i][j]),in[id[i][j]]++;
	int l=0,r=0;
	for(int i=1;i<=n*m;i++)
		if(!in[i])Q[r++]=i;
	while(l<r){
		int x=Q[l++];
		mark[x]=1;
		for(int i=0;i<H[x].size();i++){
			int u=H[x][i];
			in[u]--;
			if(!in[u])
				Q[r++]=u;
		}
	}
	S=n*m+1,T=n*m+2;
	for(int i=1;i<=n*m;i++){
		if(!mark[i])continue;
		if(A[i]>=0)Add(S,i,A[i]),Add(i,S,0),ans+=A[i];
		else if(A[i]<0)Add(i,T,-A[i]),Add(T,i,0);
		for(int j=0;j<H[i].size();j++){
			int u=H[i][j];
			if(!mark[u])continue;
			Add(u,i,inf);Add(i,u,0);
		}
	}
	Dinic();
	printf("%d\n",ans);
	return 0;
}