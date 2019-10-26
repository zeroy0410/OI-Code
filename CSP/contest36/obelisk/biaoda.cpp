#include<cstdio> 
using namespace std;
#define reg register
typedef long long ll;
#define rep(i,a,b) for(reg int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(reg int i=a,i##end=b;i>=i##end;--i)

const int P=1e9+7;
int Pow[400];
int n,m,A;
int G[20][20],cnt[1<<17],dp[1<<17],s[1<<17],t[1<<17];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;++i) {
		scanf("%d%d",&u,&v);
		u--,v--;
		G[u][v]=1;
	}
	A=(1<<n)-1;
	cnt[0]=-1;
	rep(i,1,A) cnt[i]=-cnt[i&(i-1)];
	Pow[0]=1; rep(i,1,n*n) Pow[i]=Pow[i-1]*2%P;
	dp[0]=1;
	for(reg int S=0;S<A;++S) {
		s[0]=0;
		rep(i,0,n-1) t[1<<i]=0;
		rep(i,0,n-1) if(S&(1<<i)) rep(j,0,n-1) ((G[i][j])&&(t[1<<j]++));//t中存储的是当前点与前面的多少点存在连边
		reg int T=S^A;//T表示剩余的节点
		for(reg int R=T&(T-1);;R=(R-1)&T) {
			reg int Q=R^T;//Q表示新增的节点（从小到大）
			s[Q]=s[Q&(Q-1)]+t[Q&-Q];//新增的一堆点能够和前面的多少点连边
			printf("%d %d\n",Q,s[Q]);
			dp[S|Q]=(dp[S|Q]+(ll)dp[S]*Pow[s[Q]]*cnt[Q])%P;
			printf("%d\n",dp[S|Q]);
			if(!R) break;
		}
	}
	printf("%d\n",(dp[A]+P)%P);
}
