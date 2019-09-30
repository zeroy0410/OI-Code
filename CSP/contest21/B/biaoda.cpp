#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int M=1e6+5,mod=1e9+7,Base=233;
int n,K;
string S[M],t;
vector<int>V;
map<ull,int>Mp;
map<ull,int>::iterator it;
ull A[M];
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
int main() {
	cin>>n>>K;
	A[0]=1;A[1]=n-K+1;
	for(int i=2;i<=K;i++)
		A[i]=A[i-1]*(n+i-K)%mod;
	for(int i=1; i<=n; i++)
		cin>>S[i];
	sort(S+1,S+1+n);
	ull H;
	for(int i=1; i<=n; i++) {
		H=0;
		for(int j=0; j<S[i].size(); j++)
			H=H*Base+S[i][j];
		Mp[H]=i;
	}
	cin>>t;
	H=0;
	for(int i=0; i<t.size(); i++) {
		H=H*Base+t[i];
		if((it=Mp.find(H))!=Mp.end()){
			H=0;
			V.push_back(it->second);
		}
	}
	ull ans=0;
	for(int i=0;i<K;i++){
		int id=V[i];
		cout<<id<<endl;
		ans=(ans+(((id-1-Tr.sum(id-1))%mod)*A[K-i-1])%mod)%mod;
		Tr.add(id,1);
	}
	cout<<(ans+1)%mod<<endl;
	return 0;
}
