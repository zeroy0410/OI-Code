#include<bits/stdc++.h>
#define M 200005
using namespace std;
const int mod=998244353;
int n;
char S[M];
struct P30{
	bool mark[60005];
	int ans;
	int get(){
		int res=0;
		for(int i=1;i<=n;i++)
			res=res*3+S[i];
		return res;
	}
	void dfs(){
		int cod=get();
		if(mark[cod])return;
		mark[cod]=1;ans++;
		for(int i=1;i<=n-1;i++){
			if(S[i]!=S[i+1]){
				int to=3-S[i]-S[i+1];
				char a=S[i],b=S[i+1];
				S[i]=to;S[i+1]=to;
				dfs();
				S[i]=a;S[i+1]=b;
			}
		}
	}
	void solve(){
		dfs();
		printf("%d\n",ans);
	}
}p30;
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%s",S+1);
	n=strlen(S+1);
	for(int i=1;i<=n;i++)S[i]-='a';
	p30.solve();
	return 0;
}
