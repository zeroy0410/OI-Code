#include<bits/stdc++.h>
#define M 10000005
#define LL long long
using namespace std;
const int mod=1e9+7;
char S[M],T[M];
int n,m,f[M];
struct P20{
	LL calc(int l,int r){
		LL res=0;
		for(int len=0;len<=r-l+1;len++){
			bool fl=1;
			int j=0;
			for(int i=l+len;i<=r;i++,j++){
				if(S[i]!=T[j]){
					fl=0;
					break;
				}
			}
			if(!fl)continue;
			for(int i=l;i<l+len;i++,j++){
				if(S[i]!=T[j]){
					fl=0;
					break;
				}
			}
			if(!fl)continue;
			res++;
		}
		return res;
	}
	void solve(){
		LL ans=0;
		for(int i=0;i<n;i++){
			int ed=i+m*2-1;
			if(ed>=n)break;
			ans+=calc(i,i+m-1)*calc(i+m,i+2*m-1)%mod;
			ans%=mod;
		}
		printf("%lld\n",ans);
	}
}p20;
struct P100{
	void Init(char *s,int l){
		f[0]=f[1]=0;
		for(int i=1;i<l;i++){
			int j=f[i];
			while(j&&s[i]!=s[j])j=f[j];
			if(s[i]==s[j])j++;
			f[i+1]=j;
		}
		for(int i=m+1;i<=l;i++)
			if(f[i]>=m)cnt[i-m+1]++;
		for(int i=1;i<=l;i++)cnt[i]+=cnt[i-1];
	}
	void solve(){
		for(int i=0;i<m;i++)T[i+m]=T[i];
		Init(T,m<<1);

	}
}p100;
int main(){
	scanf("%s%s",S,T);
	n=strlen(S);m=strlen(T);

	return 0;
}
