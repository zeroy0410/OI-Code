#include<cstdio>
#include<string.h>
#include<algorithm>
#define M 100005
using namespace std;
int rk[M<<1],sa[M<<1],t1[M<<1],t2[M<<1],cnt1[M<<1],cnt2[M<<1],tmp[M<<1],H[M<<1];
void Init_SA(char *s,int n){
	for(int i=0;i<=1000;i++)cnt1[i]=0;
	for(int i=1;i<=n;i++)cnt1[s[i]]++;
	for(int i=1;i<=1000;i++)cnt1[i]+=cnt1[i-1];
	for(int i=n;i>=1;i--)sa[cnt1[s[i]]--]=i;
	rk[sa[1]]=1;
	for(int i=2;i<=n;i++){
		rk[sa[i]]=rk[sa[i-1]];
		if(s[sa[i]]!=s[sa[i-1]])rk[sa[i]]++;
	}
	for(int l=1;rk[sa[n]]<n;l<<=1){
		for(int i=0;i<=n;i++)cnt1[i]=cnt2[i]=0;
		for(int i=1;i<=n;i++){
			cnt1[t1[i]=rk[i]]++;
			cnt2[t2[i]=(i+l<=n?rk[i+l]:0)]++;
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
char S[M<<1];
int main(){
	scanf("%s",S+1);
	int n=strlen(S+1);
	S[++n]='#';
	int fj=n;
	scanf("%s",S+n+1);
	n=strlen(S+1);
	Init_SA(S,n);
	int ans=0;
	for(int i=2;i<=n;i++){
		if(sa[i]<fj&&sa[i-1]>fj||sa[i]>fj&&sa[i-1]<fj)
			ans=max(ans,H[i]);
	}
	printf("%d\n",ans);
	return 0;
}
