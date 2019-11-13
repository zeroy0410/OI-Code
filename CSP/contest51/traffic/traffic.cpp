#include<bits/stdc++.h>
#define M 1000005
using namespace std;
int n,m,q;
int fa[M],dis[M],g[M];
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
int main(){
//	freopen("traffic.in","r",stdin);
//	freopen("traffic.out","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1,op,u,v,x,w,b,c;i<=q;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d%d",&u,&v,&w);
			int r1=getfa(u),r2=getfa(v);
			if(fa[r1]!=fa[r2]){
				fa[r1]=r2;
				dis[r1]=(1LL*dis[u]+dis[v]+w)%m;
				g[r1]=gcd(gcd(g[r1],g[r2]),2*w);
			}
			else g[f1]=gcd(gcd(g[f1],(1LL*dis[u]+dis[v]+w)%m),2*w);
		}
		else {
			scanf("%d%d%d%d%d",&u,&v,&x,&b,&c);
			int r1=getfa(u),r2=getfa(v);
			b%=g[r1];
			int A=b;
		}
	}
	return 0;
}
