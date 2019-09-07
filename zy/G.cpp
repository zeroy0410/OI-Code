#include<bits/stdc++.h>
using namespace std;
int n;
char s[15];
int dp[2][1<<10];
int mp[128];
bool dfs(int c,int st,int ck){
	if(!ck)return false;
	if(dp[c][st]!=-1)return dp[c][st];
	for(int i=0;i<n;i++)
		if(!(st&(1<<i))&&!dfs(!c,st|(1<<i),ck^(1<<mp[s[i]])))return true;
	return false;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%s",s);
		n=strlen(s);
		int ct=0,st=0;
		memset(mp,-1,sizeof(mp));
		for(int i=0;i<n;i++){
			if(mp[s[i]]==-1)mp[s[i]]=ct++;
			st^=1<<mp[s[i]];
		}
		st^=(1<<ct)-1;
		memset(dp,-1,sizeof(dp));
		puts(dfs(0,0,st)?"Karan":"Watan");
	}
	return 0;
}
