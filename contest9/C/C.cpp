#include<bits/stdc++.h>
#define M 100005
using namespace std;
int SG[M];
int T,n,F;
int get(int x){
	if(x<F)return 0;
	if(SG[x]!=-1)return SG[x];
	bool mark[x+1];
	memset(mark,0,sizeof(mark));
	for(int i=2;i<=x;i=x/(x/i)+1)
		for(int j=i;j<=i+1&&j<=x;j++){
			int t=x/j,d=x%j,res=0;
			if(d&1)res^=get(t+1);
			if((j-d)&1)res^=get(t);
			mark[res]=1;
		}
	SG[x]=0;
	while(mark[SG[x]])SG[x]++;
	return SG[x];
}
int main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	memset(SG,-1,sizeof(SG));
	scanf("%d%d",&T,&F);
	while(T--){
		scanf("%d",&n);
		int ans=0;
		for(int i=1,x;i<=n;i++)scanf("%d",&x),ans^=get(x);
		printf("%d ",!(ans==0));
	}
	return 0;
}
