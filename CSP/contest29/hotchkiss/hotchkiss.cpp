#include<bits/stdc++.h>
#define M 1000005
using namespace std;
int n,m,A[M<<1];
inline void read(int &x){
	char c;
	x=0;
	int f=1;
	while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
	do x=(x<<3)+(x<<1)+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	x*=f;
}
int h[M<<1],tt;
struct edge{
	int nxt,to;
}G[M<<2];
inline void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int fa[M<<1][21],dep[M<<1],l[M<<1],r[M<<1],stk[M<<1],top,Fa[M<<1],rt[M<<1],deg[M<<1];
void dfs(int x,int d,int rr){
	fa[x][0]=Fa[x];dep[x]=d;rt[x]=rr;
	for(int i=1;(1<<i)<dep[x];i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		dfs(u,d+1,rr);
	}
}
inline int LCA(int a,int b){
	if(dep[a]>dep[b])swap(a,b);
	int step=dep[b]-dep[a];
	for(int i=20;i>=0;i--)
		if(step&1<<i)b=fa[b][i];
	if(a==b)return a;
	for(int i=20;i>=0;i--)
		if(fa[a][i]!=fa[b][i])
			a=fa[a][i],b=fa[b][i];
	return fa[a][0];
}
int main(){
	freopen("hotchkiss.in","r",stdin);
	freopen("hotchkiss.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n*2;i++)read(A[i]);
	for(register int i=1;i<=n*2;i++){
		l[i]=min(i,A[i]);
		r[i]=max(i,A[i]);
		while(top&&stk[top]>=l[i]){
			int p=stk[top--];
			l[i]=min(l[i],l[p]);
			r[i]=max(r[i],r[p]);
		}
		stk[++top]=i;
	}
	for(register int i=0;i<=n*2;i++)Fa[i]=rt[i]=-1;
	for(register int i=1;i<=n*2;i++)if(r[i]==i){
		Fa[i]=l[i]-1;
		Add(l[i]-1,i);
		deg[l[i]-1]++;
	}
	r[0]=0;
	for(register int i=0;i<=n*2;i++)
		if(rt[i]==-1&&deg[i]!=0)dfs(i,1,i);
	for(register int i=1,r1,r2;i<=m;i++){
		read(r1);read(r2);
		if(r1==0||r2==0||rt[r1]==-1||rt[r2]==-1||rt[r1]!=rt[r2])puts("0");
		else printf("%d\n",dep[LCA(Fa[r1],Fa[r2])]);
	}
	return 0;
}
