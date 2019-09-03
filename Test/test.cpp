#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,q;
struct node{int x,y;}A[M];
struct poi{int a,b;};
struct YD_tree{
	struct YD{
		int l,r;
		poi xmx,xmi,ymx,ymi;
	}tree[M<<2];
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
	YD up(YD &a,YD &b){
		YD c;
		c.l=a.l;c.r=b.r;
		c.xmx=max(a.xmx,b.xmx);
		c.xmi=min(a.xmi,b.xmi);
		c.ymx=max(a.ymx,b.ymx);
		c.ymi=min(a.ymi,b.ymi);
		return c;
	}
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;
		if(l==r){
			fa.xmi=fa.xmx=A[i].x;
			fa.ymi=fa.ymx=A[i].y;
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
	}

int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&A[i].x,&A[i].y);
	return 0;
}
