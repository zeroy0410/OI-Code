#include<bits/stdc++.h>
using namespace std;
const int mod=152076289;
int n,m,K;
struct Pbl{
	int Ma[15][15],A[15];
	int get(int x){
		if(x<0)return -1;
		if(x>0)return 1;
		return 0;
	}
	int get_v(){
		int res=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				res=(res*233+Ma[i][j])%19260817;
		return res;
	}
	set<int>S;
	void dfs(int x){
		if(x>n){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					Ma[i][j]=get(A[i]-A[j])*min(abs(A[i]-A[j]),K);
				}
			}
			S.insert(get_v());
			return;
		}
		for(int i=0;i<=m;i++){
			A[x]=i;
			dfs(x+1);
		}
	}
	void solve(){
		dfs(1);
		printf("%d\n",(int)S.size());
	}
}pbl;
int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	if(n<=5&&m<=5&&K<=5)pbl.solve();
	return 0;
}
