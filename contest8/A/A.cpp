#include<bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline")
#define M 600005
using namespace std;
struct node{
	int x,id;
	bool operator < (const node& res)const{
		if(x!=res.x)return x<res.x;
		return id<res.id;
	}
}A[M];
int rk[M],sa[M],t1[M],t2[M],cnt1[M],cnt2[M],tmp[M],H[M];
void Init_SA(char *s,int n){
	for(int i=1;i<=n;i++)A[i]=(node){s[i],i};
	sort(A+1,A+n+1);
	for(int i=1;i<=n;i++)sa[i]=A[i].id;
	rk[sa[1]]=1;
	for(int i=2;i<=n;i++){
		rk[sa[i]]=rk[sa[i-1]];
		if(s[sa[i]]!=s[sa[i-1]])rk[sa[i]]++;
	}
	for(int l=1;rk[sa[n]]<n;l<<=1){
		for(int i=0;i<=n;i++)cnt1[i]=cnt2[i]=0;
		for(int i=1;i<=n;i++){
			cnt1[t1[i]=rk[i]]++;
			cnt2[t2[i]=(l+i<=n?rk[l+i]:0)]++;
		}
		for(int i=1;i<=n;i++)cnt1[i]+=cnt1[i-1],cnt2[i]+=cnt2[i-1];
		for(int i=n;i>=1;i--)tmp[cnt2[t2[i]]--]=i;
		for(int i=n;i>=1;i--)sa[cnt1[t1[tmp[i]]]--]=tmp[i];
		rk[sa[1]]=1;
		for(int i=2;i<=n;i++){
			rk[sa[i]]=rk[sa[i-1]];
			if(t1[sa[i]]!=t1[sa[i-1]]||t2[sa[i]]!=t2[sa[i-1]])rk[sa[i]]++;
		}
	}
	for(int i=1,j=0;i<=n;i++){
		j-=j>0;
		while(s[i+j]==s[sa[rk[i]-1]+j])j++;
		H[rk[i]]=j;
	}
}
struct ST_table{
	int mi[M][21],lg[M];
	void Init_RMQ(int n){
		for(int i=1;i<=n;i++)mi[i][0]=H[i];
		lg[1]=0;
		for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
		for(int j=1;(1<<j)<=n;j++)
			for(int i=1;i+(1<<j)-1<=n;i++)
				mi[i][j]=min(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
	}
	int query(int l,int r){
		int k=lg[r-l+1];
		return min(mi[l][k],mi[r-(1<<k)+1][k]);
	}
}st;
int n,len;
int LCP(int l,int r){
	if(l==r)return n-l+1;
	l=rk[l],r=rk[r];
	if(l>r)swap(l,r);
	return st.query(l+1,r);
}
struct YD_tree{
	struct YD{
		int l,r,mi;
	}tree[M<<2];
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
	void down(int p){
		lson.mi=min(lson.mi,fa.mi);
		rson.mi=min(rson.mi,fa.mi);
	}
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;fa.mi=1e9;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
	}
	void update(int l,int r,int d,int p){
		if(l==fa.l&&r==fa.r){
			fa.mi=min(fa.mi,d);
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
	}
	int query(int x,int p){
		if(fa.l==x&&fa.r==x)return fa.mi;
		down(p);
		int mid=(fa.l+fa.r)>>1;
		if(x<=mid)return query(x,p<<1);
		return query(x,p<<1|1);
	}
}Tr;
char S[M];
int calc(int L,int R){
	int l=1,r=rk[L],LL=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(LCP(sa[mid],L)>=R-L+1){
			LL=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	l=rk[L],r=n;
	int RR=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(LCP(sa[mid],L)>=R-L+1){
			RR=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return RR-LL+1;
}		
int main(){
	freopen("sub-5drome0.in","r",stdin);
	freopen("palindrome.out","w",stdout);
	scanf("%s",S+1);
	n=strlen(S+1);
	S[n+1]='$';
	for(int i=n+2;i<=2*n+1;i++)S[i]=S[2*n-i+2];
	len=n;n=n*2+1;
	Init_SA(S,n);
	st.Init_RMQ(n);
	long long ans=0;
	Tr.build(1,len,1);
	for(int i=1;i<=len;i++){
		int lcp=LCP(i,n-i+1);
		Tr.update(i,i+lcp-1,i,1);
	}
	for(int i=1;i<=len;i++){
		int cur=Tr.query(i,1);
		int l=2*cur-i;
		int ct=calc(l,i);
		ans=max(ans,1LL*ct*(i-l+1));
	}
	Tr.build(1,len,1);
	for(int i=2;i<=len;i++){
		int lcp=LCP(i,n-i+2);
		if(lcp==0)continue;
		Tr.update(i,i+lcp-1,i,1);
	}
	for(int i=1;i<=len;i++){
		int cur=Tr.query(i,1);
		int l=2*cur-i-1;
		if(l>i)continue;
		int ct=calc(l,i);
		ans=max(ans,1LL*ct*(i-l+1));
	}
	printf("%lld\n",ans>>1);
	return 0;
}
