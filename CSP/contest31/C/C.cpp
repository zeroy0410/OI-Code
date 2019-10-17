#include<bits/stdc++.h>
using namespace std;
template <typename T> void chmin(T&x,const T &y) { if(x>y)x=y; }
template <typename T> void chmax(T &x,const T &y){ if(x<y)x=y; }
typedef long long s64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int,int> pii;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define rep0(i,l,r) for(int i=l;i<r;++i)
#define gc (c=getchar())
int read() {
	char c;
	while(gc<'-');
	if(c=='-'){ 
		int x=gc-'0';
		while(gc>='0')x=x*10+c-'0';
		return -x;
	}
	int x=c-'0';
	while(gc>='0')x=x*10+c-'0';
	return x;
}
#undef gc
const int N=3000+5;
struct Point{int p,l,r;};
Point p[N];
int n,q[N*3],u;
s64 dp[N][N*3],f[N*3];
int main(){
	cin>>n;
	rep(i,1,n)scanf("%d%d%d",&p[i].p,&p[i].l,&p[i].r);
	rep(i,1,n) {
		q[++u]=(p[i].l=p[i].p-p[i].l);
		q[++u]=p[i].p;
		q[++u]=(p[i].r=p[i].p+p[i].r);
	}
	sort(q+1,q+u+1);
	u=unique(q+1,q+u+1)-q-1;
	rep(i,1,n) {
#define F(x) x=lower_bound(q+1,q+u+1,x)-q
		F(p[i].p);
		F(p[i].l);
		F(p[i].r);
#undef F
	}
	sort(p+1,p+n+1,[&](const Point &a,const Point &b){return a.p<b.p;});
	rep(i,1,n) {
		rep(r,1,u)dp[i][r]=dp[i-1][r];
		int nl=p[i].l,nr=p[i].p;
		rep(r,nl,u)f[i]=0;
		int mx=nr;
		per(j,i-1,1) {
			chmax(f[mx],dp[j][nl]+q[mx]-q[nl]);
			chmax(mx,p[j].r);
		}
		chmax(f[mx],s64(q[mx]-q[nl]));
		per(r,u,nl) {
			chmax(dp[i][r],f[r]);
			chmax(f[r-1],f[r]-(q[r]-q[r-1]));
		}
		nl=p[i].p;nr=p[i].r;
		rep(r,nl,nr)chmax(dp[i][r],dp[i-1][nl]+q[r]-q[nl]);
		rep(r,1,u)chmax(dp[i][r],dp[i][r-1]);
	}
	s64 ans=0;
	rep(r,1,u)chmax(ans,dp[n][r]);
	cout<<ans<<endl;
	return 0;
}
