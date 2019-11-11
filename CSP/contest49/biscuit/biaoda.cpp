#include<bits/stdc++.h>
#define debug(x) cerr<<"\tDEBUG: "<<#x<<" = "<<(x)<<endl;
using namespace std;
template<typename T>
inline void rd(T &res){
	static char c;res=0;
	bool f=0;
	while((c=getchar())<48)if(c=='-')f=1;
	do res=(res<<1)+(res<<3)+(c^48);
	while((c=getchar())>47);
}
template<typename T>
void Pt(T x){
	if(x>9)Pt(x/10);
	putchar(x%10^48);
}
template<typename T>
inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x==0)putchar('0');
	else Pt(x);
}
template<typename T>
inline void println(T x){
	print(x);
	putchar('\n');
}
template<typename T>inline bool tomax(T &a,T b){return a<b?a=b,1:0;}
template<typename T>inline bool tomin(T &a,T b){return a>b?a=b,1:0;}
const int maxn=2e3+100,P=1e9+7;
long long qpow(long long p,long long q){
	long long res=1;
	while(q){
		if(q&1)res=res*p%P;
		q>>=1;
		p=p*p%P;
	}
	return res;
}
int f[maxn],fr[maxn];
void init(){
	f[0]=fr[0]=1;
	for(int i=1;i<maxn;i++){
		f[i]=1LL*f[i-1]*i%P;
		fr[i]=qpow(f[i],P-2);
	}
}
int C(int a,int b){
	return 1LL*f[a]*fr[b]%P*fr[a-b]%P;
}
void add(int &a,int b){
	a+=b;
	if(a>=P)a-=P;
}
int n,m,q,ans;
int dp[maxn][maxn];
int mx[maxn];
int main(){
//	freopen("biscuit.in","r",stdin);
//	freopen("biscuit.out","w",stdout);
	init();
	rd(n);rd(m);rd(q);
	int Max=0;
	for(int i=1,l,r;i<=q;i++){
		rd(l);rd(r);
		for(int j=r+1;j<=n;j++)
			tomax(mx[j],l);
		tomax(Max,l);
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		add(dp[i][0],dp[i-1][0]);
		for(int j=0;j<n;j++){
			dp[i][j+1]=dp[i-1][j];
			if(mx[i]!=0)add(dp[i][j+1],P-dp[mx[i]-1][j]);
			add(dp[i][j+1],dp[i-1][j+1]);
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=0;j<=n;j++){
			int tmp=qpow(i-1,j)*qpow(m-i+1,n-j)%P;
			add(ans,1LL*tmp*(C(n,j)-(dp[n][j]-dp[Max-1][j]+P)%P+P)%P);
		}
	}
	println(ans*qpow(qpow(m,n),P-2)%P);
	return 0;
}

