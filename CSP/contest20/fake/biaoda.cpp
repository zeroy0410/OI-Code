#define FILE_NAME "fake"
//*INDENT-OFF*
#include<bits/stdc++.h>
using namespace std;
template<typename V>
bool tomin(V&x,V y){if(y<x){x=y;return true;}return false;}
template<typename V>
bool tomax(V&x,V y){if(x<y){x=y;return true;}return false;}
typedef long long ll;
typedef unsigned long long ull;
typedef double dbl;
typedef pair<int,int> PII;
typedef pair<int,dbl> PID;
#define lowbit(x) ((x)&-(x))
#define FILE_IO freopen(FILE_NAME".in","r",stdin);freopen(FILE_NAME".out","w",stdout)
//*INDENT-ON*
const int M=3e5+5;
int n,m,C[M],dep[M],Ans;
vector<int>E[M],PP[M];
bool mark_for_deletion[M];
struct node {
    int x,id;
    bool operator <(const node & _)const {
        return dep[x]>dep[_.x];
    }
} now;
vector<node>P[M];
priority_queue<node>Q[M];
void dfs0(int x,int f,int d) {
    dep[x]=d;
    for(auto v:E[x]) {
        if(v==f) continue;
        dfs0(v,x,d+1);
    }
}
bool cmp(int x,int y) {
    return Q[x].size()>Q[y].size();
}
int dfs1(int x,int f) {
    int miu=0;
    for(auto v:E[x]) {
        if(v==f) continue;
        miu+=dfs1(v,x);
    }
    if(E[x].size()) {
        sort(E[x].begin(),E[x].end(),cmp);
        if(E[x][0]!=f) {
            for(int i=1; i<E[x].size(); i++) {
                int v=E[x][i];
                if(v==f) continue;
                while(!Q[v].empty()) {
                    Q[E[x][0]].push(Q[v].top());
                    Q[v].pop();
                }
            }
            swap(Q[x],Q[E[x][0]]);
        } else {
            for(int i=2; i<E[x].size(); i++) {
                int v=E[x][i];
                if(v==f) continue;
                while(!Q[v].empty()) {
                    Q[E[x][1]].push(Q[v].top());
                    Q[v].pop();
                }
            }
            swap(Q[x],Q[E[x][1]]);
        }
    }
    for(auto v:P[x]) {
        miu++;
        Q[x].push(v);
    }
    while(C[x]<miu) {
        now=Q[x].top(); Q[x].pop();
        if(mark_for_deletion[now.id])continue;
        mark_for_deletion[now.id]=true;
        miu--;
    }
    for(auto v:PP[x])if(!mark_for_deletion[v]) {
        Ans++;
        miu--;
        mark_for_deletion[v]=true;
    }
    return miu;
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++)
        scanf("%d",&C[i]);
    int x,y;
    for(int i=1; i<n; i++) {
        scanf("%d%d",&x,&y);
        E[x].push_back(y);
        E[y].push_back(x);
    }
    dfs0(1,1,1);
    for(int i=1; i<=m; i++) {
        scanf("%d%d",&x,&y);
        if(dep[x]<dep[y]) swap(x,y);
        P[x].push_back((node) {y,i});
        PP[y].push_back(i);
    }
    dfs1(1,0);
    printf("%d\n",Ans);
    return 0;
}
