#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int f[110][110][2];
char s[110];
int n;
bool check(int l,int r){
	int mid=(l+r)/2;
	for(int i=1;i<=mid-l+1;i++)if(s[l+i-1]!=s[mid+i])return 0;
	return 1;
}
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=n;i;i--)
		for(int j=i;j<=n;j++){
			f[i][j][0]=f[i][j][1]=j-i+1;
			for(int k=i;k<j;k++)f[i][j][1]=min(f[i][j][1],min(f[i][k][0],f[i][k][1])+1+min(f[k+1][j][1],f[k+1][j][0]));
			for(int k=i;k<j;k++)f[i][j][0]=min(f[i][j][0],f[i][k][0]+j-k);
			if((j-i+1)%2==0&&check(i,j))f[i][j][0]=f[i][(i+j)/2][0]+1;
		}
	cout<<min(f[1][n][0],f[1][n][1])<<endl;
	return 0;
}