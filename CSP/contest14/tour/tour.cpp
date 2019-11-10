#include<stdio.h>
#include<algorithm>
#include<bitset>
#define M 1505
using namespace std;
int n;
bitset<M>G[M],tmp;
char S[M];
int cnt[M];
int main(){
	freopen("tour.in","r",stdin);
	freopen("tour.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",S+1);
		for(int j=1;j<=n;j++)
			if(S[j]=='1')G[i][j]=1,cnt[i]++;
	}
	long long ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(!G[i][j])continue;
			ans=ans+1LL*(cnt[i]-1)*(cnt[j]-1);
			tmp=(G[i]&G[j]);
			ans=ans-tmp.count();
		}
	}
	printf("%lld\n",ans*2);
	return 0;
}
