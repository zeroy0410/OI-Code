#include<stdio.h>
#define LL long long
#define M 200005
const int mod=1e9+7;
int n,m,b;
char S[M];
LL Pow[M],Sum[M];
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
struct Pbl{
	void solve(){
		while(m--){
			int op,l,r;
			char ss[5];
			scanf("%d",&op);
			if(op==0){
				scanf("%d%d",&l,&r);
				LL ans=0;
				for(int i=l;i<=r;i++)
					ans=(ans+Sum[r-i]*S[i]*(i-l+1)%mod)%mod;
				LL tot=r-l+1;
				tot=(tot*(tot-1)/2+tot)%mod;
				ans=ans*qkpow(tot,mod-2)%mod;
				printf("%lld\n",ans);
			}
			else {
				scanf("%d%s",&l,ss);
				S[l]=ss[0]-'a'+1;
			}
		}
	}
}pbl;
int main(){
	freopen("letter.in","r",stdin);
	freopen("letter.out","w",stdout);
	scanf("%d%d%d",&n,&m,&b);
	Pow[0]=1;
	for(int i=1;i<=n;i++)Pow[i]=Pow[i-1]*b%mod;
	Sum[0]=1;
	for(int i=1;i<=n;i++)Sum[i]=(Sum[i-1]+Pow[i])%mod;
	scanf("%s",S+1);
	for(int i=1;i<=n;i++)S[i]=S[i]-'a'+1;
	pbl.solve();
	return 0;
}
