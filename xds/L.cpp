#include<bits/stdc++.h>
#define M 100005
using namespace std;
const int inf=1e9+7;
struct node{
	int x,h;
	bool operator < (const node & res)const{
		return x<res.x;
	}
}A[M];
int n;
int L[M],R[M];
int dp[M][2];//已经推了前i个，第i个推的的状态
void tomin(int &x,int y){
	if(x>y)x=y;
}
struct YD_tree{
	struct YD{
		int l,r,mi,lzy;
	}tree[M<<2];
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
	void up(int p){
		fa.mi=min(lson.mi,rson.mi);
	}
	void down(int p){
		if(fa.lzy!=inf){
			tomin(lson.mi,fa.lzy);
			tomin(rson.mi,fa.lzy);
			tomin(lson.lzy,fa.lzy);
			tomin(rson.lzy,fa.lzy);
			fa.lzy=inf;
		}
	}
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
	}
	void update(int l,int r,int d,int p){
		if(fa.l==l&&fa.r==r){
			tomin(fa.mi,d);
			tomin(fa.lzy,d);
			return;
		}
		down(p);
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)update(l,r,d,p<<1);
		else if(l>mid)update(l,r,d,p<<1|1);
		else {
			update(l,mid,d,p<<1);
			update(mid+1,r,d,p<<1|1);
		}
		up(p);
	}
	int query(int x,int p){
		
int main(){
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++)
			scanf("%d%d",&A[i].x,&A[i].h);
		sort(A+1,A+n+1);
		L[1]=1;
		for(int i=2;i<=n;i++){
			if(abs(A[i].x-A[i-1].x)<=A[i].h)L[i]=L[i-1];
			else L[i]=i;
		}
		R[n]=n;
		for(int i=n-1;i>=1;i--){
			if(abs(A[i].x-A[i+1].x)<=A[i].h)R[i]=R[i+1];
			else R[i]=i;
		}
		for(int i=1;i<=
	}
	return 0;
}
