#include<bits/stdc++.h>
#define M 800005
#define LL long long
using namespace std;
int n,m,x1,x2;
int A[M],B[M];
struct Pshui{
	double ans;
	int fa[M<<1];
	int getfa(int x){
		return fa[x]==x?x:fa[x]=getfa(fa[x]);
	}
	struct edge{
		int a,b;
		double c;
		bool operator < (const edge& res)const{
			return c<res.c;
		}
	}E[M<<2];
	int tt;
	double calc(int x,int y){
		return 1.0*sqrt(1LL*x*x+1LL*y*y);
	}
	void solve(){
		for(int i=1;i<=n+m;i++)fa[i]=i;
		int cur=0;tt=0;
		for(int i=1;i<=n;i++){
			while(B[cur+1]<=A[i]&&cur+1<=m)cur++;
			if(i>1)E[++tt]=(edge){i-1,i,A[i]-A[i-1]};
			if(cur>0)E[++tt]=(edge){cur+n,i,calc(x2-x1,A[i]-B[cur])};
		}
		cur=0;
		for(int i=1;i<=m;i++){
			while(A[cur+1]<=B[i]&&cur+1<=n)cur++;
			if(i>1)E[++tt]=(edge){i-1+n,i+n,B[i]-B[i-1]};
			if(cur>0)E[++tt]=(edge){cur,i+n,calc(x2-x1,B[i]-A[cur])};
		}
		sort(E+1,E+tt+1);
		int ct=0;
		for(int i=1;i<=tt;i++){
			int a=E[i].a,b=E[i].b;
			double c=E[i].c;
			a=getfa(a);b=getfa(b);
			if(a!=b){
				fa[a]=b;
				ans+=c;
				ct++;
			}
			if(ct==n+m-1)break;
		}
		printf("%.2lf\n",ans);
	}
}pshui;
int main(){
	freopen("cable.in","r",stdin);
	freopen("cable.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&x1,&x2);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
		A[i]+=A[i-1];
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&B[i]);
		B[i]+=B[i-1];
	}
	pshui.solve();
	return 0;
}
