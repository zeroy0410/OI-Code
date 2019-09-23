#include<stdio.h>
#include<algorithm>
#include<string.h>
#define LL long long
#define M 4005
using namespace std;
const int mod=1e9+7;
int a,b,c,d;
LL C[M][M],ans;
void Init(){
	C[0][0]=1;
	for(int i=1;i<M;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
}
LL calc(int x,int y){
    if(x==0)return (y==0);
    return C[x+y-1][x-1];
}
int main(){
	Init();
	scanf("%d%d%d%d",&a,&b,&c,&d);
	int e=a-c,f=b-d;
	for(int i=0;i<=e;i++)
		for(int j=0;j<=f;j++)
			ans=(ans+C[i+j][i]*calc(c,f-j)%mod*calc(d,e-i)%mod)%mod;
	ans=ans*C[c+d][c]%mod;
	printf("%lld\n",ans);
	return 0;
}
