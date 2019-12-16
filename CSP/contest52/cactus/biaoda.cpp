#include<bits/stdc++.h>
#define FOR(i, x, y) for(int i = (x), i##END = (y); i <= i##END; ++i)
#define DOR(i, x, y) for(int i = (x), i##END = (y); i >= i##END; --i)
template<typename T, typename _T> inline bool chk_min(T &x, const _T &y) {return y < x ? x = y, 1 : 0;}
template<typename T, typename _T> inline bool chk_max(T &x, const _T &y) {return x < y ? x = y, 1 : 0;}
typedef long long ll;
const int N = 5005;
const int M = 10005;
const int P = 1e9 + 7;
template<const int N, const int M, typename T> struct Linked_List
{
	int head[N], nxt[M], tot; T to[M];
	Linked_List() {clear();}
	T &operator [](const int x) {return to[x];}
	void clear() {memset(head, -1, sizeof(head)), tot = 0;}
	void add(int u, T v) {to[tot] = v, nxt[tot] = head[u], head[u] = tot++;}
#define EOR(i, G, u) for(int i = G.head[u]; ~i; i = G.nxt[i])
};
Linked_List<N, M << 1, int> G;
int n, m, K;

inline void plseq(int &x, int y) {(x += y) >= P ? x -= P : 0;}

namespace Subtask1
{
	bool mark[1 << 20 | 5];
	int cnt[1 << 20 | 5];

	void Solve()
	{
		FOR(i, 1, m)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			u--, v--;
			G.add(u, v), G.add(v, u);
		}
		FOR(i, 0, n - 1) mark[1 << i] = 1;
		int ans = 0;
		FOR(B, 1, (1 << n) - 1)
		{
			cnt[B] = cnt[B >> 1] + (B & 1);
			if(mark[B])
			{
				if(cnt[B] <= K) ans++;
				FOR(i, 0, n - 1) if(B >> i & 1)
					EOR(j, G, i)
					{
						int k = G[j];
						if(~B >> k & 1)
							mark[B | (1 << k)] = 1;
					}
			}
		}
		printf("%d\n", ans);
	}
};

namespace Subtask2
{
	int dp[N][33];
	int ans;

	void dfs(int u, int f)
	{
		dp[u][1] = 1;
		EOR(i, G, u)
		{
			int v = G[i];
			if(v == f) continue;
			dfs(v, u);
			DOR(j, K, 1)
				FOR(k, 1, j - 1)
				plseq(dp[u][j], 1ll * dp[u][k] * dp[v][j - k] % P);
		}
		FOR(i, 1, K) plseq(ans, dp[u][i]);
	}

	void Solve()
	{
		FOR(i, 1, m)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			G.add(u, v), G.add(v, u);
		}
		dfs(1, 0);
		printf("%d\n", ans);
	}
};

namespace Subtask3
{
	int dp[N][33], ans;
	int tmp[N][33], tmp2[N][33];
	int fa[N], dfn[N], low[N], idxer;
	int stk[N], tot;
	bool is_back[M << 1];
	void tarjan(int u, int f, int fa_e)
	{
		dfn[u] = low[u] = ++idxer;
		fa[u] = f;
		EOR(i, G, u)
		{
			if(i / 2 == fa_e / 2) continue;
			int v = G[i];
			if(!dfn[v]) tarjan(v, u, i), chk_min(low[u], low[v]);
			else
			{
				chk_min(low[u], dfn[v]);
				if(dfn[u] > dfn[v]) is_back[i] = 1;
			}
		}
	}
	void dp_on_cycle(int s, int e)
	{
		tot = 0;
		for(int u = e; u != s; u = fa[u]) stk[++tot] = u;
		stk[++tot] = s;
		FOR(i, 1, tot / 2) std::swap(stk[i], stk[tot - i + 1]);

		FOR(i, 0, tot + 1) FOR(j, 0, K) tmp[i][j] = 0;
		tmp[1][0] = 1;
		FOR(i, 2, tot)
		{
			tmp[i][0] = 1;
			FOR(j, 1, K)
			{
				FOR(k, 1, j)
					plseq(tmp[i][j], 1ll * dp[stk[i]][k] * tmp[i - 1][j - k] % P);
				plseq(ans, tmp[i][j]);
			}
		}

		FOR(i, 0, tot + 1) FOR(j, 0, K) tmp[i][j] = tmp2[i][j] = 0;
		tmp[0][0] = 1;
		FOR(i, 1, tot)
			FOR(j, 1, K)
			FOR(k, 1, j)
			plseq(tmp[i][j], 1ll * dp[stk[i]][k] * tmp[i - 1][j - k] % P);
		tmp2[tot + 1][0] = 1;
		DOR(i, tot, 1)
			FOR(j, 1, K)
			FOR(k, 1, j)
			plseq(tmp2[i][j], 1ll * dp[stk[i]][k] * tmp2[i + 1][j - k] % P);
		DOR(i, tot, 1) FOR(j, 0, K) plseq(tmp2[i][j], tmp2[i + 1][j]);
		FOR(j, 1, K)
		{
			dp[s][j] = 0;
			plseq(dp[s][j], tmp[tot][j]);
			FOR(i, 1, tot - 1) FOR(k, 1, j) plseq(dp[s][j], 1ll * tmp[i][k] * tmp2[i + 2][j - k] % P);
		}
	}

	void dfs(int u, int fa_e)
	{
		dp[u][1] = 1;
		EOR(i, G, u)
		{
			if(i / 2 == fa_e / 2 || is_back[i ^ 1] || is_back[i]) continue;
			int v = G[i];
			dfs(v, i);
			if(low[v] <= dfn[u]) continue;
			DOR(j, K, 1)
				FOR(k, 1, j - 1)
				plseq(dp[u][j], 1ll * dp[u][k] * dp[v][j - k] % P);
		}
		EOR(i, G, u)
			if(is_back[i ^ 1])
				dp_on_cycle(u, G[i]);
		if(dfn[u] == low[u]) FOR(i, 1, K) plseq(ans, dp[u][i]);
	}

	void Solve()
	{
		FOR(i, 1, m)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			G.add(u, v), G.add(v, u);
		}
		tarjan(1, 0, -2);
		dfs(1, -2);
		printf("%d\n", ans);
	}
}

int main()
{
	freopen("cactus.in", "r", stdin);
	freopen("cactus.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &K);
	if(n <= 20 && m <= 40) Subtask1::Solve();
	else if(m == n - 1) Subtask2::Solve();
	else Subtask3::Solve();
	return 0;
}

