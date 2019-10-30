#include<bits/stdc++.h>
#define M 300005
#define LL long long
using namespace std;
int n,m,A[M],B[M],bc;
int Lson[M*60],Rson[M*60],ver[M],tot;
struct node{
	int cnt[2];
	LL sum[2];
	int mx[2],mi[2];
	node(){
		cnt[0]=cnt[1]=sum[0]=sum[1]=0;
		mx[0]=mx[1]=-1e9;
		mi[0]=mi[1]=1e9;
	}
	node operator + (const node res){
		node ans;
		ans.cnt[0]=cnt[0]+res.cnt[0];
		ans.cnt[1]=cnt[1]+res.cnt[1];
		ans.sum[0]=sum[0]+res.sum[0];
		ans.sum[1]=sum[1]+res.sum[1];
		ans.mx[0]=max(mx[0],res.mx[0]);
		ans.mx[1]=max(mx[1],res.mx[1]);
		ans.mi[0]=min(mi[0],res.mi[0]);
		ans.mi[1]=min(mi[1],res.mi[1]);
		return ans;
	}
	node operator - (const node res){
		node ans;
		ans.cnt[0]=cnt[0]-res.cnt[0];
		ans.cnt[1]=cnt[1]-res.cnt[1];
		ans.sum[0]=sum[0]-res.sum[0];
		ans.sum[1]=sum[1]-res.sum[1];
		return ans;
	}
}Tr[M*60];
void Insert(int od,int &rt,int x,int L,int R){
	rt=++tot;
	Lson[rt]=Lson[od];
	Rson[rt]=Rson[od];
	Tr[rt].cnt[B[x]&1]=Tr[od].cnt[B[x]&1]+1;
	Tr[rt].sum[B[x]&1]=Tr[od].sum[B[x]&1]+B[x];
	if(L==R)return;
	int mid=(L+R)>>1;
	if(x<=mid)Insert(Lson[od],Lson[rt],x,L,mid);
	else Insert(Rson[od],Rson[rt],x,mid+1,R);
}
int query(int l,int r,int L,int R,int K){
	if(L==R)return l;
	node tmp=Tr[Rson[r]]-Tr[Rson[l]];
	int mid=(L+R)>>1;
	if(tmp.cnt[0]+tmp.cnt[1]<=K)return query(Rson[l],Rson[r],mid+1,R,K);
	return query(Lson[l],Lson[r],L,mid,K-tmp.cnt[0]-tmp.cnt[1]);
}
node Query(int 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),B[i]=A[i];
	sort(B+1,B+n+1);
	bc=unique(B+1,B+m+1)-B-1;
	for(int i=1;i<=n;i++)A[i]=lower_bound(B+1,B+bc+1,A[i])-B;
	scanf("%d",&m);
	
	return 0;
}
