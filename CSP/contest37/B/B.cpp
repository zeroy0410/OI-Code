#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,m,R,A[M],l[M],r[M],ret[M];
struct YD_tree{
	struct node{
		int l,r,mx,lzy,ct;
	}tree[M<<2];
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
	void down(int p){
		if(fa.lzy){
			lson.lzy=rson.lzy=1;
			lson.ct=rson.ct=0;
			fa.lzy=0;
		}
	}
	void up(int p){
		fa.mx=max(lson.mx,rson.mx);
		fa.ct=lson.ct+rson.ct;
	}
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;fa.lzy=0;
		if(l==r){fa.mx=A[l];fa.ct=(l!=0);return;}
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
		up(p);
	}
	void update(int l,int r,int p){
		if(fa.l==l&&fa.r==r){
			fa.ct=0;fa.lzy=1;
			return;
		}
		down(p);
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)update(l,r,p<<1);
		else if(l>mid)update(l,r,p<<1|1);
		else {
			update(l,mid,p<<1);
			update(mid+1,r,p<<1|1);
		}
		up(p);
	}
	int query(int x,int p){
		while(fa.l!=fa.r){
			down(p);
			if(lson.ct>=x)p=p<<1;
			else x-=lson.ct,p=p<<1|1;
		}
		return fa.l;
	}
	int Query(int l,int r,int p){
		if(fa.l==l&&fa.r==r)return fa.mx;
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)return Query(l,r,p<<1);
		else if(l>mid)return Query(l,r,p<<1|1);
		return max(Query(l,mid,p<<1),Query(mid+1,r,p<<1|1));
	}
}Tr;
int main(){
//	freopen("tournament.in","r",stdin);
//	freopen("tournament.out","w",stdout);
	scanf("%d%d%d",&n,&m,&R);
	for(int i=1;i<n;i++)scanf("%d",&A[i]);
	for(int i=1;i<=m;i++)scanf("%d%d",&l[i],&r[i]),l[i]++,r[i]++;
	Tr.build(0,n,1);
	for(int i=1;i<=m;i++){
		int s=Tr.query(l[i]-1,1)+1;
		int t=Tr.query(r[i],1);
		Tr.update(s,t-1,1);
		if(Tr.Query(s,t-1,1)<R)ret[s]++,ret[t+1]--;
	}
	int mx=-1,ans;
	for(int i=1;i<=n;i++){
		ret[i]+=ret[i-1];
		if(ret[i]>mx){
			mx=ret[i];
			ans=i;
		}
	}
	printf("%d\n",ans-1);
	return 0;
}
