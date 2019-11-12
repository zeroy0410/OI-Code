#include<bits/stdc++.h>
#define For(a,b,c) for(int a=b;a<=c;++a)
using namespace std;
const int N=500007;
int n,A[N],B[N],G[N],S[4],D[4],C[4],sz[4],mn[4],V[4];
int fi(int u) {
	return u==C[u]?u:C[u]=fi(C[u]);
}
void uni(int x,int y,int z) {
	x=fi(x),y=fi(y);
	if(x!=y) {
		C[x]=y;
		sz[y]+=sz[x];
		V[y]+=V[x]+z;
		mn[y]=min(z,min(mn[y],mn[x]));
	}
	else {
		V[x]+=z;
		mn[x]=min(mn[x],z);
	}
}
int main() {
	freopen("cake.in","r",stdin);
	freopen("cake.out","w",stdout);
	scanf("%d",&n);
	For(i,1,n) {
		char a[9],b[9];
		scanf("%d%s%s",&G[i],a,b);
		A[i]=*a-'W',B[i]=*b-'W';
	}
	For(i,0,3) sz[i]=1,C[i]=i,mn[i]=999999999;
	For(i,1,n) {
		int a=A[i],b=B[i],x=G[i];
		if(a==b) {
			S[a]+=x;
			continue;
		}
		++D[a],++D[b];
	}
	For(i,1,n) {
		int a=A[i],b=B[i],x=G[i];
		if(a==b) continue;
		if(D[a]==1) x+=S[a],S[a]=0;
		if(D[b]==1) x+=S[b],S[b]=0;
		uni(a,b,x);
	}
	For(i,0,3) V[fi(i)]+=S[i];
	int w=0,ans=0;
	For(i,0,3)
		if(D[i]&1) ++w;
	For(i,0,3)
		if(fi(i)==i) {
			if(sz[i]==4&&w==4) ans=max(ans,V[i]-mn[i]);
			else ans=max(ans,V[i]);
		}
	printf("%d",ans);
	return 0;
}

