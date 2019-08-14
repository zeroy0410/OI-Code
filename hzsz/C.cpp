#include<bits/stdc++.h>
#define M 10005
using namespace std;
struct node{
	int x,id;
	bool operator < (const node& res) const{
		if(x!=res.x)return x<res.x;
		return id<res.id;
	}
}A[M];
int rk[M],sa[M],cnt1[M],cnt2[M],H[M],tmp[M],t1[M],t2[M],T;
void Init(char *s,int n){
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
int n;
char S[M];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s",S+1);
		n=strlen(S+1);
		Init(S,n);
		int sum=n*(n+1)/2;
		for(int i=1;i<=n;i++)sum-=H[i];
		printf("%d\n",sum);
	}
	return 0;
}
