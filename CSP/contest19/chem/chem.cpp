#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<iostream>
#define M 100005
using namespace std;
int n,h[M],tt;
string tqz[21]={"",
"meth",
"eth",
"prop",
"but",
"pent",
"hex",
"hept",
"oct",
"non",
"dec",
"undec",
"dodec",
"tridec",
"tetradec",
"pentadec",
"hexadec",
"heptadec",
"octadec",
"nonadec",
"icos"};
string qdj[21]={"","",
"di",
"tri",
"tetra",
"penta",
"hexa",
"hepta",
"octa",
"nona"};
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int in[M];
int mxdis,rt;
void dfs(int x,int f,int w){
	if(w>mxdis){mxdis=w;rt=x;}
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x,w+1);
	}
}
int main(){
	freopen("chem.in","r",stdin);
	freopen("chem.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
		in[a]++;in[b]++;
	}
	bool isl=1;int c=0;
	for(int i=1;i<=n;i++){
		if(in[i]==1)c++;
		if(in[i]!=1&&in[i]!=2)isl=0;
	}
	if(c!=2)isl=0;
	if(isl||n==1)cout<<tqz[n]<<"ane"<<endl;
	else {
		mxdis=0;dfs(1,0,0);
		int st=rt;mxdis=0;dfs(rt,0,0);
	}
	return 0;
}
