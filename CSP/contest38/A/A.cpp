#include<bits/stdc++.h>
#define uint unsigned int
#define LL unsigned long long
using namespace std;
int K,T,inc[2005];
LL L,R;
LL pf(LL x){return x*x;}
uint ans;
LL sum;
int S[65];
uint h(LL x){
	return (pf(x%20000116)+x+804)/233;
}
int main(){
	freopen("fantasy.in","r",stdin);
	freopen("fantasy.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d%lld%lld",&K,&L,&R);
		ans=sum=0;
		for(int i=0;i<K;i++)inc[i]=i+1;
		inc[K-1]=0;
		LL tmp=L;
		for(int i=0;i<60;i++){
			sum+=(S[i]=tmp%K);
			tmp/=K;
		}
		sum%=K;
		for(tmp=L;tmp<=R;tmp++){
			ans=ans+sum*h(tmp);
			sum=inc[sum];
			S[0]++;
			for(int i=0;S[i]==K;i++)
				S[i]=0,S[i+1]++,sum=inc[sum];
		}
		printf("%u\n",ans);
	}
	return 0;
}
