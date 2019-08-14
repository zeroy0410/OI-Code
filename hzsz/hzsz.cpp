#include<bits/stdc++.h>
#define M 20005
using namespace std;
int s[M];
int rk[M],sa[M],H[M];
int cnt1[M],t1[M],cnt2[M],t2[M];
int tmp[M];
struct node{
	int x,id;
	bool operator <(const node &_)const{
		return x<_.x||(x==_.x&&id<_.id);
	}
}A[M];
//sa[i]就表示排名为i的后缀的起始位置的下标
//rk[i]就表示起始位置的下标为i的后缀的排名
void Build(int *s,int n){
	for(int i=1;i<=n;i++)A[i]=(node){s[i],i};
	sort(A+1,A+n+1);
	for(int i=1;i<=n;i++)sa[i]=A[i].id;
	rk[sa[1]]=1;
	for(int i=2;i<=n;i++){//为第一个字母排序
		rk[sa[i]]=rk[sa[i-1]];
		if(s[sa[i]]!=s[sa[i-1]])rk[sa[i]]++;
	}
	for(int l=1;rk[sa[n]]<n;l<<=1){
		for(int i=0;i<=n;i++)cnt1[i]=cnt2[i]=0;
		for(int i=1;i<=n;i++){
			cnt1[t1[i]=rk[i]]++;
			cnt2[t2[i]=(l+i<=n)?rk[i+l]:0]++;
		}
		for(int i=1;i<=n;i++)cnt1[i]+=cnt1[i-1],cnt2[i]+=cnt2[i-1];
		for(int i=n;i;i--)tmp[cnt2[t2[i]]--]=i;
		for(int i=n;i;i--)sa[cnt1[t1[tmp[i]]]--]=tmp[i];
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
bool check(int x,int n){
	for(int i=1,mn=2e9,mx=0;i<=n;i++){
		if(H[i]<x)mn=mx=sa[i];
		else{
			mn=min(mn,sa[i]);
			mx=max(mx,sa[i]);
			if(mx-mn>=x)return 1;
		}
	}return 0;
}
int n;
int main(){
	while(scanf("%d",&n),n){
		for(int i=1;i<=n;i++)scanf("%d",&s[i]);
		if(n<10){puts("0");continue;}
		for(int i=1;i<n;i++)s[i]=s[i+1]-s[i];
		n--;
		Build(s,n);
		int L=4,R=n,res=-1;
		while(L<=R){
			int mid=(L+R)>>1;
			if(check(mid,n))L=mid+1,res=mid;
			else R=mid-1;
		}printf("%d\n",++res);
	}
	return 0;
}
