#include<bits/stdc++.h>
#define M 500005
#define LL long long
using namespace std;
int n,q,opt;
LL ans=0,l,r;
struct node{
	int l,r;
	LL A,B,C;
	node operator + (const node& res){
		node ans;
		ans.A=res.A+A;
		ans.B=res.B+B;
		ans.C=res.C+C;
		return ans;
	}
}tree[M<<2];
struct P100{
	LL res;
	LL calc(LL x){return x*(x+1)/2;}
	struct YD{
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
		void build(LL l,LL r,LL fl,LL fr,int p){
			fa.l=l;fa.r=r;
			fa.A=l-fr;fa.B=r-fl;fa.C=-(l*l+l+r*r-r)/2+fl*fr-fl+fr;
			if(l==r)return;
			int mid=(l+r)>>1;
			build(l,mid,l,r,p<<1);
			build(mid+1,r,l,r,p<<1|1);
			fa.A+=lson.A+rson.A;
			fa.B+=lson.B+rson.B;
			fa.C+=lson.C+rson.C;
		}
		LL query(LL l,LL r,LL fl,LL fr,int p){
			if(l<=fa.l&&r>=fa.r){
				node tmp=fa;
				tmp.A+=fr-1;tmp.B+=fl+1;tmp.C+=-fl*fr+fl-fr+1-l*r;
				return tmp.A*l+tmp.B*r+tmp.C;
			}
			int mid=(fa.l+fa.r)>>1;
			LL res=0;
			if(l<=mid)res+=query(l,r,fa.l,fa.r,p<<1);
			if(r>mid)res+=query(l,r,fa.l,fa.r,p<<1|1);
			return res;
		}
	}Tr;
	void query(int L,int R){
		if(L<=l&&r<R||L<l&&r<=R){res+=calc(r-l+1);}
		else if(l>L&&l<=R&&r>R){res+=calc(r-l+1)-calc(r-R);}
		else if(r>=L&&r<R&&l<L){res+=calc(r-l+1)-calc(L-l);}
		if(l<=L&&r>=R)return;
		int mid=(L+R)>>1;
		if(l<=mid)query(L,mid);
		if(r>mid)query(mid+1,R);
	}
	void solve(){
		Tr.build(1,n,0,0,1);
		while(q--){
			scanf("%lld %lld",&l,&r);
			LL a=(l^(ans*opt))%n+1;
			LL b=(r^(ans*opt))%n+1;
			l=min(a,b);r=max(a,b);
			res=0;
			query(1,n);
			res+=Tr.query(l,r,0,0,1);
			ans=res;
			printf("%lld\n",ans);
		}

	}
}p100;
int main(){
	scanf("%d%d%d",&n,&q,&opt);
	p100.solve();
	return 0;
}
