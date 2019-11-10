#include<bits/stdc++.h>
#define M 45
#define LL long long
using namespace std;
bool mm1;
int n,m;
LL ca[M];
struct P0{
	set<LL>S;
	map<LL,int>bin;
	void dfs(LL now,LL sta){
		S.insert(now);
		LL tmp=sta;
		while(tmp){
			int x=bin[tmp&-tmp];
			LL nxt=(sta&ca[x]);
			if(nxt&1LL<<x)nxt^=(1LL<<x);
			dfs(now|(1LL<<x),nxt);
			tmp-=(tmp&-tmp);
		}
	}
	void solve(){
		for(int i=0;i<40;i++)bin[1LL<<i]=i;
		dfs(0,(1LL<<n)-1);
		printf("%lld\n",(int)S.size());
	}
}p0;
struct P100{
	LL dp[1<<16],tmp[1<<16];
	char bin[1<<24];
	void solve(){
		for(int i=0;i<24;i++)bin[1<<i]=i;
		int nn=n/2;
		if(nn>16)nn=16;
		for(int i=0;i<1<<nn;i++){
			LL now=(1LL<<n)-1;
			bool fl=1;
			LL sta=i;
			while(sta){
				int x=bin[sta&-sta];
				if(!(now&1LL<<x)){fl=0;break;}
				now=(now&ca[x]);
				sta-=(sta&-sta);
			}
			dp[i]=fl;
		}
		for(int i=0;i<1<<nn;i++){
			if(dp[i]){
				for(int j=i;j<1<<nn;j=(j+1)|i)
					tmp[j]+=dp[i];
			}
		}
		int res=n-nn;
		LL ans=0;
		for(int i=0;i<1<<res;i++){
			LL now=(1LL<<n)-1;
			bool fl=1;
			LL sta=i;
			while(sta){
				int x=bin[sta&-sta];
				if(!(now&1LL<<(x+nn))){fl=0;break;}
				now=(now&ca[x+nn]);
				sta-=(sta&-sta);
			}
			if(fl){
				ans+=tmp[now&((1<<nn)-1)];
			}
		}
		printf("%lld\n",ans);
	}
}p100;
bool mm2;
int main(){
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		a--;b--;
		ca[a]|=(1LL<<b);
		ca[b]|=(1LL<<a);
	}
	p100.solve();
	return 0;
}
