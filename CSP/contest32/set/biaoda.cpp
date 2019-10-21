#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,p,x,t,tmp;
int rnk[20],g[300050];
bool vis[300050][20];
int f[300050];
int main(){
	//freopen("ts.in","r",stdin);
	//freopen("ts.out","w",stdout);
	scanf("%d%d%d",&n,&m,&p);
	t=(1<<n)-1;
	for(int i=1;i<=m;++i){
		scanf("%d",&x);
		for(int j=0;j<n;++j)
			if(x&(1<<j))
				vis[x][j]=true;
	}
	for(int i=0;i<n;++i)
		for(int j=0;j<=t;++j)
			if(vis[j][i]){
				for(int k=0;k<n;++k)
					if(!(j&(1<<k)))
						vis[j|(1<<k)][i]=true;
			}
	memset(f,-1,sizeof(f));
	f[0]=0;
	for(int i=0;i<t;++i){
		g[i]=g[i>>1]+(i&1);
		if(f[i]!=-1){
			for(int j=0;j<n;++j)
				if(!(i&(1<<j))){
					if(!(p&(1<<g[i]))&&vis[i|(1<<j)][j])
						continue;
					else
						f[i|(1<<j)]=j;
				}
		}
	}
	if(f[t]==-1)
		printf("-1");
	else{
		tmp=n-1;
		while(t){
			rnk[f[t]]=tmp--;
			t^=(1<<f[t]);
			printf("%d\n",t);
		}
		t=(1<<n)-1;
		for(int i=1;i<=t;++i){
			tmp=0;
			for(int j=0;j<n;++j)
				if(i&(1<<j))
					tmp=max(tmp,rnk[j]);
			printf("%d",(p&(1<<tmp))>0);
		}
	}
	return 0;
}
