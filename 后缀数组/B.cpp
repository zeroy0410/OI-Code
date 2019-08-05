#include<cstdio>
#include<algorithm>
#include<string.h>
#define M 20005
using namespace std;
struct node{
	int x,id;
	bool operator < (const node& res) const{
		if(x!=res.x)return x<res.x;
		return id<res.id;
	}
}A[M];
int H[M],sa[M],rk[M],t1[M],t2[M],cnt1[M*50],cnt2[M*50],tmp[M];
void Init(int *s,int n){
	for(int i=1;i<=n;i++)A[i]=(node){s[i],i};
	sort(A+1,A+n+1);
	for(int i=1;i<=n;i++)sa[i]=A[i].id;
	rk[sa[1]]=1;
	for(int i=2;i<=n;i++){
		rk[sa[i]]=rk[sa[i-1]];
		if(s[sa[i]]!=s[sa[i-1]])rk[sa[i]]++;
	}
	for(int l=1;rk[sa[n]]<n;l<<=1){
		for(int i=0;i<M*50;i++)cnt1[i]=cnt2[i]=0;
		for(int i=1;i<=n;i++){
			cnt1[t1[i]=rk[i]]++;
			cnt2[t2[i]=(i+l<=n)?rk[i+l]:0]++;
		}
		for(int i=0;i<M*50;i++)cnt1[i]+=cnt1[i-1],cnt2[i]+=cnt2[i-1];
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
int K;
bool check(int x,int n){
	int res=0;
	for(int i=1;i<=n;i++){
		if(H[i]>=x)res++;
		else res=1;
		if(res>=K)return 1;
	}
	return 0;
}
int n,s[M];
int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++)scanf("%d",&s[i]);
	Init(s,n);
	int l=0,r=n,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid,n)){ans=mid;l=mid+1;}
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
