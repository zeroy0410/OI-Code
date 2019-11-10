#include<bits/stdc++.h>
#define M 5005
using namespace std;
int n,m;
char S[M][M];
struct P30{
	int id(int x,int y){
		return x*m+y;
	}
	int ans,rt;
	void solve(){
		ans=-1;
		for(int i=0;i<(1<<(n*m));i++){
			for(int j=0;j<n;j++)
				for(int k=0;k<m;k++)
					if(i&1<<id(j,k))S[j][k]='(';
					else S[j][k]=')';
			int res=0;
			for(int j=0;j<n;j++){
				int c=0;bool fl=1;
				for(int k=0;k<m;k++)
					if(S[j][k]=='(')c++;
					else {
						c--;
						if(c<0){
							fl=0;
							break;
						}
					}
				if(c!=0)fl=0;
				res+=fl;
			}
			for(int k=0;k<m;k++){
				int c=0;bool fl=1;
				for(int j=0;j<n;j++)
					if(S[j][k]=='(')c++;
					else {
						c--;
						if(c<0){
							fl=0;
							break;
						}
					}
				if(c!=0)fl=0;
				res+=fl;
			}
			if(res>ans)ans=res,rt=i;
		}
		for(int j=0;j<n;j++)
			for(int k=0;k<m;k++)
				if(rt&1<<id(j,k))S[j][k]='(';
				else S[j][k]=')';
		for(int j=0;j<n;j++){
			for(int k=0;k<m;k++)
				printf("%c",S[j][k]);
			puts("");
		}
	}
}p30;
struct Pn1{
	void solve(){
		for(int i=0;i<n;i++){
			for(int j=0;j<m/2;j++)
				printf("(");
			for(int j=m/2;j<m;j++)
				printf(")");
			puts("");
		}
	}
}pn1;
struct Pm1{
	void solve(){
		for(int i=0;i<n/2;i++){
			for(int j=0;j<m;j++)
				printf("(");
			puts("");
		}
		for(int i=n/2;i<n;i++){
			for(int j=0;j<m;j++)
				printf(")");
			puts("");
		}
	}
}pm1;
struct P100{
	void out(int sw){
		if(!sw){
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++)
					printf("%c",S[i][j]);
				puts("");
			}
		}
		else {
			for(int j=0;j<m;j++){
				for(int i=0;i<n;i++)
					printf("%c",S[i][j]);
				puts("");
			}
		}
	}
	bool sw;
	void solve2(){
		S[0][0]=S[n-1][m-1]=S[0][m-1]=S[n-1][0]='(';
		for(int i=0;i<m;i++){
			S[0][i]='(';S[n-1][i]=')';
		}
		for(int i=0;i<n;i++){
			S[i][0]='(';S[i][m-1]=')';
		}
		for(int i=1;i<n-1;i++){
			for(int j=1;j<m-1;j++){
				if((i+j)&1)S[i][j]=')';
				else S[i][j]='(';
			}
		}
		out(sw);
	}
	void solve1(){
		for(int i=0;i<n/2;i++){
			for(int j=0;j<m/2;j++)
				S[i][j]='(';
			for(int j=m/2;j<m;j++)
				S[i][j]=')';
		}
		for(int i=n/2;i<n;i++){
			for(int j=0;j<m;j++)
				if(j&1)S[i][j]=')';
				else S[i][j]='(';
		}
		out(sw);
	}
	void solve(){
		sw=0;
		if(n<m){swap(n,m);sw=1;}
		if(n+m/2-1>n+m-4)solve1();
		else solve2();
	}
}p100;
int main(){
	freopen("butterfly.in","r",stdin);
	freopen("butterfly.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(n&1)pn1.solve();
	else if(m&1)pm1.solve();
	else if(n*m<=18)p30.solve();
	else p100.solve();
	return 0;
}
