#include<bits/stdc++.h>
using namespace std;
const int M=1005,inf=2e9;
int n,m;
int h[M],nx[M*10],to[M*10],v[M*10],tot=1;
void add(int a,int b,int c){
	to[++tot]=b;v[tot]=c;
	nx[tot]=h[a];h[a]=tot;
}
void adds(int a,int b,int c){
	add(a,b,c);add(b,a,0);
}
int dep[M],q[M];
bool bfs(){
	memset(dep,0,sizeof(dep));
	int l=0,r=0;
	dep[q[r++]=0]=1;
	while(l<r){
		int x=q[l++];
		for(int i=h[x];i;i=nx[i]){
			int y=to[i];
			if(!dep[y]&&v[i]){
				dep[y]=dep[x]+1;
				if(y==n*m+1)return true;
				q[r++]=y;
			}
		}
	}
	return false;
}
int cur[M];
int dfs(int x,int fl){
	if(x==n*m+1)return fl;
	int res=0;
	for(int i=cur[x];i;i=nx[i]){
		int y=to[i],inc;
		if(v[i]&&dep[y]==dep[x]+1&&(inc=dfs(y,min(fl,v[i])))){
			v[i]-=inc;v[i^1]+=inc;
			fl-=inc;res+=inc;
			if(!fl)break;
		}
	}
	return res;
}
int dinic(){
	int ans=0;
	while(bfs()){
		memcpy(cur,h,sizeof(cur));
		ans+=dfs(0,inf);
	}
	return ans;
}
int get(int x,int y){
	return (x-1)*m+y;
}
int main(){
	scanf("%d%d",&n,&m);
	int sum=0;
	for(int i=1;i<=n;i++)
		for(int a,c=i&1,j=1;j<=m;j++,c=!c){
			scanf("%d",&a),sum+=a;
			if(!c){
				int p=get(i,j);
				adds(0,p,a);
				if(i>1)adds(p,get(i-1,j),inf);
				if(i<n)adds(p,get(i+1,j),inf);
				if(j>1)adds(p,get(i,j-1),inf);
				if(j<m)adds(p,get(i,j+1),inf);
			}else adds(get(i,j),n*m+1,a);
		}
	printf("%d\n",sum-dinic());
	return 0;
}