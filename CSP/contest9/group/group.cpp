#include<bits/stdc++.h>
#define M 2000005
using namespace std;
void read(int &x){
    char c;
    x=0;
    int f=1;
    while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
    do x=(x<<3)+(x<<1)+(c^48);
    while(c=getchar(),c>='0'&&c<='9');
    x*=f;
}
int n,m,ans[M],h[M],tt;
struct edge{
	int nxt,to;
}G[M*3];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
bool check(int x){
	int c=0;
	for(int i=h[x];i;i=G[i].nxt)if(ans[G[i].to]==ans[x])c++;
	return c>1;
}
queue<int>Q;
int main(){
	srand(19260817);
	read(n);read(m);
	for(int i=1,a,b;i<=m;i++){
		read(a);read(b);
		Add(a,b);Add(b,a);
	}
	for(int i=1;i<=n;i++)ans[i]=(rand()&1)+1;
	for(int i=1;i<=n;i++)if(check(i))Q.push(i);
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		if(!check(x))continue;
		ans[x]=3-ans[x];
		for(int i=h[x];i;i=G[i].nxt)if(check(G[i].to))Q.push(G[i].to);
	}
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}
