#include<bits/stdc++.h>
#define M 1000005
using namespace std;
int n,m,q;
int fa[M],dis[M],g[M];
void read(int &x){
	x=0;
	int f=1;
	char c;
	while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
	do x=(x<<3)+(x<<1)+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	x*=f;
}
int gcd(int a,int b){ return b==0?a:gcd(b,a%b); }
void exgcd(int a,int b,int& x,int& y){
	if(b==0){x=1,y=0;return;}
	else exgcd(b,a%b,y,x),y-=a/b*x;
}
int getfa(int x){
	if(fa[x]==x)return x;
	int to=getfa(fa[x]);
	dis[x]=(dis[x]+dis[fa[x]])%m;
	return fa[x]=to;
}
void merge(int u,int v,int w){
	int r1=getfa(u),r2=getfa(v);
	if(fa[r1]!=fa[r2]){
		fa[r1]=r2;
		dis[r1]=(1LL*dis[u]+dis[v]+w)%m;
		g[r2]=gcd(gcd(g[r1],g[r2]),2*w);
	}
	else g[r1]=gcd(gcd(g[r1],(1LL*dis[u]+dis[v]+w)%m),2*w);
}
int main(){
//	freopen("traffic.in","r",stdin);
//	freopen("traffic.out","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)dis[i]=0,fa[i]=i,g[i]=m;
	for(int i=1,op,u,v,x,w,b,c;i<=q;i++){
		read(op);
		if(op==1){ read(u);read(v);read(w); merge(u,v,w); }
		else {
			int ans=0;
			read(u);read(v);read(x);read(b);read(c);
			int r1=getfa(u),r2=getfa(v);
			if(r1!=r2){puts("0");continue;}
			b%=g[r1];
			int A=b,B=g[r1],G=gcd(A,B),C=1LL*dis[u]+dis[v]-x+B;
			if(C%G){puts("0");continue;}
			int X,Y;A/=G;B/=G;C/=G;
			exgcd(A,B,X,Y);X=(1LL*X*C%B+B)%B;
			if(X<c)ans=(c-1-X)/B+1;
			printf("%d\n",ans);
		}
	}
	return 0;
}
