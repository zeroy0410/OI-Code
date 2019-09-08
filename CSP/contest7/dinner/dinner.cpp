#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL P,ans;
int f[1<<8][1<<8],p[2][1<<8][1<<8];
int pri[8]={2,3,5,7,11,13,17,19},n;
struct node{int x,S;}A[505];
bool cmp(node a,node b){
	if(a.x!=b.x)return a.x<b.x;
	return a.S<b.S;
}
template<typename T,typename TT>
void Add(T &x,TT y){
	x+=y;
	if(x>=P)x-=P;
}
int main(){
	scanf("%d%lld",&n,&P);
	for(int i=2;i<=n;i++){
		int tmp=i;
		for(int j=0;j<8;j++)
			if(tmp%pri[j]==0){
				A[i].S|=(1<<j);
				while(tmp%pri[j]==0)
					tmp/=pri[j];
			}
		A[i].x=tmp;
	}
	sort(A+2,A+n+1,cmp);
	f[0][0]=1;
	for(int i=2;i<=n;i++){
		if(i==2||A[i].x==1||A[i].x!=A[i-1].x){
			memcpy(p[0],f,sizeof(f));
			memcpy(p[1],f,sizeof(f));
		}
		for(int j=255;j>=0;j--)
			for(int k=255;k>=0;k--){
				if((k&A[i].S)==0)Add(p[0][j|A[i].S][k],p[0][j][k]);
				if((j&A[i].S)==0)Add(p[1][j][k|A[i].S],p[1][j][k]);
			}
		if(i==n||A[i].x==1||A[i].x!=A[i+1].x){
			for(int j=0;j<=255;j++)
				for(int k=0;k<=255;k++)
					f[j][k]=((p[0][j][k]+p[1][j][k]-f[j][k])%P+P)%P;
		}
	}
	for(int i=0;i<=255;i++)
		for(int j=0;j<=255;j++)
			Add(ans,f[i][j]);
	printf("%lld\n",ans);
	return 0;
}
