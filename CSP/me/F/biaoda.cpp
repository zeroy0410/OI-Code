#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ui unsigned int
const int N = 3e5 + 7;
int n, rt, s[N], g[N], u, v, z[N];
vi e[N];
ll ans, c1[N], c2[N];

inline void add(ll *c, int x, int k) {
    ++x;
    while (x <= n + 1) c[x] += k, x += x & -x;
}

inline ll ask(ll *c, int x) {
    ++x;
    ll k = 0;
    while (x) k += c[x], x -= x & -x;
    return k;
}

void dfs1(int x, int f) {
    s[x] = 1, g[x] = 0;
    bool fg = 1;
    for (ui i = 0; i < e[x].size(); i++) {
        int y = e[x][i];
        if (y == f) continue;
        dfs1(y, x);
        s[x] += s[y];
        g[x] = max(g[x], s[y]);
        if (s[y] > (n >> 1)) fg = 0;
    }
    if (n - s[x] > (n >> 1)) fg = 0;
    if (fg) rt = x;
}

void dfs2(int x, int f) {
    add(c1, s[f], -1);
    add(c1, n - s[x], 1);
    if (x ^ rt) {
        ans += x * ask(c1, n - 2 * g[x]);
        ans -= x * ask(c1, n - 2 * s[x] - 1);
        ans += x * ask(c2, n - 2 * g[x]);
        ans -= x * ask(c2, n - 2 * s[x] - 1);
        if (!z[x] && z[f]) z[x] = 1;
        ans += rt * (s[x] <= n - 2 * s[z[x]?v:u]);
    }
    add(c2, s[x], 1);
    for (ui i = 0; i < e[x].size(); i++) {
        int y = e[x][i];
        if (y == f) continue;
        dfs2(y, x);
    }
    add(c1, s[f], 1);
    add(c1, n - s[x], -1);
    if (x ^ rt) {
        ans -= x * ask(c2, n - 2 * g[x]);
        ans += x * ask(c2, n - 2 * s[x] - 1);
    }
}

inline void solve() {
	scanf("%d",&n);
    for (int i = 1; i <= n; i++) e[i].clear();
    for (int i = 1, x, y; i < n; i++) rd(x), rd(y), e[x].pb(y), e[y].pb(x);
    ans = 0;
    dfs1(1, 0);
    dfs1(rt, 0);
    u = v = 0;
    for (ui i = 0; i < e[rt].size(); i++) {
        int x = e[rt][i];
        if (s[x] > s[v]) v = x;
        if (s[v] > s[u]) swap(u, v);
    }
    for (int i = 1; i <= n + 1; i++) c1[i] = c2[i] = 0;
    for (int i = 0; i <= n; i++) add(c1, s[i], 1), z[i] = 0;
    z[u] = 1;
    dfs2(rt, 0);
	printf("%d",ans);
}

int main() {
    int T;
	scanf("%d",&T);
    while (T--) solve();
    return 0;
}