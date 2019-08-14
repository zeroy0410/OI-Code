#include<stdio.h>
#include<algorithm>
#define M 20005
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;
struct node{
	int x,id;
	bool operator < (const node& res) const{
		if(x!=res.x)return x<res.x;
		return id<res.id;
	}
}A[M];
int sa[M],rk[M],H[M],cnt1[M],cnt2[M],tmp[M];
int t1[M],t2[M];
//sa[i] 表示排名为i的后缀的起始下标
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
		for(int i=0;i<=n;i++)cnt1[i]=cnt2[i]=0;
		for(int i=1;i<=n;i++)cnt1[t1[i]=rk[i]]++,cnt2[t2[i]=(l+i<=n)?rk[i+l]:0]++;
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
bool check(int x,int n){
	for(int i=1,mi=1e9,mx=0;i<=n;i++){
		if(H[i]<x)mi=mx=sa[i];
		else {
			mi=min(mi,sa[i]);
			mx=max(mx,sa[i]);
			if(mx-mi>=x)return 1;
		}
	}
	return 0;
}
int n,S[M];
int main(){
	while(scanf("%d",&n)&&n){
		for(int i=1;i<=n;i++)scanf("%d",&S[i]);
		if(n<10){puts("0");continue;}
		for(int i=1;i<n;i++)S[i]=S[i+1]-S[i];
		n--;
		Init(S,n);
		int l=4,r=n,res=-1;	
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid,n)){res=mid;l=mid+1;}
			else r=mid-1;
		}
		printf("%d\n",res+1);
	}
}
