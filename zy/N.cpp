#include<bits/stdc++.h>
#define M 3005
using namespace std;
int T,n,m,h[M],tt;
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1,a,b;i<=m;i++){
			scanf("%d%d",&a,&b);
			Add(a,b);Add(b,a);
		}
	}
	return 0;
}
