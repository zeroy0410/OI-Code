#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n;LL P;
struct Pbl{
	int pri[105],pcnt,base;
	bool mark[105];
	void Init(){
		for(int i=2;i<=n;i++){
			if(mark[i])continue;
			pri[pcnt++]=i;
			for(int j=i;j<=n;j+=i)
				mark[j]=1;
		}
		for(int i=2;i<=n;i++){
			for(int j=0;j<pcnt;j++)
				if(i%pri[j]==0)
					hav[i]|=(1<<j);
		}
	}
	void Add(int &x,int y){
		x+=y;
		if(x>=P)x-=P;
	}
	int sum[1<<25],tmp[1<<25],hav[105];
	void solve(){
		Init();
		sum[0]=1;
		base=(1<<pcnt)-1;
		for(int i=2;i<=n;i++){
			memset(tmp,0,sizeof(tmp));
			for(int j=0;j<=base;j++)Add(tmp[j|hav[i]],sum[j]);
			for(int j=0;j<=base;j++)Add(sum[j],tmp[j]);
		}
		memcpy(tmp,sum,sizeof(tmp));
		for(int i=0;i<pcnt;i++)
			for(int j=0;j<=base;j++)
				if(j&1<<i)
					Add(sum[j],sum[j^(1<<i)]);
		int ans=0;
		for(int i=0;i<=base;i++)
			Add(ans,1LL*tmp[i]*sum[i^base]%P);
		printf("%d",ans);
	}
}pbl;
int main(){
	freopen("dinner.in","r",stdin);
	freopen("dinner.out","w",stdout);
	scanf("%d%lld",&n,&P);
	pbl.solve();
	return 0;
}
