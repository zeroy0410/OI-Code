#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n,W,A[M];
LL sum[M];
LL S(int l,int r){
	return sum[r]-sum[l-1];
}
struct P60{
	int mx[5005][5005],mi[5005][5005];
	LL dp[5005];
	void solve(){
		for(int i=1;i<=n;i++){
			mx[i][i]=A[i];mi[i][i]=A[i];
			for(int j=i+1;j<=n;j++){
				mx[i][j]=max(A[j],mx[i][j-1]);
				mi[i][j]=min(A[j],mi[i][j-1]);
			}
		}
		memset(dp,0x3f,sizeof(dp));
		dp[0]=0;
		for(int i=1;i<=n;i++){
			int pos=0;
			for(int j=i;j>=1;j--){
				if(S(j,i)>W)break;
				LL tmp=dp[j-1]+(mx[j][i]-mi[j][i])+S(j,n);
				if(tmp<dp[i]){
					pos=j;
					dp[i]=tmp;
				}
			}
		}
		printf("%lld\n",dp[n]);
	}
}p60;
struct P100{
	struct YD_tree{
		struct node{
			int l,r;
			LL mi,lzy;
		}tree[M<<2];
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
		void up(int p){
			fa.mi=min(lson.mi,rson.mi);
		}
		void down(int p){
			if(fa.lzy){
				lson.mi+=fa.lzy;
				rson.mi+=fa.lzy;
				lson.lzy+=fa.lzy;
				rson.lzy+=fa.lzy;
				fa.lzy=0;
			}
		}
		void build(int l,int r,int p){
			fa.l=l;fa.r=r;fa.mi=0;
			if(l==r)return;
			int mid=(l+r)>>1;
			build(l,mid,p<<1);
			build(mid+1,r,p<<1|1);
		}
		void update(int l,int r,LL d,int p){
			if(fa.l==l&&fa.r==r){
				fa.lzy+=d;
				fa.mi+=d;
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
			if(fa.l==l&&fa.r==r)return fa.mi;
			down(p);
			int mid=(fa.l+fa.r)>>1;
			if(r<=mid)return query(l,r,p<<1);
			else if(l>mid)return query(l,r,p<<1|1);
			return min(query(l,mid,p<<1),query(mid+1,r,p<<1|1));
		}
	}Tr;
	struct Stk{int l,r;LL x;}stk1[M],stk2[M];
	int top1,top2;
	LL dp[M];
	void solve(){
		Tr.build(1,n,1);
		dp[1]=S(1,n);Tr.update(1,1,dp[0]+S(1,n),1);
		stk1[++top1]=(Stk){1,1,A[1]};stk2[++top2]=(Stk){1,1,A[1]};
		for(int i=2;i<=n;i++){
			while(top1>0&&A[i]>stk1[top1].x){
				int l=stk1[top1].l,r=stk1[top1].r;
				Tr.update(l,r,-stk1[top1].x,1);
				top1--;
			}
			int l=1;
			if(top1)l=stk1[top1].r+1;
			stk1[++top1]=(Stk){l,i,A[i]};
			Tr.update(l,i,A[i],1);
			while(top2>0&&A[i]<stk2[top2].x){
				int l=stk2[top2].l,r=stk2[top2].r;
				Tr.update(l,r,stk2[top2].x,1);
				top2--;
			}
			l=1;
			if(top2)l=stk2[top2].r+1;
			stk2[++top2]=(Stk){l,i,A[i]};
			Tr.update(l,i,-A[i],1);
			Tr.update(i,i,dp[i-1]+S(i,n),1);
			int st=lower_bound(sum,sum+i,sum[i]-W)-sum+1;
			dp[i]=Tr.query(st,i,1);
		}
		printf("%lld\n",dp[n]);
	}
}p100;
int main(){
	scanf("%d%d",&n,&W);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),sum[i]=sum[i-1]+A[i];
	p100.solve();
	return 0;
}
