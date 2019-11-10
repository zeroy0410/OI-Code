#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,F;
int sg[M];
namespace P70{
	bool mark[M];
	void GetSG(int n,int f){
		for(int i=f;i<=n;i++){
			memset(mark,0,sizeof(mark));
			for(int j=2;j<=i;j++){
				int t=i/j,d=i%j;
				int tmp=0;
				if(d&1)tmp^=sg[t+1];
				if((j-d)&1)tmp^=sg[t];
				mark[tmp]=1;
			}
			while(mark[sg[i]])sg[i]++;
		}
	}
	void solve(){
		GetSG(1000,F);
		for(int i=1,m;i<=n;i++){
			scanf("%d",&m);
			int ans=0,t;
			while(m--)
				ans^=sg[(scanf("%d",&t)*t)];
			printf("%d%c",ans>0," \n"[i==n]);
		}
		
	}
}
namespace P100{
	int Getsg(int x){
		if(sg[x]!=-1)return sg[x];
		bool mark[x+1];
		memset(mark,0,sizeof(mark));
		for(int i=2;i<=x;i=x/(x/i)+1){
			printf("%d ",i);
			for(int j=i;j<=i+1&&j<=x;j++){
				int t=x/j,d=x%j,res=0;
				if(d&1)res^=Getsg(t+1);
				if((j-d)&1)res^=Getsg(t);
				mark[res]=1;
			}
		}
		putchar('\n');
		sg[x]=0;
		while(mark[sg[x]])sg[x]++;
		return sg[x];
	}
	void solve(){
		memset(sg,-1,sizeof(sg));
		for(int i=0;i<F;i++)sg[i]=0;
		for(int i=1,m,t;i<=n;i++){
			scanf("%d",&m);
			int res=0;
			while(m--)res^=Getsg(scanf("%d",&t)*t);
			printf("%d%c",res>0," \n"[i==n]);
		}
	}
}
int main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&F);
	F=max(F,2);
	P100::solve();
	return 0;
}
