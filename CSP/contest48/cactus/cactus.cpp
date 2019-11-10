#include<bits/stdc++.h>
#define M 500005
using namespace std;
int n,m,h[M],tt;
struct edge{
	int nxt,to,id;
}G[M<<2];
void Add(int a,int b,int id){
	G[++tt]=(edge){h[a],b,id};
	h[a]=tt;
}
int main(){
//	freopen("cactus.in","r",stdin);
//	freopen("cactus.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		Add(a,b,i);Add(b,a,i);
	}
	return 0;
}
