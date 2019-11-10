#include <cstdio>
#define ll long long
const int N=1e6+10;
const int inf=0x7fffffff;
const ll mod=1e9+7;
int n,a[N],b[N],mi=inf,id,s[N],tot;
ll dp[N],ans,f[N],sum;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",b+i);
		if(b[i]<mi)
			mi=b[i],id=i;
	}
	int cnt=0;
	while(cnt<n){
		a[++cnt]=b[id++];
		id==n+1&&(id=1);
	}
	f[0]=1,f[1]=1-a[1],sum=a[1],dp[1]=a[1],s[++tot]=1;
	for(int las,i=2;i<=n;i++){
		while(tot&&a[s[tot]]>=a[i])
			(sum-=a[s[tot]]*(f[s[tot]-1]-(tot-1?f[s[tot-1]-1]:0)))%=mod,--tot;
		(sum+=a[i]*(f[i-1]-(tot?f[s[tot]-1]:0)))%=mod;
		dp[i]=sum*(i&1?1:-1);
		(f[i]=f[i-1]+dp[i]*(i&1?-1:1))%=mod;
		s[++tot]=i;
	}
	for(int i=n;i>1;i--)
		(ans+=dp[i]*(n-i&1?-1:1))%=mod;
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}
