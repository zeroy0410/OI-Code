#include<bits/stdc++.h>
#define LL long long
const int mod=1e9+7;
using namespace std;
int n,m;
int st[20],ed[20];
void Add(int &x,int y){
	x+=y;
	if(x>=mod)x-=mod;
	if(x<0)x+=mod;
}
struct P60{
	int dp[1<<10][1<<10];
	int cnt[1<<10];
	int Pow[15];
	void Print(int x){
		for(int i=0;i<n;i++)
			if(x&1<<i)printf("1");
			else printf("0");
		puts("");
	}
	void Init(){
		for(int i=1;i<1<<n;i++)cnt[i]=cnt[i>>1]+(i&1);
		for(int i=1;i<1<<n;i++)dp[i][i]=1;
		Pow[0]=1;
		for(int i=1;i<=n;i++)Pow[i]=1LL*Pow[i-1]*2%mod;
	}
	void solve(){
		Init();
		int base=(1<<n)-1;
		for(int i=1;i<base;i++){//diandeshiyongqingkuang
			for(int j=i;j;j=(j-1)&i){//dangqiancengyijingyonglezhemeduodian
				for(int k=(base^i);k;k=(k-1)&(base^i)){//qianyicengyaoyongzhexiedian
					LL tmp=1;
					for(int r=0;r<n;r++)
						if(k&1<<r){
							tmp=tmp*(Pow[cnt[j&st[r]]]-1)%mod;
							tmp=tmp*Pow[cnt[(i^j)&st[r]]]%mod;
						}
					Add(dp[i|k][k],tmp*dp[i][j]%mod);
				}
			}
		}
		int ans=0;
		for(int i=1;i<=base;i++)
			Add(ans,dp[base][i]);
		printf("%d\n",ans);
	}
}p60;
struct P100{
	int dp[1<<17],tmp[1<<17],S[1<<17];
	int cnt[1<<17];
	int Pow[505];
	void Init(){
		cnt[0]=-1;
		for(int i=1;i<1<<n;i++)cnt[i]=-cnt[i&(i-1)];
		Pow[0]=1;
		for(int i=1;i<=n*n;i++)Pow[i]=1LL*Pow[i-1]*2%mod;
	}
	void solve(){
		Init();
		int base=(1<<n)-1;
		dp[0]=1;
		for(int i=0;i<base;i++){
			S[0]=0;
			for(int j=0;j<n;j++)tmp[1<<j]=0;
			for(int j=0;j<n;j++){if(i&1<<j){for(int k=0;k<n;k++){if(st[j]&1<<k)tmp[1<<k]++;}}}
			int to=(base^i);
			for(int T=(to&(to-1));;T=(T-1)&to){
				int ne=(T^to);
				S[ne]=S[ne&(ne-1)]+tmp[ne&(-ne)];
				Add(dp[i|ne],1LL*dp[i]*Pow[S[ne]]%mod*cnt[ne]%mod);
				if(!T)break;
			}
		}
		printf("%d\n",dp[base]);
	}
}p100;
int main(){
//	freopen("obelisk.in","r",stdin);
//	freopen("obelisk.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);a--;b--;
		st[a]|=1<<b;
	}
	p100.solve();
	return 0;
}
