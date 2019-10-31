#include<bits/stdc++.h>
#define M 300005
#define LL long long
using namespace std;
int n,m,A[M],B[M],bc;
int Lson[M*60],Rson[M*60],cnt[M*60][2],ver[M],tot;
LL sum[M*60][2];
void Insert(int od,int &rt,int x,int L,int R){
	rt=++tot;
	Lson[rt]=Lson[od];
	Rson[rt]=Rson[od];
	cnt[rt][B[x]&1]=cnt[od][B[x]&1]+1;
	sum[rt][B[x]&1]=sum[od][B[x]&1]+B[x];
	if(L==R)return;
	int mid=(L+R)>>1;
	if(x<=mid)Insert(Lson[od],Lson[rt],x,L,mid);
	else Insert(Rson[od],Rson[rt],x,mid+1,R);
}
int query_K(int l,int r,int L,int R,int K){
	if(L==R)return L;
	int ct=cnt[Lson[r]][0]+cnt[Lson[r]][1]-cnt[Lson[l]][0]-cnt[Lson[l]][1];
	int mid=(L+R)>>1;
	if(ct<=K)return query_K(Lson[l],Lson[r],L,mid,K);
	return query_K(Rson[l],Rson[r],mid+1,R,K-ct);
}
LL query_sum(int l,int r,int L,int R,int ql,int qr){
	if(L==ql&&R==qr)return sum[r][0]+sum[r][1]-sum[l][0]-sum[l][1];
	int mid=(L+R)>>1;
	if(qr<=mid)return query_sum(l,r,L,mid,ql,qr);
	else if(ql>mid)return query_sum(l,r,mid+1,R,ql,qr);
	return query_sum(l,r,L,mid,ql,mid)+query_sum(l,r,mid+1,R,mid+1,qr);
}
int query_mi(int l,int r,int L,int R,int ql,int qr){
	if(L==R)return L;
	int mid=(L+R)>>1;
	if(qr<=mid)return query_mi(l,r,L,mid-1,
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),B[i]=A[i];
	sort(B+1,B+n+1);
	bc=unique(B+1,B+m+1)-B-1;
	for(int i=1;i<=n;i++)A[i]=lower_bound(B+1,B+bc+1,A[i])-B;
	scanf("%d",&m);
	
	return 0;
}
