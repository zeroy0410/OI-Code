#include<bits/stdc++.h>
#define M 3000005
#define LL long long
using namespace std;
const int mod=1e9+7;
int n;
char S[M];
struct Bignum{
	LL a[1005];
	int len;
	Bignum(){
		memset(a,0,sizeof(a));
		len=1;
	}
	Bignum operator * (const LL& res){
		Bignum ans;
		LL J=0;
		for(int i=0;i<len;i++){
			ans.a[i]+=a[i]*res+J;
			J=ans.a[i]/10;
			ans.a[i]%=10;
		}
		int w=len;
		for(;J;J/=10)ans.a[w++]=J%10;
		ans.len=w;
		return ans;
	}
	void Print(){
		printf("%lld",a[len-1]);
		for(int i=len-2;i>=0;i--)
			printf("%lld",a[i]);
		puts("");
	}
};
struct P1{
	int pr[M],pc;
	bool mark[M];
	void Init(){
		for(int i=2;i<=n;i++){
			if(!mark[i])pr[++pc]=i;
			for(int j=i+i;j<=n;j+=i)
				mark[j]=1;
		}
	}
	void solve(){
		Init();
		LL ans=1;
		for(int i=1;i<=pc;i++){
			int tmp=n;
			LL res=0;
			while(tmp>1){
				res+=tmp/pr[i];
				tmp/=pr[i];
			}
			ans=ans*(2*res%mod+1)%mod;
		}
		printf("%lld\n",ans);
	}
}p1;
struct P2{
	int pr[M],pc;
	bool mark[M];
	void Init(){
		for(int i=2;i<=n;i++){
			if(!mark[i])pr[++pc]=i;
			for(int j=i+i;j<=n;j+=i)
				mark[j]=1;
		}
	}
	void solve(){
		Init();
		Bignum ans;ans.a[0]=1;
		for(int i=1;i<=pc;i++){
			int tmp=n;
			LL res=0;
			while(tmp>1){
				res+=tmp/pr[i];
				tmp/=pr[i];
			}
			ans=ans*(2*res+1);
		}
		ans.Print();
	}
}p2;
int main(){
//	freopen("equal.in","r",stdin);
//	freopen("equal.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",S+1);
	int fl=strlen(S+1);
	if(fl<20)p1.solve();
	else p2.solve();
	return 0;
}
