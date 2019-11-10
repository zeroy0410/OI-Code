#include<bits/stdc++.h>
#define M 500005
using namespace std;
int n,q;
char S[M];
int sum[M];
struct node{
	int mi,c;
	void Add(node x){
		mi=min(mi,x.mi);
		c+=x.c;
	}
};
struct YD_tree{
	struct tr{
		int l,r,mi,cnt,lzy;
		void reset(int x){
			lzy+=x;mi+=x;
		}
	}tree[M<<2];
	#define fa tree[p]
	#define lson tree[p<<1]
	#define rson tree[p<<1|1]
	void up(int p){
		fa.mi=min(lson.mi,rson.mi);
		fa.cnt=lson.cnt+rson.cnt;
	}
	void down(int p){
		if(fa.lzy){
			lson.reset(fa.lzy);
			rson.reset(fa.lzy);
			fa.lzy=0;
		}
	}
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;fa.lzy=0;
		if(l==r){fa.mi=sum[l];return;}
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
		up(p);
	}
	void Addsum(int l,int r,int c,int p){
		if(fa.l==l&&fa.r==r){
			fa.reset(c);
			return;
		}
		int mid=(fa.l+fa.r)>>1;
		down(p);
		if(mid>=r)Addsum(l,r,c,p<<1);
		else if(mid<l)Addsum(l,r,c,p<<1|1);
		else Addsum(l,mid,c,p<<1),Addsum(mid+1,r,c,p<<1|1);
		up(p);
	}
	void Addc(int x,int c,int p){
		if(fa.l==fa.r){
			fa.cnt+=c;
			return;
		}
		int mid=(fa.l+fa.r)>>1;
		down(p);
		if(mid>=x)Addc(x,c,p<<1);
		else Addc(x,c,p<<1|1);
		up(p);
	}
	node Query(int l,int r,int p){
		if(fa.l==l&&fa.r==r)return (node){fa.mi,fa.cnt};
		int mid=(fa.l+fa.r)>>1;
		down(p);
		if(mid>=r)return Query(l,r,p<<1);
		else if(mid<l)return Query(l,r,p<<1|1);
		else {
			node res=Query(l,mid,p<<1);
			res.Add(Query(mid+1,r,p<<1|1));
			return res;
		}
	}
}Tr;
struct que{int r,id;};
vector<que>wk[M];
int stk[M],top,ans[M];
int main(){
//	freopen("elections.in","r",stdin);
//	freopen("elections.out","w",stdout);
	scanf("%d%s%d",&n,S+1,&q);
	for(int i=1,l,r;i<=q;i++)scanf("%d%d",&l,&r),wk[l].push_back((que){r,i});
	for(int i=n;i>=1;i--)sum[i]=sum[i+1]+(S[i]=='T'?-1:1);//C比T多多少个（后缀） 
	Tr.build(1,n,1);
	for(int i=n;i>=1;i--){
		if(S[i]=='T'){
			stk[++top]=i;
			Tr.Addsum(1,i,1,1);
			Tr.Addc(i,1,1);
		}
		else if(top){
			int t=stk[top--];
			Tr.Addsum(1,t,-1,1);
			Tr.Addc(t,-1,1);
		}
		for(int j=0,sz=wk[i].size();j<sz;j++){
			int r=wk[i][j].r,id=wk[i][j].id;
			node e=Tr.Query(i,r,1);
			ans[id]=e.c;//当前区间有哪些点还没有被前缀抵消 
			e.mi-=top-e.c;//[r+1,n]还没被抵消的点要减去，变成最小后缀和 
			if(e.mi<sum[r+1])
				ans[id]+=-(e.mi-sum[r+1]);
		}
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
	return 0;
}
