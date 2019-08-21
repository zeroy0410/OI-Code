#include<bits/stdc++.h>
#define M 100005
using namespace std;
struct FHQ_treap{
	int ch[M][2],val[M],sz[M],tot;
	int rt;
	void up(int p){sz[p]=sz[ch[p][0]]+sz[ch[p][1]]+1;}
	int new_node(int v){
		val[++tot]=v;
		sz[tot]=1;
	}
	void split(int now,int v,int &x,int &y){
		if(!now)x=y=0;
		else {
			if(val[now]<=v){
				x=now;
				split(ch[now][1],v,ch[now][1],y);
			}
			else {
				y=now;
				split(ch[now][0],v,x,ch[now][0]);
			}
			up(now);
		}
	}
	int merge(int x,int y){
		if(!x||!y)return x+y;
		if(rand()&1){
			ch[x][1]=merge(ch[x][1],y);
			up(x);
			return x;
		}
		else {
			ch[y][0]=merge(x,ch[y][0]);
			up(y);
			return y;
		}
	}
	void insert(int v){
		int x,y;
		split(rt,v,x,y);
		rt=merge(merge(x,newnode(v)),y);
	}
}Tr;
int main(){
	srand(2333);
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		Tr.insert(x);
	}
	
	return 0;
}