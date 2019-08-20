#include<bits/stdc++.h>
using namespace std;
struct node{
	int a,b;
	bool operator < (const node& res)const{
		if(a!=res.a)return a<res.a;
		return b<res.b;
	}
};
set<node>S;
int main(){
	freopen("data.in","w",stdout);
	int n=100000,m=1000000;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=m;i++){
		int a,b;
		while(1){
			a=1LL*rand()*rand()%n+1;
			b=1LL*rand()*rand()%n+1;
			if(a>b)swap(a,b);
			if(a==b)continue;
			if(S.find((node){a,b})!=S.end())continue;
			S.insert((node){a,b});
			printf("%d %d\n",a,b);
			break;
		}
	}
	return 0;
}
