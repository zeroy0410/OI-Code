#include<stdio.h>
#include<algorithm>
#define LL long long
#define M 3005
using namespace std;
bool mm1;
int A[M][M],n,m,h,ty;
struct Data_Maker{
	long long Seed,a,b,c,MOD;
	long long Random() {
		c++;
		Seed=(Seed*a+b*c)%MOD;
		return Seed;
	}
	int Random_int() {
		int tmp=Random();
		if(Random()&1)tmp*=-1;
		return tmp;
	}
	void MAKE(){
		scanf("%lld%lld%lld%lld%lld",&Seed,&a,&b,&c,&MOD);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				A[i][j]=Random_int();
	}
}maker;
struct P100{
	LL sum[2][M][M];
	LL calc(int x1,int y1,int x2,int y2){
		if(y1<y2)return sum[0][x2][y2]-sum[0][x1-1][y1-1];
		return sum[1][x2][y2]-sum[1][x1-1][y1+1];
	}
	LL ans[M][M],Ans;
	void solve(){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				sum[0][i][j]=sum[0][i-1][j-1]+A[i][j];
				sum[1][i][j]=sum[1][i-1][j+1]+A[i][j];
				if(abs(i-(h+1))+abs(j-(h+1))<=h)ans[h+1][h+1]+=A[i][j];
			}
		Ans=ans[h+1][h+1];
		for(int i=h+1;i<=n-h;i++){
			for(int j=h+1;j<=m-h;j++){
				if(i==h+1&&j==h+1)continue;
				if(j==h+1){
					ans[i][j]=ans[i-1][j];
					ans[i][j]-=calc(i-1-h,j,i-1,j-h);
					ans[i][j]-=calc(i-h,j+1,i-1,j+h);
					ans[i][j]+=calc(i,j-h,i+h,j);
					ans[i][j]+=calc(i,j+h,i+h-1,j+1);
				}
				else {
					ans[i][j]=ans[i][j-1];
					ans[i][j]-=calc(i-h,j-1,i,j-1-h);
					ans[i][j]-=calc(i+1,j-h,i+h,j-1);
					ans[i][j]+=calc(i-h,j,i,j+h);
					ans[i][j]+=calc(i+1,j+h-1,i+h,j);
				}
//				printf("%d %d %lld\n",i,j,ans[i][j]);
				Ans=max(Ans,ans[i][j]);
			}
		}
		printf("%lld\n",Ans);
	}
}p100;
bool mm2;
int main(){
	freopen("rhombus.in","r",stdin);
	freopen("rhombus.out","w",stdout);
//	printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
	scanf("%d%d%d%d",&n,&m,&h,&ty);h--;
	if(ty==0){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%d",&A[i][j]);
	}
	else maker.MAKE();
	p100.solve();
	return 0;
}
