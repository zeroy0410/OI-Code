#include<bits/stdc++.h>
#define LL long long
#define have(x,y) (((x)>>((y)-1))&1)
using namespace std;
const int P=998244353;
int n,m;
int U[405],V[405];
LL dp[1<<18|5];int cnt[1<<18|5];
bool mark[1<<18|5];
void Add(LL &x,LL y){
	x+=y;
	if(x>=P)x-=P;
	if(x<0)x+=P;
}
void Solve(){
	cnt[0]=-1;for(int i=1;i<1<<n;i++)cnt[i]=-cnt[i&(i-1)];
	dp[0]=1;
	for(int i=1;i<1<<n;i++)
		for(int j=1;j<=m;j++)
			if(have(i,U[j]) and have(i,V[j])){
				mark[i]=true;break;
			}
	for(int i=1;i<1<<n;i++)
		for(int j=i;j>=1;j=(j-1)&i)
			if(!mark[j])Add(dp[i],dp[i^j]*cnt[j]);
	printf("%lld\n",dp[(1<<n)-1]*m%P*499122177%P);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d",&U[i],&V[i]);
	Solve();
	return 0;
}
