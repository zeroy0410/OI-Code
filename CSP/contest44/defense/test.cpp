#include<bits/stdc++.h>
#define LL long long
#define clr(x,y) memset(x,y,sizeof(x))
#define FOR(x,l,r) for(int x=l,x##_=r;x<=x##_;x++)
#define FR(x,l,r) for(int x=l,x##_=r;x<x##_;x++)
#define DOR(x,r,l) for(int x=r,x##_=l;x>=x##_;x--)
#define Min4(a,b,c,d) min(min(a,b),min(c,d))
#define Min3(a,b,c) min(min(a,b),c)
using namespace std;
const int N=1e5+5;
const LL INF=1e12;
int n,m,A[N];
char ty[10];
struct node{
	int a,x,b,y;
}Q[N];
int fa[N],dep[N],sz[N],son[N],top[N],ID[N];
int L[N],R[N],tot;
vector<int>edge[N];
LL dp[N][2];
void redfs(int x,int f){
	fa[x]=f;
	sz[x]=1;
	dep[x]=dep[f]+1;
	FR(i,0,edge[x].size()){
		int to=edge[x][i];
		if(to==f)continue;
		redfs(to,x);
		sz[x]+=sz[to];
		if(sz[to]>sz[son[x]])son[x]=to;
	}
}
bool chk(int x,int y){
	return x==fa[y]||y==fa[x];
}
struct P44{
	int a,X,b,Y;
	void dfs(int x,int f){
		if(x==a)dp[x][X]=A[x]*X;
		else if(x==b)dp[x][Y]=A[x]*Y;
		else dp[x][1]=A[x],dp[x][0]=0;
		FR(i,0,edge[x].size()){
			int to=edge[x][i];
			if(to==f)continue;
			dfs(to,x);
			dp[x][0]+=dp[to][1];
			dp[x][1]+=min(dp[to][0],dp[to][1]);
		}
	}
	void sl(){
		FOR(i,1,m){
			if(Q[i].x==0&&Q[i].y==0&&chk(Q[i].a,Q[i].b)){puts("-1");continue;}
			a=Q[i].a,X=Q[i].x,b=Q[i].b,Y=Q[i].y;
			clr(dp,63);
			dfs(1,0);
			printf("%lld\n",min(dp[1][1],dp[1][0]));
		}
	}
}p44;
struct YD{
	LL b[4];
	YD operator+(const YD&_)const{
		YD tmp;
		tmp.b[0]=Min3(b[2]+_.b[0],b[0]+_.b[1],b[2]+_.b[1]);
		tmp.b[1]=Min3(b[3]+_.b[0],b[1]+_.b[1],b[3]+_.b[1]);
		tmp.b[2]=Min3(b[2]+_.b[2],b[0]+_.b[3],b[2]+_.b[3]);
		tmp.b[3]=Min3(b[1]+_.b[3],b[3]+_.b[1],b[3]+_.b[3]);
		return tmp;
	}
	void init(LL x,LL y){
		b[0]=x;
		b[1]=b[2]=INF;
		b[3]=y;
	}
	LL mn1(){
		return min(b[1],b[3]);
	}
	LL mn(){
		return Min4(b[0],b[1],b[2],b[3]);
	}
	void clear(){
		b[0]=b[1]=b[2]=b[3]=INF;
	}
	void Print(){
		printf("%lld %lld %lld %lld\n",b[0]>=INF?-1:b[0],b[1]>=INF?-1:b[1],b[2]>=INF?-1:b[2],b[3]>=INF?-1:b[3]);
	}
}ze;
struct JUST_MOD_YD{
	#define ls p<<1
	#define rs p<<1|1
	#define lson tr[ls]
	#define rson tr[rs]
	struct YDtql_YDorz{
		int l,r;
		int len(){return r-l+1;}
		YD v;
	}tr[N<<2];
	void UP(int p){
		tr[p].v=lson.v+rson.v;
	}
	void Build(int l,int r,int p){
		tr[p].l=l,tr[p].r=r;
		if(l==r){
			tr[p].v.init(dp[ID[l]][0],dp[ID[l]][1]);
//			printf("%d %d  %d\n",l,r,ID[l]);
//			tr[p].v.Print();
			return;
		}
		int mid=(l+r)>>1;
		Build(l,mid,ls);
		Build(mid+1,r,rs);
		UP(p);
//		printf("%d %d\n",l,r);
//		tr[p].v.Print();
	}
	void insert(int x,int p,int d0,int d1){
		if(tr[p].l==tr[p].r){
			tr[p].v.init(d0,d1);
			return;
		}
		int mid=(tr[p].l+tr[p].r)>>1;
		if(x<=mid)insert(x,ls,d0,d1);
		else insert(x,rs,d0,d1);
		UP(p);
	}
	YD query(int l,int r,int p){
//		if(p==1)printf("\n\n%d %d %d\n",l,r,p);
		if(l>r)return ze;
		if(l==tr[p].l&&tr[p].r==r){
//			printf("%d %d %d\n",l,r,p);
//			tr[p].v.Print();
			return tr[p].v;
		}
		int mid=(tr[p].l+tr[p].r)>>1;
		if(r<=mid)return query(l,r,ls);
		else if(l>mid)return query(l,r,rs);
		else return query(l,mid,ls)+query(mid+1,r,rs);
	}
	void update(int x,int p,LL d0,LL d1){
		if(tr[p].l==tr[p].r){
			tr[p].v.b[0]+=d0;
			tr[p].v.b[3]+=d1;
			return;
		}
		int mid=(tr[p].l+tr[p].r)>>1;
		if(x<=mid)update(x,ls,d0,d1);
		else update(x,rs,d0,d1);
		UP(p);
	}
	void Charge(int x,int d){
		LL pre[2];
		pre[!d]=INF,pre[d]=0;
		while(x){
			int tp=top[x];
			YD res=query(L[tp],R[tp],1);
			update(L[x],1,pre[0],pre[1]);
			YD now=query(L[tp],R[tp],1);
			pre[0]=now.mn1()-res.mn1();
			pre[1]=now.mn()-res.mn();
			x=fa[tp];
		}
	}
	void remain(int x,int p){
		if(tr[p].l==tr[p].r){
			tr[p].v.b[0]=dp[ID[tr[p].l]][0];
			tr[p].v.b[3]=dp[ID[tr[p].l]][1];
			return;
		}
		int mid=(tr[p].l+tr[p].r)>>1;
		if(x<=mid)remain(x,ls);
		else remain(x,rs);
		UP(p);
	}
	void Uncharge(int x){
		while(x){
			int tp=top[x];
			remain(L[x],1);
			x=fa[tp];
		}
	}
}tree;
struct P56{
	LL val[N][2];
	void dfs_top(int x,int f,int tp){
		top[x]=tp;
		L[x]=++tot;
		ID[tot]=x;
		dp[x][0]=0,dp[x][1]=A[x];
		if(son[x])dfs_top(son[x],x,tp);
		else R[tp]=x;
		FR(i,0,edge[x].size()){
			int to=edge[x][i];
			if(to==f||to==son[x])continue;
			dfs_top(to,x,x);
		}
		FR(i,0,edge[x].size()){
			int to=edge[x][i];
			if(to==f||to==son[x])continue;
			dp[x][0]+=val[to][1];
			dp[x][0]+=min(val[to][0],val[to][1]);
		}
		val[x][0]=dp[x][0]+val[son[x]][1];
		val[x][1]=dp[x][1]+min(val[son[x]][1],val[son[x]][0]);
//		printf("%d: \n",x);
//		printf("x: %d : %lld %lld\n",x,dp[x][0],dp[x][1]);
//		printf("val: %lld %lld\n",val[x][0],val[x][1]);
	}
	void sl(){
		FOR(i,0,3)ze.b[i]=0;
		dfs_top(1,0,1);
		tree.Build(1,n,1);
//		tree.tr[1].v.Print();
//		printf("L R: %d %d\n",L[1],R[1]);
//		YD res=tree.query(L[1],R[1],1);
//		LL ans=res.mn();
//		if(ans>=INF)ans=-1;
//		printf("%lld\n",ans);
		FOR(i,1,m){
			int a=Q[i].a,x=Q[i].x,b=Q[i].b,y=Q[i].y;
			tree.Charge(a,x);
			tree.Charge(b,y);
			YD res=tree.query(L[1],R[1],1);
			LL ans=res.mn();
			if(ans>=INF)ans=-1;
			printf("%lld\n",ans);
			tree.Uncharge(a);
			tree.Uncharge(b);
		}
	}
}p56;
int main(){
//	freopen("defense.in","r",stdin);
//	freopen("defense.out","w",stdout);
	scanf("%d%d%s",&n,&m,ty);
	FOR(i,1,n)scanf("%d",A+i);
	FOR(i,2,n){
		int x,y;
		scanf("%d%d",&x,&y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	redfs(1,0);
	FOR(i,1,m)scanf("%d%d%d%d",&Q[i].a,&Q[i].x,&Q[i].b,&Q[i].y);
//	if(n<=2000)p44.sl();
//	else 
	p56.sl();
	
	return 0;
}

