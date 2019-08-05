#include<bits/stdc++.h>
#define M 100005
using namespace std;
struct node{
	int op,t;
}A[M];
int n,m;
char S[15];
struct P100{
	int res[35][2],ans,now;
   	int Init(int pos,int st){
		for(int i=1;i<=n;i++){
			if(A[i].op==1)st=(st&(A[i].t>>pos&1));
			else if(A[i].op==2)st=(st|(A[i].t>>pos&1));
			else st=(st^(A[i].t>>pos&1));
		}
		return st;
	}
	void solve(){
		ans=0;now=0;
 		for(int i=0;i<30;i++){
			res[i][0]=Init(i,0);
			res[i][1]=Init(i,1);
		}
		for(int i=29;i>=0;i--){
			if(res[i][1]>res[i][0]){
				if((now|1<<i)<=m){
					cout<<i<<endl;
					ans|=1<<i;
					now|=1<<i;
				}
			}
			else if(res[i][0])ans|=1<<i;
		}
		printf("%d\n",ans);
	}
}p100;
int main(){
	freopen("sleep.in","r",stdin);
	freopen("sleep.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s%d",S+1,&A[i].t);
		if(S[1]=='A')A[i].op=1;
		else if(S[1]=='O')A[i].op=2;
		else A[i].op=3;
	}
	p100.solve();
	return 0;
}
