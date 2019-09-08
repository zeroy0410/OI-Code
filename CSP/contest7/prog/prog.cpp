#include<bits/stdc++.h>
#define M 100005
using namespace std;
int T,n;
int B[M<<1],bcnt;
struct que{
	int a,b,c;
}Q[M];
int fa[M<<2];
int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
bool check(){
	for(int i=1;i<=2*bcnt;i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		Q[i].a=lower_bound(B+1,B+bcnt+1,Q[i].a)-B;
		Q[i].b=lower_bound(B+1,B+bcnt+1,Q[i].b)-B;
		if(Q[i].c)
			fa[getfa(Q[i].a)]=getfa(Q[i].b);
	}
	for(int i=1;i<=n;i++)
		if(!Q[i].c&&getfa(Q[i].a)==getfa(Q[i].b))return 0;
	return 1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		bcnt=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d%d%d",&Q[i].a,&Q[i].b,&Q[i].c);
			B[++bcnt]=Q[i].a;B[++bcnt]=Q[i].b;
		}
		sort(B+1,B+bcnt+1);
		bcnt=unique(B+1,B+bcnt+1)-B-1;
		if(check())puts("YES");
		else puts("NO");
	}
	return 0;
}
