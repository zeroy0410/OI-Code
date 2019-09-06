#include<bits/stdc++.h>
#define M 100005
using namespace std;
int T,n,m;
char S[M],P[M],tmp[M];
int pre[M],nxt[M];
void del(int x){
	pre[nxt[x]]=pre[x];
	nxt[pre[x]]=nxt[x];
}
void merge(int a,int b){
	if(S[a]!=S[b])return;
	del(a);
}
bool solve(){
	for(int i=m;i>=1;i--){
		if(P[i]=='L'){
			if(nxt[0]==n+1)return 1;
			bool fl=0,rd=0;
			for(int j=nxt[0];j!=n+1;j=nxt[j]){
				if(fl&&S[j]=='B'){del(j);rd=1;merge(pre[j],nxt[j]);}
				if(rd&&S[j]=='R')break;
				if(S[j]=='R')fl=1;
			}
			if(!rd){
				fl=0;
				for(int j=nxt[0];j!=n+1;j=nxt[j]){
					if(S[j]=='B'){del(j);fl=1;}
					if(S[j]=='R')break;
				}
				if(!fl){
					for(int j=pre[n+1];j!=0;j=pre[j]){
						if(S[j]=='B')del(j);
						else break;
					}
				}
			}
		}
		else {
			bool fl=0,rd=0;
			for(int j=nxt[0];j!=n+1;j=nxt[j]){
				if(fl&&S[j]=='R'){del(j);rd=1;merge(pre[j],nxt[j]);}
				if(rd&&S[j]=='B')break;
				if(S[j]=='B')fl=1;
			}
			if(!rd){
				fl=0;
				for(int j=nxt[0];j!=n+1;j=nxt[j]){
					if(S[j]=='R'){del(j);fl=1;}
					if(S[j]=='B')break;
				}
				if(!fl){
					for(int j=pre[n+1];j!=0;j=pre[j]){
						if(S[j]=='R')del(j);
						else break;
					}
				}
			}
		}
	}
	if(nxt[0]==n+1)return 1;
	return 0;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s%s",tmp+1,P+1);
		n=strlen(tmp+1);m=strlen(P+1);
		int tc=0;
		for(int i=1;i<=n;i++)
			if(tmp[i]!=tmp[i-1])
				S[++tc]=tmp[i];
		S[tc+1]=0;
		n=tc;
		for(int i=0;i<=n+1;i++){
			pre[i]=i-1;
			nxt[i]=i+1;
		}
		if(solve())puts("Yes");
		else puts("No");
	}
	return 0;
}
