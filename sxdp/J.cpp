#include<cstdio>
#include<algorithm>
#define M 1005
using namespace std;
const int mod=1e9+7;
int n,h[M],tt;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int main(){
	scanf("%d",&n);
	return 0;
}
