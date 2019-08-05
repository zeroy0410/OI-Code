#include<bits/stdc++.h>
using namespace std;
#define M 105
int tot,s,e,n,m,i,j,a,a1[M],a2[M],t1,t2,h[M],H[M],nx[M*M],v[M*M],t[M*M],l,r,Q[M],dep[M],sum,res;
bool f;
char c[205];
void add(int x,int y,int z) {
	t[++tot]=y,nx[tot]=h[x],h[x]=tot,v[tot]=z;
}
int bfs() {
	for(int i=1; i<=e; i++)dep[i]=0;
	l=0,Q[r=1]=s,dep[s]=1;
	while(l<r) {
		a=Q[++l];
		for(int i=H[a]=h[a]; i; i=nx[i])
			if(!dep[t[i]]&&v[i])dep[t[i]]=dep[a]+1,Q[++r]=t[i];
	}
	return dep[e];
}
int dfs(int x,int y) {
	if(x==e)return y;
	int ans=0,f;
	for(int i=H[x]; ans<y&&i; i=nx[i])
		if(dep[t[i]]==dep[x]+1&&v[i])
			H[x]=i,f=dfs(t[i],min(v[i],y-ans)),v[i]-=f,v[i^1]+=f,ans+=f;
	return ans;
}
int main() {
	tot=1,scanf("%d%d",&m,&n),s=n+m+1,e=n+m+2;
	for(i=1; i<=m; i++) {
		scanf("%d",&a),add(s,i,a),add(i,s,0),sum+=a;
		while(getchar()==' ')scanf("%d",&a),add(i,a+m,1e9),add(a+m,i,0);
	}
	for(i=1; i<=n; i++)scanf("%d",&a),add(m+i,e,a),add(e,m+i,0);
	while(bfs())res+=dfs(s,1e9);
	for(i=1; i<=m; i++)if(dep[i])a1[++t1]=i;
	for(i=1; i<=n; i++)if(dep[i+m])a2[++t2]=i;
	for(i=1; i<t1; i++) printf("%d ",a1[i]);
	printf("%d\n",a1[t1]);
	for(i=1; i<t2; i++) printf("%d ",a2[i]);
	printf("%d\n%d\n",a2[t2],sum-res);
	return 0;
}