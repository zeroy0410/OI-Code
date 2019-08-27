#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1e5 + 3;
pair<int,int> a[N];
int l[N],r[N],dp[N][2];
void pre(int n){
	for(int i=1;i<=n;i++)
		l[i] = r[i] = i;
	for(int i=2;i<=n;i++)
	{
		int k = i;
		while(l[k] != 1  && a[i].first-a[l[k]-1].first <= a[i].second)
			k = l[k] - 1;
		l[i] = l[k];
	}
	for(int i=n-1;i>=1;i--)
	{
		int k = i;
		while(r[k] != n  && a[r[k]+1].first-a[i].first <= a[i].second)
			k = r[k] + 1;
		r[i] = r[k];
	}
}

inline void check_min(int &a,int b){
	a = a < b ? a : b;
}

#define lson u<<1
#define rson u<<1|1

struct Seg
{
	int l,r;
	int mmin,lazy;
	inline int mid(){
		return l + r >> 1;
	}
}T[N<<2];

void build(int u,int l,int r)
{
	T[u].l = l , T[u].r = r;
	T[u].mmin = T[u].lazy = N;
	if(l == r - 1)
		return ;
	int m = T[u].mid();
	build(lson,l,m);
	build(rson,m,r);
}

void push_up(int u)
{
	T[u].mmin = min(T[lson].mmin,T[rson].mmin);
}

void push_down(int u)
{
	if(T[u].lazy == N)
		return ;
	check_min(T[lson].mmin,T[u].lazy);
	check_min(T[rson].mmin,T[u].lazy);
	check_min(T[lson].lazy,T[u].lazy);
	check_min(T[rson].lazy,T[u].lazy);
	T[u].lazy = N;
}

void updata(int u,int l,int r,int up)
{
	if(T[u].l == l && T[u].r == r)
	{
		check_min(T[u].mmin,up);
		check_min(T[u].lazy,up);
		return ;
	}
	push_down(u);
	int m = T[u].mid();
	if(r <= m)
		updata(lson,l,r,up);
	else if(l >= m)
		updata(rson,l,r,up);
	else
		updata(lson,l,m,up) , updata(rson,m,r,up);
	push_up(u);
}

int query(int u,int l)
{
	if(T[u].l == l && T[u].r == l+1)
		return T[u].mmin;
	push_down(u);
	int m = T[u].mid();
	if(l <  m)
		return query(lson,l);
	else
		return query(rson,l);
}

int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		for(int i=1;i<=n;i++)
			scanf("%d%d",&a[i].first,&a[i].second);
		sort(a+1,a+1+n);
		pre(n);
		build(1,1,n+1);
		dp[0][0] = dp[0][1] = 0;
		for(int i=1;i<=n;i++)
		{
			dp[i][0] = min(dp[l[i]-1][0],dp[l[i]-1][1]) + 1;
			dp[i][1] = min(dp[i-1][0],dp[i-1][1]) + 1;
			check_min(dp[i][1],query(1,i));
			updata(1,i,r[i]+1,dp[i][1]);
		}
		printf("%d\n",min(dp[n][0],dp[n][1]));
	}
	return 0;
}
