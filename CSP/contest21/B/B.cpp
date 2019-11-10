#include<cstdio>
#include<algorithm>
#include<vector>
#include<string.h>
#include<iostream>
#define LL unsigned long long
#define M 1000005
using namespace std;
const int mod=1e9+7;
bool mm1;
int n,m;
string S[M];
char s[M],T[M];
int ch[M][26],tt;
int Val[M];
LL ans,A[M];
vector<int>wk;
struct BIT{
	int C[M];
	void add(int x,int d){
		x++;
		while(x<M){
			C[x]+=d;
			x+=(x&-x);
		}
	}
	int sum(int x){
		x++;int res=0;
		while(x){
			res+=C[x];
			x-=(x&-x);
		}
		return res;
	}
}Tr;
void Insert(string ss,int l,int d){
	int u=0;
	for(int i=0;i<l;i++){
		if(!ch[u][ss[i]-'a'])ch[u][ss[i]-'a']=++tt;
		u=ch[u][ss[i]-'a'];
	}
	Val[u]=d;
}
bool mm2;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)cin>>S[i];
	sort(S+1,S+n+1);
	for(int i=1;i<=n;i++)
		Insert(S[i],S[i].length(),i);
	A[0]=1;A[1]=n-m+1;
	for(int i=2;i<=m;i++)
		A[i]=A[i-1]*(n+i-m)%mod;
	scanf("%s",T);
	int len=strlen(T),u=0;
	for(int i=0;i<len;i++){
		if(!ch[u][T[i]-'a'])u=0;
		u=ch[u][T[i]-'a'];
		if(Val[u])wk.push_back(Val[u]);
	}
	for(int i=0;i<m;i++){
		int id=wk[i];
		ans=(ans+(((id-1-Tr.sum(id-1))%mod)*A[m-i-1])%mod)%mod;
		Tr.add(id,1);
	}
	cout<<(ans+1)%mod<<endl;
	return 0;
}
