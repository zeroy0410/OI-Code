#include<bits/stdc++.h>
#define LL long long
using namespace std;
#define M 1000005
const int mod=1e9;
int n,m,K;
struct que{int a,b,c;}A[M];
int fa[M<<1],g[M<<1],bj[M<<1];
LL ans;
int getfa(int x){
	if(fa[x]==x)return x;
	int t=fa[x];
	fa[x]=getfa(fa[x]),g[x]=(g[x]+g[t])%2;
	return fa[x];
}
LL solve(){
	int r1,r2,t;
	for(int i=1;i<=n+m;i++)fa[i]=i,g[i]=0,bj[i]=-1;
	fa[n+1]=1;bj[1]=0;
	for(int i=1,a,b,c;i<=K;i++){
		a=A[i].a,b=A[i].b,c=A[i].c;
		if(a==1&&b==1)continue;
		if(a==1||b==1){
			if(b==1){r1=getfa(a);t=a;}
			else {r1=getfa(b+n);t=b+n;}
			if(bj[r1]==-1)bj[r1]=(c^g[t]);
			else if(bj[r1]!=(c^g[t]))return 0;
		}
		else {
			r1=getfa(a),r2=getfa(b+n);
			if(r1!=r2){
				fa[r1]=r2;
				g[r1]=(g[b+n]-g[a]+c+4)%2;
				if(bj[r1]!=-1&&bj[r2]!=-1&&bj[r2]!=bj[r1]^g[r1])return 0;
				if(bj[r2]==-1&&bj[r1]!=-1)bj[r2]=bj[r1]^g[r1],bj[r1]=-1;
			}
			else if((g[a]^g[b+n]^c)==1)return 0;
		}
	}
	LL res=1;
	for(int i=1;i<=n+m;i++){
		if(getfa(i)==i&&bj[i]==-1){
			res=(res<<1)%mod;
			// cout<<i<<endl;
		}
	}
	return res;	
}
int main(){
//	freopen("color.in","r",stdin);
//	freopen("color.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	int fl=-1;
	for(int i=1;i<=K;i++){
		scanf("%d%d%d",&A[i].a,&A[i].b,&A[i].c);
		if(A[i].a==1&&A[i].b==1)fl=A[i].c;
		if(!(A[i].a&1)&&!(A[i].b&1))A[i].c^=1;
	}
	LL ans=0;
	if(fl==-1||fl==0)ans+=solve();
	if(fl==-1||fl==1){
		for(int i=1;i<=K;i++)
			if(A[i].a!=1&&A[i].b!=1)
				A[i].c^=1;
		ans+=solve();
	}
	ans%=mod;
	printf("%lld\n",ans);
	return 0;
}
