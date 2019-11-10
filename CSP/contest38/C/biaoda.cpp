#include<bits/stdc++.h>
#define FOR(x,y,z) for(int x=y,x##_=z;x<=x##_;x++)
#define DOR(x,y,z) for(int x=y,x##_=z;x>=x##_;x--)
#define FOG(x,y,z) for(register int x=y,x##_=z;x<=x##_;x++)
#define DOG(x,y,z) for(register int x=y,x##_=z;x>=x##_;x--)
#define FOO(x,y) for(int x=0,x##_=(int)y;x<x##_;x++)
#define EOR(x,y) for(int x##_=head[x],y=edge[x##_].e;x##_;y=edge[x##_=edge[x##_].to].e)
#define EGOR(x,y,z) for(int x##_=head[x],y=edge[x##_].e,z=edge[x##_].c;x##_;y=edge[x##_=edge[x##_].to].e,z=edge[x##_].c)
#define szf(x) sizeof(x)
#define clr(x,y) memset(x,y,szf(x))
#define sot(A,x) sort(A+1,A+x+1)
#define uni(A,x) {sort(A+1,A+x+1);x=unique(A+1,A+x+1)-A-1;}
#define readf(x) scanf("%lf",&x)
#define reads(x) scanf("%s",x)
#define read2(x,y) read(x),read(y)
#define read3(x,y,z) read2(x,y),read(z)
#define read4(x,y,z,w) read3(x,y,z),read(w)
#define pf printf
#define sf scanf
#define ll long long
#define db double
#define ct clock_t
#define ck clock
using namespace std;
bool mem1;
template<class T>void read(T &x){
	x=0;
	int f=1;
	char c;
	while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
	do x=(x<<3)+(x<<1)+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	x*=f;
}
template<class T>bool tomin(T &x,T y){return y<x?x=y,1:0;}
template<class T>bool tomax(T &x,T y){return x<y?x=y,1:0;}
const int maxn=5e5+5;
const int maxm=1e6+5;
int n,m;
int deg[maxn];
struct Edge{
	int e,to;
}edge[maxm<<1];
int head[maxn],tot;
vector<int>Bod[maxn];
void Add(int x,int y){
	edge[++tot]=(Edge){y,head[x]};
	head[x]=tot;
	deg[y]++;
	Bod[x].push_back(tot);
	Bod[y].push_back(tot);
}
namespace P19{
	int ans[maxn];
	int q[maxn],l,r;
	int Deg[maxn];
	bool Check(int s){
		l=1,r=0;
		FOR(i,1,n)if(i!=s&&!(Deg[i]=deg[i]))q[++r]=i;
		int tot=0;
		while(l<=r){
			int u=q[l++];
			tot++;
			EOR(u,v){
				if(v!=s&&!(--Deg[v]))
				q[++r]=v;
			}
		}return tot==n-1;
	}
	void solve(){
		FOR(i,1,n){
			FOO(j,Bod[i].size()){
				int x=Bod[i][j];
				if(edge[x].e!=i)deg[edge[x].e]--;
			}
			if(Check(i))ans[++ans[0]]=i;
			FOO(j,Bod[i].size()){
				int x=Bod[i][j];
				if(edge[x].e!=i)deg[edge[x].e]++;
			}
		}
		pf("%d\n",ans[0]);
		FOR(i,1,ans[0])pf("%d ",ans[i]);
	}
}
namespace P28{
	int q[maxn],l,r;
	bool vis[maxn];
	int tot=0;
	int stk[maxn],top;
	void solve(){
		l=1,r=0;
		FOR(i,1,n)if(!deg[i])q[++r]=i;
		while(l<=r){
			int u=q[l++];
			vis[u]=1;
			tot++;
			EOR(u,v)if(!(--deg[v]))q[++r]=v;
		}
		FOR(i,1,n)if(!vis[i]){
			int x=i;
			do{
				stk[++top]=x;
				tot++;
				EOR(x,y){
					x=y;
					break;
				}
				vis[x]=1;
			}while(x!=i);
			break;
		}
		if(tot!=n){
			puts("0");
			return;
		}
		pf("%d\n",top);
		cerr<<top<<endl;
		sot(stk,top);
		FOR(i,1,top)pf("%d ",stk[i]);
	}
}
namespace P50{
	int ad[maxn];
	int ans[maxn];
	void solve(){
		int tot=0;
		FOR(u,1,n){
			EOR(u,v)if(v<u){
				tot++;
				ad[v]++;
				ad[u+1]--;
			}
		}
		FOR(i,1,n)if((ad[i]+=ad[i-1])==tot)ans[++ans[0]]=i;
		pf("%d\n",ans[0]);
		FOR(i,1,ans[0])pf("%d ",ans[i]);
	}
}
namespace P63{
	bool vis[maxn];
	bool Check(){
		FOR(u,1,n)EOR(u,v)if(v==u%n+1)vis[u]=1;
		FOR(i,1,n)if(!vis[i])return 0;
		return 1;
	}
	int ad[maxn];
	int ans[maxn];
	void solve(){
		int tot=0;
		FOR(u,1,n){
			EOR(u,v)if(v!=u%n+1){
				tot++;
				if(u<v){
					ad[v]++;
					ad[n+1]--;
					ad[1]++;
					ad[u+1]--;
				}else{
					ad[v]++;
					ad[u+1]--;
				}
			}
		}
		FOR(i,1,n)if((ad[i]+=ad[i-1])==tot)ans[++ans[0]]=i;
		pf("%d\n",ans[0]);
		FOR(i,1,ans[0])pf("%d ",ans[i]);
	}
}
namespace P100{
	bool vis[maxn];
	int stk[maxn],top,lop[maxn],seg[maxn];
	int o[maxn],sz,id[maxn];
	bool mark[maxm<<1];
	int mxa[maxn],mxb[maxn],mna[maxn],mnb[maxn];
	int Mxa[maxn],Mxb[maxn],Mna[maxn],Mnb[maxn];
	void dfsa(int u){
		if(lop[u]){
			puts("0");
			exit(0);
		}
		if(vis[u])return;
		lop[u]=1;
		vis[u]=1;
		EOR(u,v)if(u_<=m){
			dfsa(v);
			tomax(mxa[u],mxa[v]);
			tomin(mna[u],mna[v]);
		}
		lop[u]=0;
	}
	void dfsb(int u){
		if(lop[u]){
			puts("0");
			exit(0);
		}
		if(vis[u])return;
		lop[u]=1;
		vis[u]=1;
		EOR(u,v)if(u_>m){
			dfsb(v);
			tomax(mxb[u],mxb[v]);
			tomin(mnb[u],mnb[v]);
		}
		lop[u]=0;
	}
	int ad[maxn];
	void Modi(int l,int r){
		if(l>r)return;
		ad[l]++;
		ad[r+1]--;
	}
	int ans[maxn];
	void Work(){
		int tmp=m;
		FOR(u,1,n)EOR(u,v)if(u_<=m){
			Add(v,u);
			++tmp;
			if(mark[u_])mark[tmp]=1;
		}
		FOR(i,1,n){
			vis[i]=lop[i]=0;
			Mxa[i]=Mxb[i]=mxa[i]=mxb[i]=0;
			Mna[i]=Mnb[i]=mna[i]=mnb[i]=n+1;
		}
		FOR(i,1,sz){
			int u=o[i];
			mxa[u]=mxb[u]=mna[u]=mnb[u]=id[u]=i;
			vis[u]=1;
		}
		FOR(i,1,sz){
			int u=o[i];
			EOR(u,v)if(u_<=m&&!mark[u_]){
				dfsa(v);
				tomax(Mxa[i],mxa[v]);
				tomin(Mna[i],mna[v]);
			}
		}
		FOR(i,1,n)if(!id[i])vis[i]=0;
		FOR(i,1,sz){
			int u=o[i];
			EOR(u,v)if(u_>m&&!mark[u_]){
				dfsb(v);
				tomax(Mxb[i],mxb[v]);
				tomin(Mnb[i],mnb[v]);
			}
		}
		FOR(i,1,n)if(!vis[i])dfsa(i);
		FOR(i,1,sz){
			if(Mna[i]<=i)Modi(1,Mna[i]-1),Modi(i+1,sz);
			if(Mxb[i]>=i)Modi(1,i-1),Modi(Mxb[i]+1,sz);
			if(Mxa[i]>=i)Modi(i+1,Mxa[i]-1);
			if(Mnb[i]<=i)Modi(Mnb[i]+1,i-1);
		}
		FOR(i,1,sz)if(!(ad[i]+=ad[i-1]))ans[++ans[0]]=o[i];
		sot(ans,ans[0]);
		pf("%d\n",ans[0]);
		FOR(i,1,ans[0])pf("%d ",ans[i]);
	}
	void dfs(int u){
		if(lop[u]){
			FOR(i,lop[u],top){
				o[++sz]=stk[i];
				mark[seg[i]]=1;
			}
			Work();
			exit(0);
		}
		if(vis[u])return;
		vis[u]=1;
		stk[++top]=u;
		lop[u]=top;
		EOR(u,v){
			seg[top]=u_;
			dfs(v);
		}
		lop[u]=0;
		top--;
	}
	void solve(){
		FOR(i,1,n)if(!vis[i])dfs(i);
		pf("%d\n",n);
		FOR(i,1,n)pf("%d ",i);
	}
}
vector<int>eg[maxn];
bool mem2;
int main(){
	freopen("reality.in","r",stdin);
	freopen("reality.out","w",stdout);
	int x,y;
	read2(n,m);
	bool flag28=n==m;
	bool flag50=1;
	FOR(i,1,m){
		read2(x,y);
		eg[x].push_back(y);
		flag28&=x==i;
		flag50&=y<x||y==x+1;
	}
	m=0;
	FOR(x,1,n){
		sort(eg[x].begin(),eg[x].end());
		eg[x].erase(unique(eg[x].begin(),eg[x].end()),eg[x].end());
		FOO(i,eg[x].size()){
			Add(x,eg[x][i]);
			m++;
		}
	}
	if(n<=2000)P19::solve();
	else if(flag28)P28::solve();
	else if(flag50)P50::solve();
	else if(P63::Check())P63::solve();
	else P100::solve();
	return 0;
}
