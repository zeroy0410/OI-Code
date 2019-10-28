#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n,K,A[M],pc;
const LL inf=1e10;
LL po[M],pos[M];
bool mark[M];
const int mod1=998244353,mod2=1e9+7;
void Init(){
	for(int i=2;i<M;i++){
		if(!mark[i])po[++pc]=i,pos[i]=pc;
		for(int j=i+i;j<M;j+=i)
			mark[j]=1;
	}
}
struct node{
	LL x,y;
	bool operator < (const node& res)const{
		if(x!=res.x)return x<res.x;
		return y<res.y;
	}
};
map<node,int>mp;
LL Pow1[M],Pow2[M];
int main(){
	Init();
	scanf("%d%d",&n,&K);mp.clear();
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	Pow1[0]=Pow2[0]=1;
	for(int i=1;i<M;i++)Pow1[i]=Pow1[i-1]*233%mod1;
	for(int i=1;i<M;i++)Pow2[i]=Pow2[i-1]*233%mod2;
	LL ans=0;
	for(int i=1;i<=n;i++){
		int x=A[i];LL res=0,res2=0,res3=0,res4=0;
		for(int j=1;j<=pc&&po[j]*po[j]<=x;j++){
			int ct=0;
			if(x%po[j]==0){
				while(x%po[j]==0){x/=po[j];ct++;}
			}
			ct=ct%K;
			res=(res+Pow1[j]*ct%mod1)%mod1;
			res2=(res2+Pow1[j]*((K-ct)%K)%mod1)%mod1;
			res3=(res3+Pow2[j]*ct%mod2)%mod2;
			res4=(res4+Pow2[j]*((K-ct)%K)%mod2)%mod2;
		}
		if(x!=1){
			int j=pos[x];
			int ct=1;
			res=(res+Pow1[j]*ct%mod1)%mod1;
			res2=(res2+Pow1[j]*((K-ct)%K)%mod1)%mod1;
			res3=(res3+Pow2[j]*ct%mod2)%mod2;
			res4=(res4+Pow2[j]*((K-ct)%K)%mod2)%mod2;
		}
		node t=(node){res2,res4};
		ans+=mp[t];
		t=(node){res,res3};
		mp[t]++;
	}
	printf("%lld\n",ans);
	return 0;
}
