#include<bits/stdc++.h>
#define M 10000005
#define LL unsigned long long
using namespace std;
const int mod=1e9+7;
const int P=19260817;
char S[M],T[M];
LL has[2][M],f[M];
LL Pow[M];
void Init(char *s,int len,bool f){
	for(int i=1;i<=len;i++)
		has[f][i]=has[f][i-1]*P+s[i]-'a'+1;
}
int n,m;
map<LL,LL>mp;
int main(){
	scanf("%s%s",S+1,T+1);mp.clear();
	n=strlen(S+1);m=strlen(T+1);
	Init(S,n,0);Init(T,m,1);
	Pow[0]=1;for(int i=1;i<=max(n,m);i++)Pow[i]=Pow[i-1]*P;
	for(int i=0;i<=m;i++)mp[(has[1][m]-has[1][i]*Pow[m-i])*Pow[i]+has[1][i]]++;
	for(int i=1;i+m-1<=n;i++)if(mp.count(has[0][i+m-1]-has[0][i-1]*Pow[m]))f[i]+=mp[has[0][i+m-1]-has[0][i-1]*Pow[m]];
	LL ans=0;
    for(int i=1;i+2*m-1<=n;i++)ans=(ans+f[i]*f[i+m]%mod)%mod;
	printf("%lld\n",ans);
	return 0;
}
