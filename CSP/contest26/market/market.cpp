#include<bits/stdc++.h>
#define M 305
#define LL long long
using namespace std;
bool mm1;
LL dp[M*M],tmp[M*M];
int n,m;
struct node{ int c,v; };
vector<node>wk[M];
struct que{int co,id;};
vector<que>Q[M];
int ans[100005];
bool mm2;
int main(){
	freopen("market.in","r",stdin);
	freopen("market.out","w",stdout);
//	printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
	scanf("%d%d",&n,&m);
	for(int i=1,c,v,t;i<=n;i++){
		scanf("%d%d%d",&c,&v,&t);
		wk[t].push_back((node){c,v});
	}
	for(int i=1,co,t;i<=m;i++){
		scanf("%d%d",&t,&co);
		Q[t].push_back((que){co,i});
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=300;i++){
		for(int j=0;j<wk[i].size();j++){
			int c=wk[i][j].c,v=wk[i][j].v;
			for(int k=90000;k>=v;k--)
				dp[k]=min(dp[k],dp[k-v]+c);
		}
		tmp[90000]=dp[90000];
		for(int k=89999;k>=0;k--){
			tmp[k]=dp[k];
			tmp[k]=min(tmp[k],tmp[k+1]);
		}
		for(int j=0;j<Q[i].size();j++){
			int co=Q[i][j].co,id=Q[i][j].id;
			int l=0,r=90000,res=-1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(tmp[mid]<=co){res=mid;l=mid+1;}
				else r=mid-1;
			}
			ans[id]=res;
		}
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
