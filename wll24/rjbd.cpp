#include <bits/stdc++.h>
using namespace std;
int n,m,b1[105],b2[105],t[105],f1[105],f2[105],dis[2000000];
char s1[25],s2[25];
bool book[2000000];
queue<int>que;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%s%s",&t[i],s1,s2);
		for(int j=0;j<n;j++)
			if(s1[j]=='+')b1[i]|=(1<<j);
			else if(s1[j]=='-')b2[i]|=(1<<j);
		for(int j=0;j<n;j++)
			if(s2[j]=='-')f1[i]|=(1<<j);
			else if(s2[j]=='+')f2[i]|=(1<<j);
	}
	memset(dis,127,sizeof(dis)),dis[(1<<n)-1]=0;
	que.push((1<<n)-1),book[(1<<n)-1]=1;
	while(!que.empty()){
		int F=que.front();que.pop(),book[F]=0;
		for(int i=1,nxt;i<=m;i++)if((F&b1[i])==b1[i]&&!(F&b2[i]))
			if(nxt=(F&(~f1[i]))|f2[i],dis[nxt]>dis[F]+t[i]){
				dis[nxt]=dis[F]+t[i];
				if(!book[nxt])que.push(nxt),book[nxt]=1;
			}
	}
	if(dis[0]>2e9)puts("0");
	else printf("%d\n",dis[0]);
	return 0;
}