#include<bits/stdc++.h>
#define M 100005
using namespace std;
const int mod=998244353;
const int inv2=499122177;
int n,m,pw=1;
struct YD_tree{
	struct node{
		int l,r,f,g,sum,mul,ans;
	}tree[M<<3];
	#define fa tree[p]
	#define lson tree[p<<1]
	#define rson tree[p<<1|1]
	void up(int p){ fa.ans=((lson.ans+rson.ans)%mod+fa.f)%mod; }
	void downtag(int ad,int mu,int p){
		fa.g=(1LL*fa.g*mu+ad)%mod;
		fa.mul=1LL*fa.mul*mu%mod;
		fa.sum=(1LL*fa.sum*mu%mod+ad)%mod;
	}
	void down(int p){
		if(fa.mul==1&&fa.sum==0)return;
		downtag(fa.sum,fa.mul,p<<1);
		downtag(fa.sum,fa.mul,p<<1|1);
		fa.mul=1;fa.sum=0;
	}
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;fa.sum=fa.f=fa.g=fa.ans=0;fa.mul=1;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
	}
	void reset(int p){ fa.f=1LL*(fa.f+fa.g)*inv2%mod;up(p); }
	void update(int l,int r,int p){
		if(fa.l==l&&fa.r==r){
			fa.f=1LL*inv2*(fa.f+1)%mod;
			downtag(inv2,inv2,p);up(p);
			return;
		}
		int mid=(fa.l+fa.r)>>1;down(p);
		fa.f=1LL*fa.f*inv2%mod;
		fa.g=1LL*fa.g*inv2%mod;
		if(r<=mid){update(l,r,p<<1);reset(p<<1|1);}
		else if(l>mid){update(l,r,p<<1|1);reset(p<<1);}
		else {
			update(l,mid,p<<1);
			update(mid+1,r,p<<1|1);
		}
		up(p);
	}
}Tr;
int main(){
	scanf("%d%d",&n,&m);
	Tr.build(1,n,1);
	while(m--){
		int op,l,r;
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&l,&r);
			Tr.update(l,r,1);
			pw=(pw+pw)%mod;
		}
		else printf("%lld\n",1LL*Tr.tree[1].ans*pw%mod);
	}
	return 0;
}
