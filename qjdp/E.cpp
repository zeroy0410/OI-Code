#include<bits/stdc++.h>
#define M 105
using namespace std;
char S[M];
int dp[M][M],n;
int calc(int x){
	int res=0;
	while(x){
		res++;
		x/=10;
	}
	return res;
}
bool check(int l,int r,int len){
	for(int i=l;i<=r;i++)
		if(S[i]!=S[(i-l)%len+l])return 0;
	return 1;
}
int dfs(int l,int r){
	if(l==r)return 1;
	if(dp[l][r]!=-1)return dp[l][r];
	int& res=dp[l][r];res=2e9;
	for(int len=1;len<r-l+1;len++){
		if((r-l+1)%len!=0)continue;
		if(check(l,r,len))
			res=min(res,calc((r-l+1)/len)+2+dfs(l,l+len-1));
	}
	for(int i=l;i<r;i++){
		int tmp=dfs(l,i)+dfs(i+1,r);
		for(int len=1;len<r-i;len++){
			if((r-i)%len!=0)continue;
			if(check(i+1,r,len)){
				tmp=min(tmp,dfs(l,i)+2+calc((r-i)/len)+dfs(i+1,i+len));
			}
		}
		res=min(res,tmp);
	}
	return res;
}
int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%s",S+1);
	n=strlen(S+1);
	printf("%d\n",dfs(1,n));
	return 0;
}
