#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n,t,K;
struct node{
	int x1,y1,x2,y2,id;
	bool operator < (const node& res)const{
		return x1<res.x1;
	}
}A[M],st;
int B[M<<1],bcnt;
struct YD_tree{
	struct YD{
		int l,r;
		LL mx,ad;
	}tree[M<<3];
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
	void down(int p){
		if(fa.ad){
			lson.mx=max(lson.mx,fa.ad);
			rson.mx=max(rson.mx,fa.ad);
			lson.ad=max(lson.ad,fa.ad);
			rson.ad=max(rson.ad,fa.ad);
		}
	}
	void up(int p){
		fa.mx=max(lson.mx,rson.mx);
	}
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;fa.mx=fa.ad=-1e9;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
	}
	void update(int l,int r,LL d,int p){
		if(fa.l==l&&fa.r==r){
			fa.mx=max(fa.mx,d);
			fa.ad=max(fa.ad,d);
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
	LL query(int l,int r,int p){
		if(fa.l==l&&fa.r==r)return fa.mx;
		int mid=(fa.l+fa.r)>>1;
		down(p);
		if(r<=mid)return query(l,r,p<<1);
		else if(l>mid)return query(l,r,p<<1|1);
		return max(query(l,mid,p<<1),query(mid+1,r,p<<1|1));
	}
}Tr;
LL ans[M];
int main(){
	scanf("%d%d%d",&n,&t,&K);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&A[i].x1,&A[i].y1,&A[i].x2,&A[i].y2);
		A[i].id=i;
		B[++bcnt]=A[i].y1;B[++bcnt]=A[i].y2-1;
	}
	sort(B+1,B+bcnt+1);
	bcnt=unique(B+1,B+bcnt+1)-B-1;
	Tr.build(1,bcnt,1);
	for(int i=1;i<=n;i++){
		A[i].y1=lower_bound(B+1,B+bcnt+1,A[i].y1)-B;
		A[i].y2=lower_bound(B+1,B+bcnt+1,A[i].y2-1)-B;
	}
	sort(A+1,A+n+1);
	int st=0;
	for(int i=1;i<=n;i++)ans[A[i].id]=A[i].x1;
	for(int i=1;i<=n;i++)
		if(A[i].id==t){st=i;break;}
	Tr.update(A[st].y1,A[st].y2-1,A[st].x2-A[st].x1,1);
	ans[A[st].id]+=K;
	for(int i=st+1;i<=n;i++){
		LL now=Tr.query(A[i].y1,A[i].y2,1);
		if(now!=-1e9&&now+ans[A[st].id]>A[i].x1){
			Tr.update(A[i].y1,A[i].y2,now+A[i].x2-A[i].x1,1);
			ans[A[i].id]=now+ans[A[st].id];
		}
	}
	for(int i=1;i<=n;i++)
		printf("%lld ",ans[i]);
	puts("");
	return 0;
}
