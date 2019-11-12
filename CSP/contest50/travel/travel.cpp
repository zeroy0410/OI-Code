#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,m,h[M],tt;
struct edge{
	int nxt,to,co;
}G[M<<1];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
int main(){
//	freopen("travel.in","r",stdin);
//	freopen("travel.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,a,b,c;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
	}
	p20.solve();
	return 0;
}
