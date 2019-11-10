#include<bits/stdc++.h>
#define REP(i,a,b) for(int i(a);i<=(b);++i)
#define dbg(x) cout<<#x<<" = "<<(x)<<endl;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
using namespace std;
inline int read(){
	int f=1,x=0;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return f*x;
}
inline char smin(int&x,const int&y){return x>y?x=y,1:0;}
inline char smax(int&x,const int&y){return x<y?x=y,1:0;}
struct FastIO{
	static const int S=1310720;
	int wpos;char wbuf[S];
	FastIO():wpos(0) {}
	inline int xchar(){
		static char buf[S];
		static int len=0,pos=0;
		if(pos==len)pos=0,len=fread(buf,1,S,stdin);
		if(pos==len)return -1;
		return buf[pos++];
	}
	inline int read(){
		int c=xchar(),x=0;
		while(c<=32&&~c)c=xchar();
		if(c==-1)return -1;
		for(;'0'<=c&&c<='9';c=xchar())x=x*10+c-'0';
		return x;
	}
}io;
#define read io.read
const int N=2005,p=998244353;
int n,a[4][N],f[N][N],g[N][N],w[4][N],ans[N];
inline void inc(int&x,int y){x+=y;if(x>=p)x-=p;}
int main(){
	n=read();
	REP(i,1,n)REP(j,0,3)a[j][i]=read();
	REP(i,0,3)REP(j,0,3)w[i][j]=read();
	int m=n/2+1;
	REP(k,0,3){
		memset(f,0,sizeof f);memset(g,0,sizeof g);
		f[0][0]=g[n+1][0]=1;
		REP(i,1,n)REP(j,0,i)
			f[i][j]=((j?1ll*a[k][i]*f[i-1][j-1]%p:0)+1ll*(1-a[k][i]+p)*f[i-1][j])%p;
		for(int i=n;i;--i)for(int j=n-i+1;~j;--j)
			g[i][j]=((j?1ll*a[k][i]*g[i+1][j-1]%p:0)+1ll*(1-a[k][i]+p)*g[i+1][j])%p;
		REP(i,1,n)for(int j=n-i+1;~j;--j)inc(g[i][j],g[i][j+1]);
		REP(i,1,n)REP(j,0,i-1)if(f[i-1][j]){
			REP(t,0,3)if(t==k)ans[i]=(ans[i]+1ll*f[i-1][j]*g[i+1][max(0,m-1-j)]%p*a[k][i]%p*w[k][k])%p;
			else ans[i]=(ans[i]+1ll*f[i-1][j]*g[i+1][max(0,m-j)]%p*a[t][i]%p*w[k][t])%p;
		}
	}
	REP(i,1,n)printf("%d\n",ans[i]);
	return 0;
}
