#include <bits/stdc++.h>
#define rep(i, a, b) for(int i(a), i##_END_(b); i <= i##_END_; i++)
#define drep(i, a, b) for(int i(a), i##_END_(b); i >= i##_END_; i--)

#define File(name) freopen(#name".in", "r", stdin), freopen(#name".out", "w", stdout)

typedef long long ll;
typedef double db;

template<class T> void rd(T &a) {
#define gc getchar()
	char c; bool f = false;
	for(c = gc; !isdigit(c); c = gc) f |= c == '-';
	for(a = 0; isdigit(c); c = gc) a = (a << 1) + (a << 3) + c - '0';
	if(f) a = -a;
#undef gc
}

template<class T> inline bool tomax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template<class T> inline bool tomin(T &a, T b) {return b < a ? a = b, 1 : 0;}

const int N = 1e5 + 5;

template<int N, int M, class T> struct Link {
#define erep(k, G, o) for(int k(G.HEAD[o]); k; k = G.NXT[k])
	int HEAD[N], NXT[M], tot; T W[M];
	void add(int x, T w) {NXT[++tot] = HEAD[x]; W[HEAD[x] = tot] = w;}
	T& operator[] (int x) {return W[x];}
};
struct Edge {
	int to, w;
};
Link<N, N * 2, Edge> G;

struct Tree {
	int fa[N], hs[N], tp[N], dep[N], sz[N], dis[N];
	void dfs1(int o, int f) {
		fa[o] = f; dep[o] = dep[f] + 1;
		sz[o] = 1; hs[o] = 0;
		erep(k, G, o) {
			int v = G[k].to;
			if(v == f) continue;
			dis[v] = dis[o] + G[k].w;
			dfs1(v, o);
			sz[o] += sz[v];
			if(sz[v] > sz[hs[o]]) hs[o] = v;
		}
	}
	void dfs2(int o, int f, int t) {
		tp[o] = t;
		if(hs[o]) dfs2(hs[o], o, t);
		erep(k, G, o) {
			int v = G[k].to;
			if(v == f || v == hs[o]) continue;
			dfs2(v, o, v);
		}
	}
	int lca(int u, int v) {
		while(tp[v] != tp[u]) {
			if(dep[tp[u]] < dep[tp[v]]) std::swap(u, v);
			u = fa[tp[u]];
		}
		return dep[u] < dep[v] ? u : v;
	}
	void init(int rt) {
		dis[rt] = 0; dfs1(rt, 0); dfs2(rt, 0, rt);
	}
} t1, t2;

int vec[N], n, m;

namespace P60 {
	bool check() {
		return (ll) n * m <= 1e8 && (ll) m * m <= 1e8;
	}
	int tag[N];
	void dfs(int o, int f) {
		erep(k, G, o) {
			int v = G[k].to;
			if(v == f) continue;
			dfs(v, o);
			tag[o] += tag[v];
		}
	}
	int upd(int u, int v, int d) {
		int p = t1.lca(u, v);
		tag[u] += d; tag[v] += d;
		tag[p] -= d; tag[t1.fa[p]] -= d;
	}
	bool mark[N];
	int main() {
		rep(i, 1, m) mark[vec[i]] = true;
		t1.init(1);
		rep(i, 1, m) {
			t2.init(vec[i]);
			int mx = 0, p = 0;
			rep(j, 1, m) if(i != j) tomax(mx, t2.dis[vec[j]]);
			rep(j, 1, m) if(t2.dis[vec[j]] == mx) {
				if(p == 0) p = vec[j];
				else p = t2.lca(p, vec[j]);
			}
			upd(vec[i], p, 1);
		}
		dfs(1, 0);
		int mx = 0, c = 0;
		rep(i, 1, n) if(!mark[i]) {
			if(tomax(mx, tag[i])) c = 0;
			if(mx == tag[i]) c++;
		}
		printf("%d %d\n", mx, c);
		return 0;
	}
}

int main() {
	File(tree);
	int a, b, w;
	rd(n); rd(m);
	rep(i, 1, m) rd(vec[i]);
	rep(i, 2, n) {
		rd(a); rd(b); rd(w);
		G.add(a, (Edge) {b, w});
		G.add(b, (Edge) {a, w});
	}
	if(P60::check()) return P60::main();
	return 0;
}

