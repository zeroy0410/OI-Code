#include<bits/stdc++.h>
#define M 205
using namespace std;
int W,I,N,G;
map<char,int>mp;
int dp[M][M][5];
int num[5];
struct node{int a,b;};
vector<node>wk[5];
char S[15];
char s[M];
char ans[5]={'0','W','I','N','G'};
bool dfs(int l,int r,int x){
	if(l==r)return dp[l][r][x];
	if(dp[l][r][x]!=-1)return dp[l][r][x];
	for(int i=0;i<num[x];i++){
		int a=wk[x][i].a;
		int b=wk[x][i].b;
		for(int j=l;j<=r-1;j++)
			if(dfs(l,j,a)&&dfs(j+1,r,b))return dp[l][r][x]=1;
	}
	return dp[l][r][x]=0;
}
int main(){
	mp['W']=1;mp['I']=2;mp['N']=3;mp['G']=4;
	for(int i=1;i<=4;i++)scanf("%d",&num[i]);
	for(int i=1;i<=4;i++){
		for(int j=1;j<=num[i];j++){
			scanf("%s",S+1);
			int a=mp[S[1]];
			int b=mp[S[2]];
			wk[i].push_back((node){a,b});
		}
	}
	scanf("%s",s+1);
	memset(dp,-1,sizeof(dp));
	int n=strlen(s+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=4;j++)dp[i][i][j]=0;
		dp[i][i][mp[s[i]]]=1;
	}
	bool fl=0;
	for(int i=1;i<=4;i++)
		if(dfs(1,n,i))fl=1,printf("%c",ans[i]);
	if(!fl)puts("The name is wrong!");
	puts("");
	return 0;
}
