#include<stdio.h>
#define M 200005
#define LL long long
const int mod=1e9+7;
int n,m,b;
char S[M];
LL Pow[M],Sum[M];
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
struct node{
	int len;
	LL ls,rs,ss,sum;
	node operator +(node res){
		node ans;
		ans.len=len+res.len;
		ans.sum=(sum*Pow[res.len]+res.sum)%mod;
		ans.ss=(ss+res.ss+(rs*Sum[res.len]+res.ls*len))%mod;
		ans.rs=(rs*Pow[res.len]+res.sum*len+res.rs)%mod;
		ans.ls=(sum*Sum[res.len]+res.ls+ls)%mod;
		return ans;
	}
};
struct YD_tree{
	struct YD{
		int l,r;
		node x;
	}tree[M<<2];
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
	void up(int p){
		fa.x=lson.x+rson.x;
	}
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;
		if(l==r){
			fa.x.len=r-l+1;
			fa.x.ls=fa.x.rs=fa.x.ss=fa.x.sum=S[l];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
		up(p);
	}
	void update(int x,int d,int p){
		if(fa.l==x&&fa.r==x){
			fa.x.ls=fa.x.rs=fa.x.ss=fa.x.sum=d;
			return;
		}
		int mid=(fa.l+fa.r)>>1;
		if(x<=mid)update(x,d,p<<1);
		else update(x,d,p<<1|1);
		up(p);
	}
	node query(int l,int r,int p){
		if(fa.l==l&&fa.r==r)return fa.x;
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)return query(l,r,p<<1);
		else if(l>mid)return query(l,r,p<<1|1);
		return query(l,mid,p<<1)+query(mid+1,r,p<<1|1);
	}
}Tr;
char ss[15];
int main(){
	scanf("%d%d%d",&n,&m,&b);
    scanf("%s",S+1);
    for(int i=1;i<=n;i++)S[i]=S[i]-'a'+1;
    Pow[0]=1;
	for(int i=1;i<=n+1;i++)Pow[i]=Pow[i-1]*b%mod,Sum[i]=(Sum[i-1]+Pow[i])%mod;
	Tr.build(1,n,1);
	while(m--){
		int op,l,r;
		scanf("%d",&op);
		if(op==0){
			scanf("%d%d",&l,&r);
			LL tot=r-l+1;
			tot=(tot*(tot-1)%mod*qkpow(2,mod-2)%mod+tot)%mod;
			printf("%lld\n",(Tr.query(l,r,1).ss*qkpow(tot,mod-2)%mod+mod)%mod);
		}
		else {
			scanf("%d%s",&l,ss);
			Tr.update(l,ss[0]-'a'+1,1);
		}
	}
	return 0;
}
