#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n,m,L,A[M];
LL sum[M],dp1[M][55],dp2[M][55],ans[M];
struct que{ int l,r,id; };
vector<que>wk[M<<2];
LL S(int l,int r){return sum[r]-sum[l-1];}
void Add(int l,int r,int p,que d){
	int mid=(l+r)>>1;
	if(d.l<=mid&&d.r>mid){
		wk[p].push_back(d);
		return;
	}
	if(d.r<=mid)Add(l,mid,p<<1,d);
	else Add(mid+1,r,p<<1|1,d);
}
void solve(int l,int r,int p){
	if(l==r){
		if(L==1&&A[l]>0)dp1[l][0]=dp2[l][0]=A[l];
		else dp1[l][0]=dp2[l][0]=0;
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid,p<<1);solve(mid+1,r,p<<1|1);
	for(int i=0;i<wk[p].size();i++){
		int ql=wk[p][i].l,qr=wk[p][i].r,id=wk[p][i].id;
		ans[id]=max(ans[id],dp2[ql][0]+dp1[qr][0]);
		for(int d=1;d<L;d++){
			if(ql+d-1<=mid&&mid+L-d<=qr){
				ans[id]=max(ans[id],dp2[ql][d]+dp1[qr][L-d]+S(mid-d+1,mid-d+L));
			}
		}
	}
	for(int d=0;d<L;d++){
		for(int i=mid+1;i<=r;i++){
			if(i-L==l-1&&d==0)dp1[i][d]=max(dp1[i][d],S(i-L+1,i));
			else {
				if(i-1>=l+d-1)dp1[i][d]=dp1[i-1][d];
				if(i-L>=l+d-1)dp1[i][d]=max(dp1[i][d],dp1[i-L][d]+S(i-L+1,i));
			}
		}
	}
	for(int d=0;d<L;d++){
		for(int i=mid;i>=l;i--){
			if(i+L==r+1&&d==0)dp2[i][d]=max(dp2[i][d],S(i,i+L-1));
			else {
				if(i+1<=r-d+1)dp2[i][d]=dp2[i+1][d];
				if(i+L<=r-d+1)dp2[i][d]=max(dp2[i][d],dp2[i+L][d]+S(i,i+L-1));
			}
		}
	}
}
int main(){
//	freopen("carritch.in","r",stdin);
//	freopen("carritch.out","w",stdout);
	scanf("%d%d",&n,&L);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),sum[i]=sum[i-1]+A[i];
	scanf("%d",&m);
	for(int i=1,l,r;i<=m;i++){
		scanf("%d%d",&l,&r);
		que tmp=(que){l,r,i};
		if(l==r){
			if(L==1&&A[l]>0)ans[i]=A[l];
			else ans[i]=0;
		}
		else Add(1,n,1,tmp);
	}
	solve(1,n,1);
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
