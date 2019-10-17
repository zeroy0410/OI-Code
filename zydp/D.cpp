#include<bits/stdc++.h>
#define M 100005
using namespace std;
const int mod=1e9+1;
int n;
int sz[M];
int dp[15][1<<12];
void Add(int &x,int y){
	x+=y;
	if(x>=mod)x-=mod;
}
vector<int>ca[1<<12];
vector<int>hf;
void Init(){
	for(int i=0;i<1<<12;i++)
		if(!(i&(i>>1)))
			hf.push_back(i);
	for(int i=0;i<hf.size();i++){
		int x=hf[i];
		for(int j=0;j<hf.size();j++){
			int y=hf[j];
			if(x&y)continue;
			ca[x].push_back(y);
		}
	}
}
int main(){
	Init();
	scanf("%d",&n);
	int r,ct;
	for(r=1,ct=1;;r=r*2,ct++){
		if(r>n)break;
		sz[ct]=1;
		int x=r;
		while(x<=n){
			x=x*3;
			sz[ct]++;
		}
	}
	ct--;
	for(int i=0;i<1<<sz[1];i++)
		if(!(i&(i>>1)))dp[1][i]=1;
	for(int i=1;i<=ct-1;i++){
		for(int j=0;j<hf.size();j++){
			int x=hf[j];
			if(x>=(1<<sz[i]))break;
			for(int k=0;k<ca[x].size();k++){
				if(ca[x][k]>=(1<<sz[i+1]))break;
				Add(dp[i+1][ca[x][k]],dp[i][x]);
			}
		}
	}
	int ans=0;
	for(int i=0;i<1<<sz[ct];i++)
		Add(ans,dp[ct][i]);
	printf("%d\n",ans);
	return 0;
}
