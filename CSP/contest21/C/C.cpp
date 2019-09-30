#include<cstdio>
#include<iostream>
using namespace std;
int A[20][20],n,m;
bool check(int *T,int l){
	bool f1=0,f2=0;
	for(int i=1;i<l;i++)
		if(T[i]<T[i-1])f1=1;
		else f2=1;
	if(f1&&f2)return 0;
	return 1;
}
int tmp[20],B[20];
int dp[20][2],ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			scanf("%d",&A[i][j]);
	for(int i=1;i<1<<n;i++){
		int l=0,bcnt=0;
		for(int j=0;j<m;j++){
			for(int r=0;r<n;r++)
				if(i&1<<r)tmp[l++]=A[r][j];
			if(check(tmp,l))B[bcnt++]=j;
		}
		ans+=bcnt;
		for(int j=0;j<bcnt;j++){
			int s=0;
			for(int r=0;r<bcnt;r++){
				
			}	
		}
	}
	return 0;
}
