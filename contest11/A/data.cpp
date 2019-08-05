#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("dmngp.in","w",stdout);
	int n=8,m=8;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			printf(".");
		puts("");
	}
	return 0;
}
while(top[u]!=top[v]){
			if(dep[top[u]]>dep[top[v]]){
				query(ID[top[u]],ID[u],1);
				u=fa[top[u]];
			}
			else {
				query(ID[top[v]],ID[v],1);
				v=fa[top[v]];
			}
		} 
		if(dep[u]>dep[v])query(ID[v],ID[u],1);
		else query(ID[u],ID[v],1);
