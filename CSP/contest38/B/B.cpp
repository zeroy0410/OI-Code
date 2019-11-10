#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
struct Matrix{
	int a[155][155],n,m;
	Matrix(){memset(a,0,sizeof(a));}
	void resize(int _n,int _m){n=_n;m=_m;}
	Matrix operator * (const Matrix& res){
		Matrix ans;ans.resize(n,res.m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=res.m;j++)
				for(int k=1;k<=m;k++)
					ans.a[i][j]=(ans.a[i][j]+1LL*a[i][k]*res.a[k][j]%mod)%mod;
		return ans;
	}
}trans;
int n,m,A[25],B[25];
LL base;
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int tot;
vector<int>wk,sta[155];
map<vector<int>,int>mp;
Matrix Qkpow(Matrix a,int b){
	Matrix res;res.resize(tot,tot);
	for(int i=1;i<=tot;i++)
		res.a[i][i]=1;
	while(b){
		if(b&1)res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
void dfs(int x,int las){
	if(x==0){
		++tot;
		sta[tot]=wk;
		mp[sta[tot]]=tot;
		return;
	}
	for(int i=las;i<=x;i++){
		wk.push_back(i);
		dfs(x-i,i);
		wk.pop_back();
	}
}
bool vis[25];
int get(int *P){
	memset(vis,0,sizeof(vis));
	wk.clear();
	for(int i=1;i<=n;i++){
		int x=i,ct=1;
		if(!vis[x]){
			vis[x]=1;
			while(!vis[P[x]]){
				vis[P[x]]=1;
				x=P[x];
				ct++;
			}
			wk.push_back(ct);
		}
	}
	sort(wk.begin(),wk.end());
	return mp[wk];
}
int tmp[25];
void Init(){
	dfs(n,1);
	trans.resize(tot,tot);
	for(int i=2;i<=tot;i++){
		int ct=0;
		for(int j=0;j<(int)sta[i].size();j++){
			int u=sta[i][j];
			for(int k=1;k<=u;k++)
				tmp[ct+k]=ct+k+1;
			tmp[ct+u]=ct+1;
			ct+=u;
		}
		for(int a=1;a<=n;a++){
			for(int b=a+1;b<=n;b++){
				for(int c=a+1;c<=n;c++){
					if(a==b||a==c||b==c)continue;
					int t=tmp[a];
					tmp[a]=tmp[b]; tmp[b]=tmp[c]; tmp[c]=t;
				   	int cod=get(tmp);
					trans.a[i][cod]=(1LL*trans.a[i][cod]+base)%mod;
					tmp[c]=tmp[b]; tmp[b]=tmp[a]; tmp[a]=t;
				}
			}
		}
	}
	trans.a[1][1]++;
}
int main(){
	//freopen("goodbye.in","r",stdin);
	//freopen("goodbye.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1;i<=n;i++)scanf("%d",&B[i]);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(B[j]<B[i]){
				swap(B[j],B[i]);
				swap(A[j],A[i]);
			}
	base=qkpow(n*(n-1)*(n-2)/3,mod-2);
	Init();
//	for(int i=1;i<=tot;i++){
//		for(int j=1;j<=tot;j++)
//			printf("%d ",trans.a[i][j]);
//		puts("");
//	}
	trans=Qkpow(trans,m);
	printf("%d\n",trans.a[get(A)][1]);
	return 0;
}
