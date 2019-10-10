#include<bits/stdc++.h>
#define M 50005
#define LL long long
using namespace std;
const int mod=1e9+7;
const LL inf=1e18+1;
int n,m,q,T;
char S[M],op[M];
LL dp[M][25];
int nxt[25][15];
void Add(LL &x,LL y){
	x+=y;
	if(x>=inf)x=inf;
}
bool cmp(int x,int y){
	while(x)if(op[x--]!=op[y--])return 0;
	return 1;
}
void Init(){
	for(int i=0;i<=m;i++){
		for(int j=0;j<=9;j++){
			if(i==m)nxt[i][j]=m;
			else if(i<m&&j==op[i+1])nxt[i][j]=i+1;
			else {
				bool fl=0;
				for(int k=i;k>=1;k--){
					if(j==op[k]&&cmp(k-1,i)){
						nxt[i][j]=k;
						fl=1;
						break;
					}
				}
				if(!fl)nxt[i][j]=0;
			}
		}
	}
}
struct P50{
	void solve(){
		dp[n+1][m]=1;
		for(int i=n;i>=1;i--){
			for(int j=0;j<=m;j++)
				for(int k=(i==1);k<=9;k++)
					if(S[i]=='?'||S[i]==k+'0')
						Add(dp[i][j],dp[i+1][nxt[j][k]]);
		}
		while(q--){
			LL x,res=0,ans=0;
			scanf("%lld",&x);
			for(int i=1;i<=n;i++){
				int las=-1;
				for(int j=(i==1);j<=9;j++)
					if(S[i]=='?'||S[i]==j+'0'){
						if(x>dp[i+1][nxt[res][j]])x-=dp[i+1][nxt[res][j]];
						else {
							las=j;
							break;
						}
					}
					if(las==-1){ans=-1;break;}
					ans=(ans*10+las)%mod;
					res=nxt[res][las];
			}
			printf("%lld\n",ans);
		}	
	}
}p50;
struct P100{
	void solve(){

	}
}p100;
int main(){
	scanf("%d",&T);
	while(T--){
		memset(dp,0,sizeof(dp));
		scanf("%d%d",&n,&q);
		scanf("%s",op+1);m=strlen(op+1);
		for(int i=1;i<=m;i++)op[i]-='0';
		Init();
		scanf("%s",S+1);
		p50.solve();
	}
	return 0;
}
