#include<bits/stdc++.h>
#define M 2005
using namespace std;
const int mod=998244353;
int n,p[M][5],w[5][5];
int main(){
//	freopen("revolution.in","r",stdin);
//	freopen("revolution.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=4;j++)
			scanf("%d",&p[i][j]);
	}
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			scanf("%d",&w[i][j]);
	
	return 0;
}
