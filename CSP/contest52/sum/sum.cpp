#include<bits/stdc++.h>
#define M 1205
#define LL long long
using namespace std;
int n,m,A[M];
int pre[M][35],las[M][35],now[35];
LL sum[M];
void Add(int *X,int v){
	for(int i=1;i<=m;i++){
		if(v>X[i]){
			for(int j=m;j>=i+1;j--)
				X[j]=X[j-1];
			X[i]=v;
			break;
		}
	}
}
void Add2(int *X,int v){
	for(int i=1;i<=m;i++){
		if(v<X[i]){
			for(int j=m;j>=i+1;j--)
				X[j]=X[j-1];
			X[i]=v;
			break;
		}
	}
}
int Q[35];
void Sort(int *X,int *Y){
	int i=1,j=1;
	for(int k=1;k<=m;k++){
		int a,b;
		if(i<=m)a=X[i];
		else a=-1e9;
		if(j<=m)b=Y[j];
		else b=-1e9;
		if(a>=b){Q[k]=a;i++;}
		else {Q[k]=b;j++;}
	}
}
int main(){
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]),sum[i]=sum[i-1]+A[i];
	for(int i=0;i<=n+1;i++)
		for(int j=1;j<=m;j++)
			pre[i][j]=las[i][j]=-1e9;
	for(int i=n;i>=1;i--){
		for(int j=1;j<=m;j++)
			las[i][j]=las[i+1][j];
		Add(las[i],A[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			pre[i][j]=pre[i-1][j];
		Add(pre[i],A[i]);
	}
	LL ans=-1e18;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)now[j]=1e9;
		for(int j=i;j<=n;j++){
			Add2(now,A[j]);
			LL res=sum[j]-sum[i-1];
			Sort(pre[i-1],las[j+1]);
			for(int k=1;k<=m;k++){
				if(now[k]<Q[k])
					res+=Q[k]-now[k];
				else break;
			}
			ans=max(ans,res);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
