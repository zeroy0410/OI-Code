#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring> 
#include <cmath> 
#include <algorithm>
using namespace std; 
inline int gi() {
    register int data = 0, w = 1;
    register char ch = 0;
    while (!isdigit(ch) && ch != '-') ch = getchar(); 
    if (ch == '-') w = -1, ch = getchar(); 
    while (isdigit(ch)) data = 10 * data + ch - '0', ch = getchar(); 
    return w * data; 
} 
const int MAX_N = 2e3 + 5; 
struct Graph { int to, next; } e[MAX_N << 1]; 
int fir[MAX_N], e_cnt; 
void clearGraph() { memset(fir, -1, sizeof(fir)); e_cnt = 0; } 
void Add_Edge(int v, int u) { e[e_cnt] = (Graph){v, fir[u]}, fir[u] = e_cnt++; } 
int N, w[MAX_N]; 
struct Node { 
    int deg, beg, end, pa[MAX_N]; 
    bool st[MAX_N], ed[MAX_N]; 
    void clear() { 
        deg = 0, beg = end = -1; 
        for (int i = 0; i <= N; i++) st[i] = ed[i] = 1, pa[i] = i; 
    } 
    int getf(int x) { while (x != pa[x]) x = pa[x] = pa[pa[x]]; return x; } 
} t[MAX_N]; 
int Find(int x, int id) { 
    int res = N + 1; 
    if (~id && (t[x].end == -1 || t[x].end == id)) { 
        if (t[x].ed[id] && (t[x].beg == -1 || t[x].deg <= 1 || t[x].getf(id) != t[x].getf(t[x].beg))) res = x; 
    } 
    for (int i = fir[x]; ~i; i = e[i].next) { 
        if (id == (i >> 1)) continue; 
        int ed = i >> 1; 
        if (~id) { 
            if (id == t[x].end || ed == t[x].beg || t[x].getf(id) == t[x].getf(ed)) continue; 
            if (!t[x].ed[id] || !t[x].st[ed]) continue; 
            if (~t[x].beg && ~t[x].end && t[x].deg > 2 &&
                t[x].getf(id) == t[x].getf(t[x].beg) && t[x].getf(ed) == t[x].getf(t[x].end)) continue; 
            res = min(res, Find(e[i].to, ed)); 
        } else { 
            if (t[x].beg == -1 || t[x].beg == ed) { 
                if (!t[x].st[ed]) continue; 
                if (~t[x].end && t[x].deg > 1 && t[x].getf(ed) == t[x].getf(t[x].end)) continue; 
                res = min(res, Find(e[i].to, ed)); 
            } 
            else continue; 
        } 
    } 
    return res; 
} 
bool Link(int x, int id, int p) { 
    if (x == p) return t[x].end = id, 1; 
    for (int i = fir[x]; ~i; i = e[i].next) { 
        if (id == (i >> 1)) continue; 
        int ed = i >> 1; 
        if (Link(e[i].to, ed, p)) { 
            if (~id) { 
                t[x].ed[id] = t[x].st[ed] = 0, --t[x].deg; 
                t[x].pa[t[x].getf(id)] = t[x].getf(ed); 
            } 
            else t[x].beg = ed; 
            return 1; 
        } 
    } 
    return 0; 
} 
int main () { 
    int T = gi();
    while (T--) {
        clearGraph();
        N = gi(); for (int i = 1; i <= N; i++) w[i] = gi(), t[i].clear();
        if (N == 1) { puts("1"); continue; } 
        for (int i = 1; i < N; i++) { 
            int u = gi(), v = gi(); 
            Add_Edge(u, v), Add_Edge(v, u); 
            ++t[u].deg, ++t[v].deg; 
        } 
        for (int i = 1; i <= N; i++) { 
            int p = Find(w[i], -1); 
            Link(w[i], -1, p); 
            printf("%d ", p); 
        } 
        putchar('\n'); 
    } 
    return 0; 
} 