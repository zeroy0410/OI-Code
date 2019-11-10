#include<bits/stdc++.h>
#define FOR(i,l,r) for(register int i=(l),i##R=(r);i<=i##R;i++)
#define DOR(i,r,l) for(register int i=(r),i##L=(l);i>=i##L;i--)
#define loop(i,n) for(register int i=0,i##R=(n);i<i##R;i++)
#define mms(a,x) memset(a,x,sizeof a)
using namespace std;
const int N=1e6+5,P=998244353,Base=97,Mod=1e9+7;
int n,m;
inline void rd(int &x){
	static char c;x=0;
	while((c=getchar())<48);
	do x=(x<<1)+(x<<3)+(c^48);
	while((c=getchar())>47);
}
struct Graph{
	int tot,to[N],nxt[N],len[N],head[N];
	void add(int x,int y,int z){tot++;to[tot]=y;len[tot]=z;nxt[tot]=head[x];head[x]=tot;}
	void clear(){mms(head,-1);tot=0;}
#define EOR(G,i,x) for(int i=G.head[x];i!=-1;i=G.nxt[i])
}G;
void add(int &x,int y){x+=y;if(x>=P)x-=P;}
void Mul(int &x,int y){x=(int)(1ll*x*y)%P;}
int ind[N];
int ans[N],dis[N];
int fa[N][21],key[N][21],pw[N];
int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)Mul(ans,a);
		Mul(a,a),b>>=1;
	}
	return ans;
}
void topo(){
	queue<int>Q;
	FOR(i,1,n)
		if(!ind[i])Q.push(i),ans[i]=dis[i]=0;
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		if(fa[x][0])ans[x]=1ll*(ans[fa[x][0]]+key[x][0])%P*29%P;
		FOR(i,1,20){
			fa[x][i]=fa[fa[x][i-1]][i-1];
			key[x][i]=(int)((key[x][i-1]+1ll*pw[1<<(i-1)]*key[fa[x][i-1]][i-1]%Mod)%Mod);
		}
		EOR(G,i,x){
			int v=G.to[i];
			if(dis[v]<dis[x]+1){
				dis[v]=dis[x]+1;
				fa[v][0]=x;
				key[v][0]=G.len[i];
			}
			else if(dis[v]==dis[x]+1){
				if(key[v][0]>G.len[i]){
					fa[v][0]=x;
					key[v][0]=G.len[i];
				}
				else if(key[v][0]==G.len[i]){
					int w=fa[v][0],t=x;
					DOR(i,20,0){
						if(!fa[w][i]||!fa[t][i])continue;
						if(key[w][i]==key[t][i])
							w=fa[w][i],t=fa[t][i];
					}
					if(key[w][0]>key[t][0])fa[v][0]=x;
				}
			}
			ind[v]--;
			if(!ind[v])Q.push(v);
		}
	}
	FOR(i,1,n)if(ind[i])ans[i]=-1;
}
int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	pw[0]=1;FOR(i,1,1<<19)pw[i]=(int)(1ll*pw[i-1]*Base)%Mod;
	G.clear();
	rd(n),rd(m);
	FOR(i,1,m){
		int x,y,w;
		rd(x),rd(y),rd(w);
		ind[x]++;
		G.add(y,x,w);
	}
	topo();
	FOR(i,1,n){
		if(ans[i]==-1)puts("Infinity");
		else printf("%d\n",ans[i]);
	}
	return 0;
}
