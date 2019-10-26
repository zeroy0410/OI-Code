#include<bits/stdc++.h>
#define FOR(i, x, y) for(int i = (x), i##END = (y); i <= i##END; ++i)
#define DOR(i, x, y) for(int i = (x), i##END = (y); i >= i##END; --i)
template<typename T, typename _T> inline bool chk_min(T &x, const _T y) {return y < x ? x = y, 1 : 0;}
template<typename T, typename _T> inline bool chk_max(T &x, const _T y) {return x < y ? x = y, 1 : 0;}
typedef long long ll;
const int N = 1e5 + 5;
const int M = 1e5 + 5;
template<const int N, const int M, typename T> struct LinkedList
{
	int head[N], nxt[M], tot; T to[M];
	LinkedList() {clear();}
	T &operator [](const int x) {return to[x];}
	void clear() {memset(head, -1, sizeof(head)), tot = 0;}
	void add(int u, T v) {to[tot]= v, nxt[tot] = head[u], head[u] = tot++;}
	#define EOR(i, G, u) for(int i = G.head[u]; ~i; i = G.nxt[i])
};
LinkedList<N, M << 1, int> G;
LinkedList<N, N, int> T;
int n, m;
using namespace std;
namespace Subtask2
{
	int dfn[N], low[N], idxer;
	int fa[N];
	int deg[N];
	int ans[N], Ac;
	bool mrk[N];
	void dfs(int u, int fa_e)
	{
		dfn[u] = low[u] = ++idxer;
		EOR(i, G, u)
		{
			int v = G[i];
			if(i / 2 == fa_e / 2) continue;
			if(u==926)cout<<v<<' '<<dfn[v]<<' '<<dfn[u]<<endl;
			if(!dfn[v])
			{
				//printf("(%d, %d)\n", u, v);
				dfs(v, i);
				T.add(u, v);
				chk_min(low[u], low[v]);
			}
			else chk_min(low[u], dfn[v]);
		}
	}
	void redfs(int u)
	{
		mrk[u] = 1;
		EOR(i, T, u)
		{
			int v = T[i];
//			if(u==926&&v==162)puts("!!");
			if(low[v] >= dfn[u]) mrk[u] = 0;
			redfs(v);
		}
	}
	void Solve()
	{
		FOR(u, 1, n) EOR(i, G, u)
		{
			int v = G[i];
			deg[v]++;
		}
		dfs(1, -2);
		int cnt = 0;
		EOR(i, T, 1)
		{
			int u = T[i];
			cnt++;
			redfs(u);
		}
		if(cnt <= 1 && m - deg[1] == n - 2) ans[++Ac] = 1;
		FOR(i, 2, n) if(mrk[i] && m - deg[i] == n - 2) ans[++Ac] = i;
		printf("%d\n", Ac);
		FOR(i, 1, Ac) printf("%d%c", ans[i], (i == Ac ? '\n' : ' '));
	}
};

int main()
{
	scanf("%d%d", &n, &m);
	FOR(i, 1, m)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G.add(u, v), G.add(v, u);
	}
	Subtask2::Solve();
	return 0;
}
