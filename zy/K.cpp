#include<bits/stdc++.h>
#define M 1005
using namespace std;
int T,n,m,H,A[M],h[M],tt;
struct edge{
	int nxt,to;
}G[M];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int main(){
	scanf("%d",&T);
	while(T--){
		memset(h,0,sizeof(h));
		tt=0;
		scanf("%d%d",&n,&H);
		for(int i=1;i<=n;i++)
			scanf("%d",&A[i]);
		for(int i=1,x;i<=n;i++){
			scanf("%d",&x);
			for(int j=1,y;j<=x;j++){
				scanf("%d",&y);
				Add(i,y);
			}
		}

	}
	return 0;
}
