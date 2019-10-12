#include <bits/stdc++.h>
using namespace std;
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define fst first
#define snd second
#define SZ(u) ((int) (u).size())
#define ALL(u) (u).begin(), (u).end()
inline void proc_status(){
	ifstream t("/proc/self/status");
	cerr << string(istreambuf_iterator<char>(t), istreambuf_iterator<char>()) << endl;
}
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template<typename T> inline T read(){
	register T sum(0), fg(1);
	register char ch(getchar());
	for(; !isdigit(ch); ch = getchar()) if(ch == '-') fg = -1;
	for(;  isdigit(ch); ch = getchar()) sum = sum * 10 - '0' + ch;
	return sum * fg;
}
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = (int) 1e6;
int n, m;
int p[MAXN * 2 + 5];
inline void input(){
	n = read<int>(), m = read<int>();
	for(int i = 1; i <= 2 * n; ++i) p[i] = read<int>();
}
namespace TREE{
	const int MAX_NODE = MAXN * 2;
	int l[MAXN * 2 + 5], r[MAXN * 2 + 5];
	int fa[MAX_NODE + 5];
	vector<int> adj[MAX_NODE + 5];
	const int MAX_LOG = 20;
	int rt[MAX_NODE + 5], dep[MAX_NODE + 5], anc[MAX_LOG + 1][MAX_NODE + 5];
	inline void dfs(int u,int rt0){
		rt[u]=rt0;
		dep[u]=fa[u]==-1 ? 1 : dep[fa[u]] + 1;
		anc[0][u] = fa[u];
		for(int i = 1; (1 << i) < dep[u]; ++i) anc[i][u] = anc[i - 1][anc[i - 1][u]];
		for(auto v : adj[u]) dfs(v, rt0);
	}
	inline void build(){
		static vector<int> stk;
		stk.clear();
		for(int i = 1; i <= 2 * n; ++i){
			l[i] = min(i, p[i]);
			r[i] = max(i, p[i]);
			while(!stk.empty() && stk.back() >= l[i]){
				int p = stk.back();
				stk.pop_back();
				chkmin(l[i], l[p]);
				chkmax(r[i], r[p]);
			}
			stk.push_back(i);
		}
		for(int i = 0; i <= 2 * n; ++i) rt[i] = fa[i] = -1;
		for(int i = 1; i <= 2 * n; ++i) if(r[i] == i){
			fa[i] = l[i] - 1;
			adj[l[i] - 1].push_back(i);
		}
		r[0] = 0;
		for(int i = 0; i <= 2 * n; ++i) if(!adj[i].empty() && rt[i] == -1) dfs(i, i);
	}
	inline int lca(int u, int v){
		if(dep[u] < dep[v]) swap(u, v);
		for(int k = dep[u] - dep[v], i = 0; (1 << i) <= k; ++i) if(k >> i & 1) u = anc[i][u];
		if(u == v) return u;
		for(int i = MAX_LOG; i >= 0; --i) if((1 << i) < dep[u] && anc[i][u] != anc[i][v]) u = anc[i][u], v = anc[i][v];
		return fa[u];
	}
	inline int query(int r1, int r2) { return rt[r1] == -1 || rt[r2] == -1 || rt[r1] != rt[r2] ? 0 : dep[lca(fa[r1], fa[r2])]; }
}
inline void solve(){
	TREE::build();
	while(m--){
		int r1 = read<int>(), r2 = read<int>();
		if(r1 == 0 || r2 == 0) puts("0");
		else printf("%d\n", TREE::query(r1, r2));
	}
}
int main(){
	input();
	solve();
	return 0;
}

