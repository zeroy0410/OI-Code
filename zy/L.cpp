#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
const int mod=1e9+7;
int T,n,m,fa[M],a[M],b[M];
int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
int cnt[M],fac[M];
int main(){
	scanf("%d",&T);
	fac[0]=1;for(int i=1;i<M;i++)fac[i]=1LL*fac[i-1]*i%mod;
	for(int i=1;i<M;i++)fa[i]=i;
	while(T--){
		scanf("%d%d",&n,&m);
		LL ans=fac[n];
		for(int i=0;i<m;i++)
			scanf("%d%d",&a[i],&b[i]);
		for(int i=1;i<1<<m;i++){
			int fl=1,tc=0,ct=0;
			bool no=0;
			for(int j=0;j<m;j++){
				if(!(i&1<<j))continue;
				fl=-fl;ct++;
				int x=getfa(a[j]),y=getfa(b[j]);
				if(x==y){no=1;break;}
				fa[x]=y;
				x=a[j];y=b[j];
				cnt[x]++;cnt[y]++;
				if(cnt[x]>2||cnt[y]>2){no=1;break;}
				tc+=1-(cnt[x]==2)-(cnt[y]==2);
			}
			if(!no)ans=(ans+fl*(1LL<<tc)*fac[n-ct])%mod;
			for(int j=0;j<m;j++){
				if(!(i&1<<j))continue;
				fa[a[j]]=a[j];fa[b[j]]=b[j];
				cnt[a[j]]=0;cnt[b[j]]=0;
			}
		}
		cout<<(ans+mod)%mod<<endl;
	}
	return 0;
}
