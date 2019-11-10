#include<bits/stdc++.h>
using namespace std;
const int P=1e9+7;
long long Pow(long long a,int b){
	long long res=1;
	for(;b;b>>=1,a=a*a%P)
		if(b&1)res=res*a%P;
	return res;
}
int ans[10][10];
int main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	ans[1][1]=2;
	ans[1][2]=4;
	ans[2][2]=12;
	ans[2][3]=36;
	ans[3][3]=112;
	ans[3][4]=336;
	ans[4][4]=912;
	ans[4][5]=2688;
	ans[5][5]=7136;
	ans[5][6]=21312;
	ans[6][6]=56768;
	ans[6][7]=170112;
	ans[7][7]=453504;
	ans[7][8]=1360128;
	ans[8][8]=3626752;
	ans[8][9]=10879488;
	int n,m;
	scanf("%d%d",&n,&m);
	if(n>m)swap(n,m);
	if(n==m)printf("%d\n",ans[n][m]);
	else if(n==1)printf("%lld\n",ans[n][n+1]*Pow(2,m-n-1)%P);
	else printf("%lld\n",ans[n][n+1]*Pow(3,m-n-1)%P);
	return 0;
}

