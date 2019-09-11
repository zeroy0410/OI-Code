#include<bits/stdc++.h>
#define LL long long
#define M 50005
using namespace std;
int n,s;
struct node{
	int id,v;
	bool operator < (const node& res)const{
		if(v!=res.v)return v<res.v;
		return id<res.id;
	}
}A[M];
struct que{
	int a,b,c;
}G[M<<1];
int gcnt=0;
int main(){
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i].v);
		A[i].id=i;
	}
	sort(A+1,A+n+1);
	int las=1;
	for(int i=2;i<=n;i++){
		if(las==-1||A[i].v-A[las].v>s||A[i].v-A[las].v==0){
			puts("-1");
			return 0;
		}
		else {
			G[++gcnt]=(que){A[las].id,A[i].id,A[i].v-A[las].v};
		}
		if(A[i].v!=A[i+1].v)las=i;
	}
	printf("%d\n",gcnt);
	for(int i=1;i<=gcnt;i++){
		printf("%d %d %d\n",G[i].a,G[i].b,G[i].c);
	}
	return 0;
}