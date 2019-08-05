 #include<bits/stdc++.h>
#define debug(x) cerr<<"\tDEBUG: "<<#x<<" = "<<(x)<<endl
#define debug2(a,x) cerr<<#a<<"\tDEBUG: "<<#x<<" = "<<(x)<<endl
using namespace std;
const int maxn=1e5+100,maxm=maxn*40;
int n,m,K;
int tot,head[maxn],to[maxn],nxt[maxn];
void add_edge(int u,int v){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
map<int,long long>val[maxn];
map<int,long long>::iterator it;
struct node{
	int d;
	long long w;
};
vector<node>T[maxn];
int rt[maxn],lson[maxm],rson[maxm];
long long mx[maxm],lazy[maxm];
void add(int p,long long d){
	if(!p)return;
	mx[p]+=d;
	lazy[p]+=d;
}
void down(int p){
	if(lazy[p]){
		add(lson[p],lazy[p]);
		add(rson[p],lazy[p]);
		lazy[p]=0;
	}
}
void up(int p){
	mx[p]=max(mx[lson[p]],mx[rson[p]]);
}
void insert(int &rt,int l,int r,int x,long long val){
	if(!rt)rt=++tot;
	if(l==r){
		mx[rt]=val;
		return;
	}
	down(rt);
	int mid=l+r>>1;
	if(x<=mid){
		insert(lson[rt],l,mid,x,val);
	}else insert(rson[rt],mid+1,r,x,val);
	up(rt);
}
int Merge(int a,int b,int l,int r,long long Maxa,long long Maxb){
	if(!a&&!b)return 0;
	if(!a){
		add(b,Maxa);
		return b;
	}else if(!b){
		add(a,Maxb);
		return a;
	}
	if(l==r){
		mx[a]=max(mx[a],Maxa)+max(mx[b],Maxb);
		return a;
	}else {
		down(a);down(b);
		int mid=l+r>>1;
		rson[a]=Merge(rson[a],rson[b],mid+1,r,max(Maxa,mx[lson[a]]),max(Maxb,mx[lson[b]]));
		lson[a]=Merge(lson[a],lson[b],l,mid,Maxa,Maxb);
		up(a);
		return a;
	}
}
long long Query(int rt,int l,int r,int L,int R){
	if(!rt||l==L&&r==R)return mx[rt];
	down(rt);
	int mid=l+r>>1;
	if(R<=mid)return Query(lson[rt],l,mid,L,R);
	else if(L>mid)return Query(rson[rt],mid+1,r,L,R);
	else return max(Query(lson[rt],l,mid,L,mid),Query(rson[rt],mid+1,r,mid+1,R));
}
void dfs(int x){
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];
		dfs(y);
		rt[x]=Merge(rt[x],rt[y],1,K,0,0);
	}
	for(int i=0;i<T[x].size();i++){
		T[x][i].w+=Query(rt[x],1,K,1,T[x][i].d);
	}
	for(int i=0;i<T[x].size();i++){
		insert(rt[x],1,K,T[x][i].d,T[x][i].w);
	}
}
int main(){
	cin>>n>>m>>K;
	for(int i=2,x;i<=n;i++){
		scanf("%d",&x);
		add_edge(x,i);
	}
	for(int i=1,v,d,w;i<=m;i++){
		scanf("%d%d%d",&v,&d,&w);
		val[v][d]+=w;
	}
	for(int i=1;i<=n;i++){
		for(it=val[i].begin();it!=val[i].end();it++){
			T[i].push_back((node){(*it).first,(*it).second});
		}
	}
	dfs(1);
	cout<<Query(rt[1],1,K,1,K)<<endl;
    return 0;
}
