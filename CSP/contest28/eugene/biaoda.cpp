#include <bits/stdc++.h>
template <typename _tp> inline void read(_tp&x){
	char ch=getchar(),ob=0;x=0;
	while(ch!='-'&&!isdigit(ch))ch=getchar();if(ch=='-')ob=1,ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();if(ob)x=-x;
}
const int N = 1001000, M = N + N;
int dir[2][N];
int rev[M], ans[M], rep[M];
int vis[N];
int n, m, tot;
struct node {
	int id, to;
}a[2][N];
void add(int x, int y, int id, int t) {
	node*f = a[t];
	int*d = dir[t];
	if(f[x].id and f[x].to == y) {
		rep[f[x].id] = rep[id] = 0;
		ans[id] = 1, ans[f[x].id] = d[y];
		f[x].id = f[y].id = 0;
		return ;
	}
	bool flg = true;
	if(f[x].id) {
		flg = false;
		rep[f[x].id] = tot;
		rev[f[x].id] = d[x];
		f[x].id = 0;
		x = f[x].to;
	}
	if(f[y].id) {
		flg = false;
		rep[f[y].id] = tot;
		rev[f[y].id] = d[y] ^ 1;
		f[y].id = 0;
		y = f[y].to;
	}
	f[x].to = y, f[y].to = x;
	d[x] = 1, d[y] = 0;
	if(flg) f[x].id = f[y].id = id;
	else rep[id] = f[x].id = f[y].id = tot++;
}
void work(int p) {
	int x = p, t = 0;
	vis[x] = 1;
	while(a[t][x].id) {
		ans[a[t][x].id] = dir[t][x];
		if(vis[a[t][x].to]) return ;
		vis[a[t][x].to] = true;
		x = a[t][x].to, t ^= 1;
	}
	x = p, t = 1;
	while(a[t][x].id) {
		ans[a[t][x].id] = dir[t][x] ^ 1;
		vis[a[t][x].to] = true;
		x = a[t][x].to, t ^= 1;
	}
}
int main() {
	freopen("eugene.in","r",stdin);
	freopen("eugene.out","w",stdout);
	read(n), read(m), tot = m+1;
	for(int i=1,x,y,z;i<=m;++i) {
		read(x), read(y), read(z);
		add(x, y, i, z-1);
	}
	for(int i=0;i<n;++i)
		if(!vis[i]) work(i);
	for(int i=tot;i;--i)
		if(rep[i]) ans[i] = ans[rep[i]] ^ rev[i];
	for(int i=1;i<=m;++i)
		putchar('0'+ans[i]);
	putchar(10);
	return 0;
}
