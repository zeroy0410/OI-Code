#include<bits/stdc++.h>
#define rint register int
using namespace std;
const int mod=1e9+7;
const int base=(1<<27)-1;
int n,k,l,A[30];
int C[61][61],gc[30][30];
char cnt[1<<27|5],can[1<<27|5],bin[1<<27|5];
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
void init(){
	for(int i=1;i<=27;i++)
		for(int j=1;j<=27;j++)
			gc[i][j]=gcd(i,j);
	for(rint i=0;i<=60;i++)
		for(rint j=0;j<=i;j++)
			if(j==0||j==i)C[i][j]=1;
			else C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	can[0]=1;
	for(rint i=0;i<27;i++)can[1<<i]=1,bin[1<<i]=i;
	for(rint i=1;i<=base;i++){
		cnt[i]=cnt[i&(i-1)]+1;
		if(can[i]!=1)continue;
		int tmp[30],len=0;
		for(rint ii=i;ii;ii&=ii-1)tmp[++len]=bin[ii&-ii];
		for(rint j=tmp[len]+1;j<27;j++){
			int s=i|(1<<j);
			if(can[s])continue;
			bool f=1;
			for(rint q=1;f&&q<=len;q++)if((1<<(gc[j+1][tmp[q]+1]-1))&~s)f=0;
			can[s]=f?1:-1;
		}
	}
}
int main(){
	init();
	for(int _=(scanf("%d",&_),_);_;_--){
		scanf("%d%d%d",&n,&k,&l);
		int st=0;
		for(rint i=1;i<=n;i++){
			scanf("%d",&A[i]);st|=1<<(A[i]-1);
		}
		int cn=cnt[st],ss=st;
		for(rint i=1;i<=n;i++)
			for(rint j=i+1;j<=n;j++)
				if((1<<(gc[A[i]][A[j]]-1))&~ss)
					ss|=1<<(gc[A[i]][A[j]]-1);
		long long ans=0;
		for(int i=ss,ed=(1<<l);i<ed;i=(i+1)|ss)if(can[i]==1&&cnt[i]<=cn+k)ans+=C[cn+k-1][cnt[i]-1];
		printf("%lld\n",ans%mod);
	}
	return 0;
}
