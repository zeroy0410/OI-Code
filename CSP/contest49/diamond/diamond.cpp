#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
int T,n;
int get(int x){
	int a=0,b=0;
	while(x){
		int t=x%10;
		x/=10;
		if(t&1)a+=t;
		else b+=t;
	}
	return abs(a-b);
}
LL sum[M<<1];
LL ans[M];
int main(){
	freopen("diamond.in","r",stdin);
	freopen("diamond.out","w",stdout);
	scanf("%d",&T);
	for(int i=1;i<M*2;i++)
		sum[i]=sum[i-1]+get(i);
	ans[1]=2;
	for(int i=1;i<M;i++){
		int st=i+1,ed=i+i;
		ans[i]=ans[i-1]+sum[ed]-sum[st-1]+sum[ed-1]-sum[st-1];
	}
	while(T--){
		scanf("%d",&n);
		printf("%lld\n",ans[n]);
	}
	return 0;
}
