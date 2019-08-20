#include<bits/stdc++.h>
#define M 100005
using namespace std;
bool mm1;
int n;
char A[25];
map<long long,int>mp;
int get(char c){
	if(c=='A')return 1;
	if(c=='C')return 2;
	if(c=='G')return 3;
	if(c=='T')return 4;
}
char rev(char c){
	if(c=='A')return 'T';
	if(c=='C')return 'G';
	if(c=='G')return 'C';
	if(c=='T')return 'A';
}
bool mm2;
int main(){
	// printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
	scanf("%d",&n);
	int ans=0;
	for(int i=1;i<=n;i++){
		scanf("%s",A+1);
		int l=strlen(A+1);
		long long res1=0,res2=0;
		for(int j=1;j<=l;j++){
			res1=res1*5+get(A[j]);
			res2=res2*5+get(rev(A[j]));
		}
		// puts(A+1);
		if(mp[res2]){
			mp[res2]--;
			ans++;
		}
		else mp[res1]++;
	}
	printf("%d\n",ans);
	return 0;
}