#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#define FOR(i,l,r) for(int i=(l),i##R=(r);i<=i##R;i++)
#define DOR(i,r,l) for(int i=(r),i##L=(l);i>=i##L;i--)
#define loop(i,n) for(int i=0,i##R=(n);i<i##R;i++)
#define mms(a,x) memset(a,x,sizeof a)
#define lowbit(x) (x&(-x))
using namespace std;
typedef double db;
typedef long long ll;
template<typename A,typename B>inline void chkmax(A &x,const B y){if(x<y)x=y;}
template<typename A,typename B>inline void chkmin(A &x,const B y){if(x>y)x=y;}
const int N=155,inf=2e9;
struct Graph{
	static const int M=305,Mx=M*M*2;
	int tot,to[Mx],nxt[Mx],len[Mx],cost[Mx],head[M],cur[M];
	void add(int x,int y,int z,int c){
		tot++;to[tot]=y;
		len[tot]=z;cost[tot]=c;
		nxt[tot]=head[x];head[x]=tot;
	}
	void adds(int x,int y,int z,int c){
//		printf("x:%d y:%d z:%d c:%d\n",x,y,z,c);
        cout<<x<<' '<<y<<' '<<z<<endl;
		add(x,y,z,c);
		add(y,x,0,-c);
	}
	void clear(){mms(head,-1);tot=1;}
	#define EOR(G,i,x) for(int i=G.head[x];i!=-1;i=G.nxt[i])
	#define COR(G,i,x) for(int &i=G.cur[x];i!=-1;i=G.nxt[i])
}G;
int n,m,K,s,t;
int dis[N][N];
namespace Very_Weird{
	void init(){
		FOR(k,0,n){
			FOR(i,0,n)FOR(j,i,n)
				if(k<=j)chkmin(dis[i][j],dis[i][k]+dis[k][j]);
			FOR(i,0,n)FOR(j,i,n)dis[j][i]=dis[i][j];
		}
	}
	void build(){
		s=0,t=2*(n+1)+1;
		G.adds(s,1,K,0);
		FOR(i,2,n+1){
			G.adds(s,i,1,0);
			G.adds(i+n+1,t,1,0);
		}
		FOR(i,1,n+1)FOR(j,i+1,n+1)if(dis[i-1][j-1]<1e9)
			G.adds(i,j+n+1,1,dis[i][j]);
	}
	int mn[N<<1];
	bool vis[N<<1];
	bool spfa(){
		FOR(i,0,t)vis[i]=0,mn[i]=inf;
		queue<int>Q;
		Q.push(s);mn[s]=0;
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			vis[x]=0;
			EOR(G,i,x){
				int v=G.to[i];
				if(G.len[i]&&mn[v]>mn[x]+G.cost[i]){
					mn[v]=mn[x]+G.cost[i];
					if(!vis[v])vis[v]=1,Q.push(v);
				}
			}
		}
		return mn[t]!=inf;
	}
	int dfs(int x,int flow){
		vis[x]=1;
		if(x==t)return flow;
		int ret=0;
		COR(G,i,x){
			int v=G.to[i];
			if(!vis[v]&&G.len[i]&&mn[v]==mn[x]+G.cost[i]){
				int res=dfs(v,min(flow,G.len[i]));
				flow-=res,G.len[i]-=res;
				G.len[i^1]+=res,ret+=res;
				if(!flow)break;
			}
		}
		if(!ret)mn[x]=inf;
		return ret;
	}
	int Dinic(){
		int ans=0;
		while(spfa()){
			FOR(i,0,t)G.cur[i]=G.head[i];
			ans+=mn[t]*dfs(s,inf);
		}
		return ans;
	}
	void solve(){
		init();
		build();
		printf("%d\n",Dinic());
	}
}
int main(){
	// freopen("save.in","r",stdin);
	// freopen("save.out","w",stdout);
	G.clear();
	scanf("%d%d%d",&n,&m,&K);
	mms(dis,63);
	FOR(i,0,n)dis[i][i]=0;
	FOR(i,1,m){
		int x,y,l;
		scanf("%d%d%d",&x,&y,&l);
		if(x>y)swap(x,y);
		chkmin(dis[x][y],l);
		chkmin(dis[y][x],l);
	}
	Very_Weird::solve();
	return 0;
}