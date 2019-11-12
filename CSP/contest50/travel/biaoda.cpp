#include<bits/stdc++.h>
#define debug(x) cerr<<"\tDEBUG: "<<#x<<" = "<<(x)<<endl;
using namespace std;
template<typename T>
inline void rd(T &res){
	static char c;res=0;
	bool f=0;
	while((c=getchar())<48)if(c=='-')f=1;
	do res=(res<<1)+(res<<3)+(c^48);
	while((c=getchar())>47);
	if(f)res=-res;
}
void Pt(int x){
	if(x>9)Pt(x/10);
	putchar(x%10^48);
}
inline void print(int x){
	if(x==0)putchar('0');
	else Pt(x);
}
const int maxn=2e5+100,inf=1e9;
bool cur1;
int n,m;
int tot,head[maxn],to[maxn<<1],nxt[maxn<<1];
void add_edge(int u,int v){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
int fa[maxn],dep[maxn];
int son[maxn],sz[maxn];
void dfs1(int f,int x){
	sz[x]=1;
	dep[x]=dep[f]+1;
	fa[x]=f;
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];
		if(y==f)continue;
		dfs1(x,y);
		sz[x]+=sz[y];
		if(sz[y]>sz[son[x]])son[x]=y;
	}
}
int top[maxn];
int id,L[maxn],dfn[maxn];
void dfs2(int Top,int x){
	L[x]=++id;
	dfn[id]=x;
	top[x]=Top;
	if(son[x])dfs2(Top,son[x]);
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];
		if(y==fa[x]||y==son[x])continue;
		dfs2(y,y);
	}
}
int jump(int x,int D){
	if(D==0)return x;
	if(dep[x]<=D)return 0;
	else {
		D--;
		while(D){
			if(dep[x]-dep[top[x]]<D){
				D-=dep[x]-dep[top[x]]+1;
				x=fa[top[x]];
			}else{
				x=dfn[L[x]-D];
				D=0;
			}
		}
		if(fa[x]<=n)return fa[x];
		return x;
	}
}
int LCA(int a,int b){
	while(top[a]!=top[b]){
		if(dep[top[a]]>dep[top[b]])
			a=fa[top[a]];
		else b=fa[top[b]];
	}
	return dep[a]<dep[b]?a:b;
}
const int S=70;
int pos[17][S+1][100005]; 
bool cur2;
int main(){
//	double Sz=&cur1-&cur2;
//	cout<<Sz/1024/1024<<endl;
//	freopen("data.in","r",stdin);
//	freopen("my.out","w",stdout);
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
	rd(n);
	for(int i=1,x,y,z;i<n;i++){
		rd(x);rd(y);rd(z);
		if(z==1){
			add_edge(x,y);
			add_edge(y,x);
		}else {
			add_edge(x,i+n);
			add_edge(i+n,x);
			add_edge(y,i+n);
			add_edge(i+n,y);
		}
	}
	dfs1(0,1);
	dfs2(1,1);
	for(int t=2;t<=S;t++){
		for(int i=1;i<=n;i++)
			pos[0][t][i]=jump(i,t);
		for(int i=1;i<17;i++){
			for(int j=1;j<=n;j++){
				pos[i][t][j]=pos[i-1][t][pos[i-1][t][j]];
			}
		}
	}
	rd(m);
	for(int i=1,u,v,p;i<=m;i++){
		rd(u);rd(v);rd(p);
		if(u==v){
			puts("0");
			continue;
		}
		int lca=LCA(u,v);
		int ans=0;
		if(p<=S){
			for(int i=16;i>=0;i--){
				if(pos[i][p][u]!=0&&dep[pos[i][p][u]]>dep[lca]){
					u=pos[i][p][u];
					ans+=1<<i;
				}
				if(pos[i][p][v]!=0&&dep[pos[i][p][v]]>dep[lca]){
					v=pos[i][p][v];
					ans+=1<<i;
				}
			}
		}else {
			while(1){
				int nxt=jump(u,p);
				if(dep[nxt]<=dep[lca])break;
				u=nxt;
				ans++;
			}
			while(1){
				int nxt=jump(v,p);
				if(dep[nxt]<=dep[lca])break;
				v=nxt;
				ans++;
			}
		}
		int tmp=dep[u]+dep[v]-dep[lca]*2;
		if(tmp>0&&tmp<=p){
			ans++;
		}else if(tmp>p)
			ans+=2;
		print(ans);putchar('\n');
//		printf("%d\n",ans);
	}
	return 0;
}

