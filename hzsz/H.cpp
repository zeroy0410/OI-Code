#include<cstdio>
#include<iostream>
#include<string.h>
#define M 100005
#define LL long long
using namespace std;
int K;
int rk[M<<1],sa[M<<1],t1[M<<1],t2[M<<1],cnt1[M<<1],cnt2[M<<1],tmp[M<<1],H[M<<1];
void Init_SA(char *s,int n){
	for(int i=0;i<=1000;i++)cnt1[i]=0;
	for(int i=1;i<=n;i++)cnt1[(int)s[i]]++;
	for(int i=1;i<=1000;i++)cnt1[i]+=cnt1[i-1];
	for(int i=n;i>=1;i--)sa[cnt1[(int)s[i]]--]=i;
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
int stk[M<<1],na[M<<1],nb[M<<1],top;
int main(){
	while(scanf("%d",&K)&&K){
		scanf("%s",S+1);
		int n=strlen(S+1);
		S[++n]='#';
		int fj=n;
		scanf("%s",S+n+1);
		n=strlen(S+1);
		Init_SA(S,n);
		for(int i=2;i<=n;i++)H[i]=max(0,H[i]-K+1);
        LL ans=0,w1=0,w2=0;top=0;
        for(int i=2;i<=n;i++){
            stk[++top]=H[i];
            if(sa[i-1]<fj)na[top]=1,nb[top]=0,w1+=H[i];
            else na[top]=0,nb[top]=1,w2+=H[i];
            while((top>1)&&stk[top]<=stk[top-1]){
                w1-=na[top-1]*(stk[top-1]-stk[top]);
                w2-=nb[top-1]*(stk[top-1]-stk[top]);
                na[top-1]+=na[top]; nb[top-1]+=nb[top];
                stk[top-1]=stk[top--];
            }if(sa[i]<fj)ans+=w2;
            else ans+=w1;
        }printf("%lld\n",ans); 
	}
	return 0;
}
