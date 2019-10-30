#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define rep(i,a,b) for(reg int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(reg int i=a,i##end=b;i>=i##end;--i)
const int N=20;
const ll P=998244353;
int n,m;
int a[N],b[N];
ll qpow(ll x,ll k){
	ll res=1;
	for(;k;k>>=1,x=x*x%P) if(k&1) res=res*x%P;
	return res;
}
int cnt;
struct Mat{
	ll a[150][150];
	void init(){ memset(a,0,sizeof a); }
	void Get1(){ rep(i,1,cnt) a[i][i]=1; }
	Mat operator * (const Mat x) const {
		Mat res; res.init();
		rep(i,1,cnt) rep(j,1,cnt) rep(k,1,cnt) res.a[i][k]=(res.a[i][k]+a[i][j]*x.a[j][k])%P;
		return res;
	}
}x,res;
ll base;
int st,c;
vector <int> state[150],d;
map <vector <int>,int> M;
void dfs(int l,int s) {
	if(s==n) {
		cnt++;
		state[cnt]=d;
		M[state[cnt]]=cnt;
		return;
	}
	rep(i,l,n-s) d.push_back((int)i),dfs(i,s+i),d.pop_back();
}
int vis[N];
int EnCode(int a[]){
	memset(vis,0,sizeof vis);
	vector <int> d;
	rep(i,1,n) if(!vis[i]) {
		int cnt=0,x=i;
		while(!vis[x]) vis[x]=1,x=a[x],cnt++;
		d.push_back(cnt);
	}
	sort(d.begin(),d.end());
	return M[d];
}
void Pre_Make(){
	dfs(1,0);
	st=EnCode(a);
	rep(i,2,cnt) {
		c=0;
		rep(j,0,state[i].size()-1) {
			rep(k,1,state[i][j]-1) b[c+k]=c+k+1;
			b[c+state[i][j]]=c+1;
			c+=state[i][j];
		}
		rep(x,1,n) rep(y,x+1,n) rep(z,x+1,n) if(x!=y && x!=z && z!=y) {
			int t=b[x];
			b[x]=b[z],b[z]=b[y],b[y]=t;
			(::x.a[i][EnCode(b)]+=base)%=P;
			t=b[x];
			b[x]=b[y],b[y]=b[z],b[z]=t;
		}
	}
	x.a[1][1]++;
}
int main(){
	scanf("%d%d",&n,&m);
	if(m==0) return puts("0"),0;
	rep(i,1,n) scanf("%d",a+i);
	rep(i,1,n) scanf("%d",b+i);
	rep(i,1,n) rep(j,i+1,n) if(b[j]<b[i]) swap(b[j],b[i]),swap(a[j],a[i]);
	base=qpow(n*(n-1)*(n-2)/3,P-2);
	Pre_Make();
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=cnt;j++)
			printf("%d ",x.a[i][j]);
		puts("");
	}
	res.Get1();
	while(m) {
		if(m&1) res=res*x;
		x=x*x;
		m>>=1;
	}
	printf("%lld\n",res.a[st][1]);
}
