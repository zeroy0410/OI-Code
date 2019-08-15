#include<bits/stdc++.h>
using namespace std;
const int mod=1e9;
bool mm1;
int n,m,K;
struct P50{
	int dp[2][5005][1<<4];
	int mp[5005][5005];
	int dxy[4][2]={0,0,-1,0,0,-1,-1,-1};
	void Add(int& x,int y){
		x+=y;
		if(x>=mod)x-=mod;
	}
	int ask(int x,int y,int k){
		int res=0;
		for(int k=0;k<1<<4;k++){
			for(int r=0;r<4;r++){
				int nx=2+dxy[r][0];
				int ny=i+dxy[r][1];
				if((k&1<<r)&&mp[nx][ny]==0){return -1;}
				if(!(k&1<<r)&&mp[nx][ny]==1){return -1;}
				
			}
			if(fl)dp[cur][i][k]=1;
		}
	}
	void solve(){
		memset(mp,-1,sizeof(mp));
		memset(dp,0,sizeof(dp));
		for(int i=1,a,b,c;i<=K;i++){
			scanf("%d%d%d",&a,&b,&c);
			mp[a][b]=c;
		}
		int cur=0;
		for(int i=2;i<=m;i++){
			
		}
		for(int i=3;i<=n;i++){
			cur=!cur;
			memset(dp[cur],0,sizeof(dp[cur]));
			for(int k=0;k<1<<4;k++){

		}
	}
}p50;
bool mm2;
int main(){
//	freopen("color.in","r",stdin);
//	freopen("color.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	
	return 0;
}
