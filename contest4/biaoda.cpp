#include<bits/stdc++.h>
using namespace std;
#define MN 2000
#define MOD 1000000007
char a[MN+5],b[MN+5],c[MN+5];
int F[MN*3+5],R[MN*3+5],z[MN+5],Z[MN+5],f[MN+5][MN*3+5],g[MN+5][MN*3+5];
inline int inv(int x){
	int y=MOD-2,r=1;
	for(;y;y>>=1,x=1LL*x*x%MOD)if(y&1)r=1LL*r*x%MOD;
	return r;
}
inline int C(int n,int m){return 1LL*F[n]*R[n-m]%MOD;}
inline void rw(int&x,int y){if((x+=y)>=MOD)x-=MOD;}
int main(){
	int n,i,j,k,l,ans;
	scanf("%d%s%s%s",&n,a+1,b+1,c+1);
	for(i=1;i<=n;++i){
		if(a[i]=='x'&&(a[i-1]!='o'||a[i+1]!='o'))return 0*puts("0");
		if(c[i]=='x'&&(c[i-1]!='o'||c[i+1]!='o'))return 0*puts("0");
	}
	for(F[0]=i=1;i<=3*n;++i)F[i]=1LL*F[i-1]*i%MOD;
	for(R[i=3*n]=inv(F[3*n]);i--;)R[i]=1LL*R[i+1]*(i+1)%MOD;
	for(i=1;i<=n;++i)Z[i]=Z[i-1]+(z[i]=(a[i]=='x')+(b[i]=='x')+(c[i]=='x'));
	ans=F[Z[n]];
	for(i=1;i<=n;i=j){
		if(b[i]=='o'){j=i+1;continue;}
		for(j=i;j<=n&&b[j]=='x';++j);
		for(k=1;k<=z[i];++k)f[i][k]=k*F[z[i]-1];g[i][1]=F[z[i]-1];
		for(k=i+1;k<j;++k){
			for(l=1;l<=Z[k-1]-Z[i-1];++l){
				rw(f[k][l+1],1LL*f[k-1][l]*C(Z[k]-Z[i-1]-l-1,z[k]-1)%MOD);
				rw(g[k][l+1],1LL*f[k-1][l]*C(Z[k]-Z[i-1]-l-1,z[k]-1)%MOD);
				rw(g[k][l],1LL*g[k-1][l]*C(Z[k]-Z[i-1]-l,z[k]-1)%MOD);
				if(z[k]==1)rw(f[k][l],g[k-1][l]);
				if(z[k]==2)rw(f[k][l],1LL*g[k-1][l]*(Z[k]-Z[i-1]-l)%MOD),
				           rw(f[k][l+1],1LL*g[k-1][l]*l%MOD);
				if(z[k]==3)rw(f[k][l],1LL*g[k-1][l]*C(Z[k]-Z[i-1]-l,2)%MOD),
				           rw(f[k][l+1],2LL*g[k-1][l]*l%MOD*(Z[k]-Z[i-1]-l-1)%MOD),
				           rw(f[k][l+2],1LL*g[k-1][l]*C(l+1,2)%MOD);
			}
			for(l=1;l<=Z[k]-Z[i-1];++l)rw(f[k][l],f[k][l-1]);
			for(l=Z[k]-Z[i-1];l;--l)rw(g[k][l],g[k][l+1]);
		}
		ans=1LL*ans*R[Z[j-1]-Z[i-1]]%MOD*f[j-1][Z[j-1]-Z[i-1]]%MOD;
	}
	printf("%d",ans);
}