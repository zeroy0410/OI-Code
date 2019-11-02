#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
 
const int MaxN = 100000 + 5;
const int S = 170;
const int MaxS = S + 5, MaxV = MaxN / S + 5;
const int INF = 0x3F3F3F3F;
 
int N, Q, V, F, LastAns;
int A[MaxN];
int Ans[MaxV][MaxS][MaxS], Lnk[MaxV][MaxN], Cnt[MaxV][MaxS], Left[MaxV][MaxS], Right[MaxV][MaxS];
int Bel[MaxN], L[MaxV], R[MaxV], Tag[MaxV], Stk[MaxV][MaxS], Top[MaxV];
int ColStack[MaxS], Tp; bool Used[MaxN];
 
void init() {
  scanf("%d %d %d", &N, &Q, &F);
  for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
  for (int i = 1; i <= N; ++i) {
    Bel[i] = (i - 1) / S + 1;
    if (L[Bel[i]] == 0) L[Bel[i]] = i;
    R[Bel[i]] = i;
  }
  V = Bel[N];
}
 
inline void getColStack(int l, int r) {
  for (int i = 1; i <= Tp; ++i) {
    Used[ColStack[i]] = false;
    ColStack[i] = 0;
  }
  Tp = 0;
  for (int i = l; i <= r; ++i) {
    int c = A[i];
    if (Used[c] == true) continue;
    Used[c] = true;
    ColStack[++Tp] = c;
  }
}
 
inline void recalc(int s, int col) {
  int c = Lnk[s][col];
  int maxC = -INF;
  for (int i = L[s]; i <= R[s]; ++i) {
    if (A[i] == col) maxC = i;
    int c2 = Lnk[s][A[i]];
    Ans[s][c][c2] = std::min(Ans[s][c][c2], i - maxC);
    Ans[s][c2][c] = std::min(Ans[s][c2][c], i - maxC);
  }
  int minC = INF;
  for (int i = R[s]; i >= L[s]; --i) {
    if (A[i] == col) minC = i;
    int c2 = Lnk[s][A[i]];
    Ans[s][c][c2] = std::min(Ans[s][c][c2], minC - i);
    Ans[s][c2][c] = std::min(Ans[s][c2][c], minC - i);
  }
}
 
inline void updateBlock(int l, int r, int v) {
  int s = Bel[l];
  int *left = Left[s], *right = Right[s], *stk = Stk[s], *lnk = Lnk[s], *cnt = Cnt[s];
  if (Tag[s] != 0) {
    getColStack(L[s], R[s]);
    for (int i = 1; i <= Tp; ++i) {
      int c = lnk[ColStack[i]];
      cnt[c] = 0;
      for (int j = 1; j <= S; ++j)
        Ans[s][c][j] = Ans[s][j][c] = INF;
      left[c] = right[c] = 0;
      stk[++Top[s]] = c;
      lnk[ColStack[i]] = 0;
    }
    lnk[Tag[s]] = stk[Top[s]--];
    int x = lnk[Tag[s]];
    cnt[x] = R[s] - L[s] + 1;
    left[x] = L[s], right[x] = R[s];
    Ans[s][x][x] = 0;
    for (int i = L[s]; i <= R[s]; ++i) A[i] = Tag[s];
    Tag[s] = 0;
  }
  getColStack(l, r);
  for (int i = 1; i <= Tp; ++i) {
    int c = lnk[ColStack[i]];
    for (int j = 1; j <= S; ++j)
      Ans[s][c][j] = Ans[s][j][c] = INF;
    left[c] = right[c] = 0;
  }
  for (int i = l; i <= r; ++i) {
    int c = lnk[A[i]];
    cnt[c]--;
    if (cnt[c] == 0) {
      stk[++Top[s]] = c;
      lnk[A[i]] = 0;
    }
  }
  if (lnk[v] == 0) {
    lnk[v] = stk[Top[s]--];
  }
  cnt[lnk[v]] += r - l + 1;
  for (int i = l; i <= r; ++i) A[i] = v;
  for (int i = L[s]; i <= R[s]; ++i) {
    int c = lnk[A[i]];
    if (left[c] == 0) left[c] = i;
    right[c] = i;
  }
  if (Used[v] == false) ColStack[++Tp] = v;
  for (int i = 1; i <= Tp; ++i)
    if (lnk[ColStack[i]] != 0) recalc(s, ColStack[i]);
}
 
void solve() {
  memset(Ans, 0x3F, sizeof Ans);
  for (int s = 1; s <= V; ++s) {
    int *left = Left[s], *right = Right[s], *stk = Stk[s], *lnk = Lnk[s], *cnt = Cnt[s];
    static int a[MaxS];
    for (int i = L[s]; i <= R[s]; ++i)
      a[i - L[s] + 1] = A[i];
    std::sort(a + 1, a + 1 + R[s] - L[s] + 1);
    for (int i = L[s]; i <= R[s]; ++i)
      lnk[A[i]] = std::lower_bound(a + 1, a + 1 + R[s] - L[s] + 1, A[i]) - a;
    int mx = 0;
    for (int i = L[s]; i <= R[s]; ++i) {
      int c = lnk[A[i]];
      mx = std::max(mx, c);
      if (left[c] == 0) left[c] = i;
      right[c] = i;
      cnt[c]++;
    }
    Top[s] = 0;
    for (int i = mx + 1; i <= S; ++i) stk[++Top[s]] = i;
    for (int i = L[s]; i <= R[s]; ++i)
      for (int j = L[s]; j <= R[s]; ++j) {
        int ci = lnk[A[i]], cj = lnk[A[j]];
        Ans[s][ci][cj] = std::min(Ans[s][ci][cj], abs(i - j));
      }
  }
  for (int q = 1; q <= Q; ++q) {
    int opt;
    scanf("%d", &opt);
    if (opt == 1) {
      int l, r, x;
      scanf("%d %d %d", &l, &r, &x);
      l ^= LastAns, r ^= LastAns, x ^= LastAns;
      int u = Bel[l], v = Bel[r];
      if (u == v) {
        updateBlock(l, r, x);
        continue;
      }
      updateBlock(l, R[u], x);
      updateBlock(L[v], r, x);
      for (int i = u + 1; i < v; ++i) Tag[i] = x;
    } else {
      int x, y;
      scanf("%d %d", &x, &y);
      x ^= LastAns, y ^= LastAns;
      int ans = INF, maxX = -INF, maxY = -INF;
      for (int s = 1; s <= V; ++s) {
        int *left = Left[s], *right = Right[s], *lnk = Lnk[s];
        if (Tag[s] == 0) {
          int _x = lnk[x], _y = lnk[y];
          if (_x != 0 && _y != 0) ans = std::min(ans, Ans[s][_x][_y]);
          if (_x != 0) ans = std::min(ans, left[_x] - maxY);
          if (_y != 0) ans = std::min(ans, left[_y] - maxX);
          if (_x != 0) maxX = right[_x];
          if (_y != 0) maxY = right[_y];
        } else {
          if (Tag[s] == x) {
            ans = std::min(ans, L[s] - maxY);
            maxX = R[s];
          } else if (Tag[s] == y) {
            ans = std::min(ans, L[s] - maxX);
            maxY = R[s];
          }
        }
      }
      if (F == 0 || ans == INF) LastAns = 0;
      else LastAns = ans;
      if (ans == INF) puts("-1");
      else printf("%d\n", ans);
    }
  }
}
 
int main() {
  init();
  solve();
  return 0;
}
