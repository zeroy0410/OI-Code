#include<bits/stdc++.h>
#define M 500005
using namespace std;
int n,m,mod;
struct node{
	int l,b,pr;
	bool operator < (const node& res)const{
		return l<res.l;	
	}
}A[M];
struct YD_tree{
	struct YD{
		int l,r,sum;
	}tree[M<<2];
	#define fa tree[p]
	#define lson tree[p<<1]
	#define rson tree[p<<1|1]
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;
		if(l==r){fa.sum=1;return;}	
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
		fa.sum=1LL*lson.sum*rson.sum%mod;
	}
	void update(int x,int p){
		if(fa.l==fa.r&&fa.l==x){
			fa.sum++;fa.sum%=mod;
			return;
		}
		int mid=(fa.l+fa.r)>>1;
		if(x<=mid)update(x,p<<1);
		else update(x,p<<1|1);
		fa.sum=1LL*lson.sum*rson.sum%mod;
	}
	int query(int l,int r,int p){
		if(l>r)return 1; 
		if(fa.l==l&&fa.r==r)return fa.sum;
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)return query(l,r,p<<1);
		else if(l>mid)return query(l,r,p<<1|1);
		return query(l,mid,p<<1)*query(mid+1,r,p<<1|1)%mod;	
	}
}T;
int H[M],w[M],mp[M];
int las[M],now[M],v[M];
int find(int x){
	int l=1,r=m,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(A[w[mid]].l>=x){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	if(A[w[m]].l<x)return m+1;
	return ans;
}
int main(){
	freopen("fish.in","r",stdin);
	freopen("fish.out","w",stdout); 
	scanf("%d%d%d",&n,&m,&mod);
	for(int i=1;i<=n;i++)scanf("%d%d",&A[i].l,&A[i].b);
	sort(A+1,A+n+1);T.build(1,m,1);
	for(int i=n;i>=1;i--){
		if(!H[A[i].b])H[A[i].b]=i;
		A[i].pr=las[A[i].b];
		las[A[i].b]=i;
	}m=0;
	int ans=0;
	for(int i=1;i<=n;i++)if(H[A[i].b]==i)w[mp[A[i].b]=++m]=i;
	int cur=1;
	for(int i=1;i<=m;i++){
		while(A[cur].l*2<=A[w[i]].l){
			now[A[cur].b]=cur;
			v[mp[A[cur].b]]++;
			T.update(mp[A[cur].b],1);
			cur++;
		}
		int k,d=T.query(1,i-1,1);
		if(!now[A[w[i]].b])k=las[A[w[i]].b];
		else k=A[now[A[w[i]].b]].pr;
		if(!k)k=m+1;
		else k=find(A[k].l<<1);
		ans=(ans+1LL*d*T.query(i+1,k-1,1)%mod+1LL*d*v[i]%mod)%mod;
	}
	printf("%d\n",ans);
	return 0;
}		
