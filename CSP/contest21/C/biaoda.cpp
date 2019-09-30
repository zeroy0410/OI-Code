#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,A[25][25],B[25][25];
struct P55{
	bool check(int c1,int c2){
		for(int i=0;i<c1;i++){
			bool f1=0,f2=0;
			for(int j=1;j<c2;j++){
				if(B[i][j]>B[i][j-1])f1=1;
				else f2=1;
			}
			if(f1&&f2)return 0;
		}
		for(int j=0;j<c2;j++){
			bool f1=0,f2=0;
			for(int i=1;i<c1;i++){
				if(B[i][j]>B[i-1][j])f1=1;
				else f2=1;
			}
			if(f1&&f2)return 0;
		}
//		for(int i=0;i<c1;i++){
//			for(int j=0;j<c2;j++)
//				printf("%d ",B[i][j]);
//			puts("");
//		}
//		puts("");
		return 1;
	}
	void solve(){
		int ans=0;
		for(int i=1;i<(1<<n);i++){
			for(int j=1;j<(1<<m);j++){
				int c1=0,c2=0;
				for(int r=0;r<n;r++){
					if(!(i&1<<r))continue;
					c2=0;
					for(int h=0;h<m;h++){
						if(!(j&1<<h))continue;
						B[c1][c2++]=A[r][h];
					}
					c1++;
				}
				if(check(c1,c2))ans++;
			}
		}
		printf("%d\n",ans);
	}
}p55;
struct P100{
	int Q[25];
	void solve(){
		int ans=0;
		for(int i=1;i<1<<m;i++){
			int ct=0;
			for(int j=0;j<n;j++){
				int c=0;
				for(int k=0;k<m;k++){
					if(i&1<<k)
						Q[c++]=A[j][k];
				}
				bool f1=0,f2=0;
				for(int i=1;i<c;i++)
					if(Q[i]>Q[i-1])f1=1;
					else f2=1;
				if(f1&&f2)continue;
				ct++;
			}
			ans+=1<<ct;
			if(ct==n)ans--;
		}
		printf("%d\n",ans);
	}
}p100;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			scanf("%d",&A[i][j]);
	p55.solve();
	return 0;
}
