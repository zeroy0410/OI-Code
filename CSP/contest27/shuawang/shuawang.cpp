#include<bits/stdc++.h>
#define MM 50005
#define LL long long
using namespace std;
int T,n,m,q;
char M[MM],S[MM];
struct P20{
	int A[MM],ac,mch,base;
	void dfs(int x){
		if(x>wcnt){
			int s=0,ss=0;
			bool fl=0;
			for(int i=1;i<=n;i++){
				s=s*10+S[i]-'0';
				if(i>=m){
					int tmp=s-ss*base;
					if(tmp==mch)fl=1;
					ss=ss*10+S[i-m+1]-'0';
				}
			}
			if(fl)A[++ac]=s;
			return;
		}
		for(int i=0;i<=9;i++){
			S[wk[x]]='0'+i;
			dfs(x+1);
		}
	}
	int wk[MM],wcnt;
	void solve(){
		wcnt=0;mch=0;ac=0;base=1;
		for(int i=1;i<=m;i++)
			mch=10*mch+M[i]-'0',base=base*10;
		for(int i=1;i<=n;i++)
			if(S[i]=='?')wk[++wcnt]=i;
		dfs(1);
		sort(A+1,A+ac+1);
		while(q--){
			LL k;
			scanf("%lld",&k);
			if(k>ac)puts("-1");
			else printf("%d\n",A[k]);
		}
	}
}p20;
int main(){
	freopen("shuawang.in","r",stdin);
	freopen("shuawang.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&q);
		scanf("%s",M+1);m=strlen(M+1);
		scanf("%s",S+1);
		if(n<=7)p20.solve();
	}
	return 0;
}
