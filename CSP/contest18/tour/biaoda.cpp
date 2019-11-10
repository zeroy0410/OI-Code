#include <bits/stdc++.h>
#define M 1000010
#define P 998244353
using namespace std;
int pr[M],Head[M],Next[M],Go[M],D[M],Val[M],Cnt,n,m,ans;
int getf(int x){return pr[x]==x?x:pr[x]=getf(pr[x]);}
void addedge(int x, int y, int z) {
    Go[++Cnt]=y;
    Next[Cnt]=Head[x];
    Head[x]=Cnt;
    Val[Cnt]=z;
}
void DFS(int x,int f=0,int v=0){
	for(int T=Head[x];T;T=Next[T])
		if(Go[T]!=f)DFS(Go[T],x,Val[T]);
	if(D[x])D[x]^=1,D[f]^=1,ans=(ans+v)%P;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)pr[i]=i;
    for(int i=1,v=2;i<=m;i++,v=v*2%P){
        int a,b;
        scanf("%d%d",&a,&b);
        if(getf(a)!=getf(b)){
            addedge(a,b,v);
            addedge(b,a,v);
            pr[getf(a)]=getf(b);
        }
        D[a]^=1,D[b]^=1;
        ans=(ans+v)%P;
    }
    DFS(1);
    printf("%d\n",(ans%P+P)%P);
    return 0;
}
