#include<cstdio>
#include<algorithm>
#define M 1005
using namespace std;
int n,m,h[M],tt;
struct edge{
	int nxt,to,co;
}G[M*10];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
void dfs(int x,int f){

}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,a,b,c;i<=n;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
	}

	return 0;
}
