#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
const int mod=1e9+7;
int n,m,A[M];
void Add(LL &x,LL y){
	x+=y;
	if(x>=mod)x-=mod;
	if(x<0)x+=mod;
}
struct YD_tree{
	struct node{
		int l,r;
		LL val,ad;
	}tree[M<<2];
	int tid[M];
	int stk[M<<2],top;
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;fa.ad=1;fa.val=0;
		if(l==r){
			tid[l]=p;
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
	}
	void up(int p){
		fa.val=(lson.val+rson.val)%mod;
	}
	void mul(int p,LL d){
		fa.val=fa.val*d%mod;
		fa.ad=fa.ad*d%mod;
	}
	void down(int p){
		if(fa.ad>1){
			mul(p<<1,fa.ad);
			mul(p<<1|1,fa.ad);
			fa.ad=1;
		}
	}
	void update(int x,LL d){
		top=0;int t=tid[x];
		while(t){
			stk[++top]=t;
			t>>=1;
		}
		for(int i=top;i>=2;i--)down(stk[i]);
		tree[tid[x]].val=(tree[tid[x]].val+d)%mod;
		for(int i=2;i<=top;i++)up(stk[i]);
	}
	void Update(int l,int r,int p){
		if(l>r)return;
		if(fa.l==l&&fa.r==r){ mul(p,2);return; }
		int mid=(fa.l+fa.r)>>1;
		down(p);
		if(r<=mid)Update(l,r,p<<1);
		else if(l>mid)Update(l,r,p<<1|1);
		else {
			Update(l,mid,p<<1);
			Update(mid+1,r,p<<1|1);
		}
		up(p);
	}
	LL query(int l,int r,int p){
		if(l==fa.l&&r==fa.r)return fa.val;
		down(p);
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)return query(l,r,p<<1);
		else if(l>mid)return query(l,r,p<<1|1);
		return (query(l,mid,p<<1)+query(mid+1,r,p<<1|1))%mod;
	}
}Tr[25];
LL C[25][25];
LL dp[M][25];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	C[0][0]=1;
	for(int i=1;i<=m;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			Add(C[i][j],C[i-1][j]),Add(C[i][j],C[i-1][j-1]);
	}
	for(int i=0;i<=m+1;i++)Tr[i].build(0,n,1);
	for(int i=0;i<=m;i++)Tr[i].update(0,1);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++)dp[i][j]=Tr[j].query(0,A[i]-1,1);
		for(int k=0;k<=m;k++){
			LL sum=0;
			for(int j=0;j<=k;j++)Add(sum,dp[i][j]*C[k][j]%mod);
			Tr[k].update(A[i],sum);
		}
		for(int j=0;j<=m+1;j++)Tr[j].Update(A[i]+1,n,1);
		Tr[m+1].update(A[i],dp[i][m]);
	}
	LL ans=Tr[m+1].query(1,n,1);
	printf("%lld\n",ans);
	return 0;
}
