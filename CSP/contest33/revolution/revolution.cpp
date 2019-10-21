#include<bits/stdc++.h>
#define M 2005
using namespace std;
const int mod=998244353;
int n,p[M][5],w[5][5];
struct P10{
	int ans[M];
	void solve(){
		for(int i=0;i<1<<n;i++){
			int res=1,c1=0,c2=0;
			for(int j=0;j<n;j++){
				if(i&1<<j){
					c1++;
					res=1LL*res*p[j+1][1]%mod;
				}
				else {
					c2++;
					res=1LL*res*p[j+1][2]%mod;
				}
			}
			int id=1;
			if(c2>c1)swap(c1,c2),id=2;
			if(c1>n/2){
				for(int j=0;j<n;j++){
					int pc=0;
					if(i&1<<j)
						pc=w[id][1];
					else 
						pc=w[id][2];
					ans[j]=(ans[j]+1LL*pc*res%mod)%mod;
				}
			}
		}
		for(int i=0;i<n;i++)
			printf("%d\n",ans[i]);
	}
}p10;
int main(){
	freopen("revolution.in","r",stdin);
	freopen("revolution.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=4;j++)
			scanf("%d",&p[i][j]);
	}
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			scanf("%d",&w[i][j]);
	if(n<=10)p10.solve();
	return 0;
}
