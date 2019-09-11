#include<cstdio>
#include<string.h>
#include<iostream>
#define M 1000005
using namespace std;
int rk[M<<1],sa[M<<1],t1[M<<1],t2[M<<1],cnt1[M<<1],cnt2[M<<1],tmp[M<<1],H[M<<1],l;
void Init_SA(int *s,int n){ 
	for(int i=0;i<=100000;i++)cnt1[i]=0;
	for(int i=1;i<=n;i++)cnt1[(int)s[i]]++;
	for(int i=1;i<=100000;i++)cnt1[i]+=cnt1[i-1];
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
char S[M];
int mp[M],st[M],tp[M],n,pos[M];
bool mark[110];
bool check(int mid){
	memset(mark,0,sizeof(mark));
	int num=0,ans=0;
	for(int i=1;i<=l;i++){
		if(H[i]>=mid){
			for(int j=1;j<=n;j++){
				if(sa[i]>st[j-1]&&sa[i]<st[j])ans+=(mark[j]?0:1),mark[j]=1;
				if(sa[i-1]>st[j-1]&&sa[i-1]<st[j])ans+=(mark[j]?0:1),mark[j]=1;
			}
		}
		else {
			if(ans>n/2)pos[++num]=sa[i-1];
			ans=0;
			memset(mark,0,sizeof(mark));
		}
	}
	if(ans>n/2)pos[++num]=sa[n];
	if(num){pos[0]=num;return 1;}
	return 0;
}
int main(){
//	freopen("C.1.dat","r",stdin);
//	freopen("data.out","w",stdout);
	bool flag=0;
	while(scanf("%d",&n)&&n){
		if(flag)printf("\n");flag=1;
		l=0;
		for(int i=1;i<=n;i++){
			scanf("%s",S+1);
			int ll=strlen(S+1);
			for(int j=1;j<=ll;j++){
				tp[++l]=S[j];
				mp[l]=st[i];
			}
			tp[++l]=300+i;
			st[i]=l;
		}
		Init_SA(tp,l);
		int L=1,R=l,ans=-1;
		while(L<=R){
			int mid=(L+R)>>1;
			if(check(mid)){
				ans=mid;
				L=mid+1;
			}
			else R=mid-1;
		}
		if(ans==-1)printf("?\n");
		else {
			for(int i=1;i<=pos[0];i++){
				for(int j=pos[i];j<pos[i]+L-1;j++)printf("%c",tp[j]);
				printf("\n");
			}
		}
	}
	return 0;
}
