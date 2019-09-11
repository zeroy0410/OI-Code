#define FILE_NAME "graph"
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
const int M=1e5+5;
int n,m,ind[M],Dec[M];
vector<int>E[M];
struct node {
    int d,x;
    bool operator <(const node & _)const { return d>_.d; }
    friend ostream& operator<<(ostream& os,node T){
        return os<<'('<<T.d<<','<<T.x<<')';
    }
} now;
bool Check(int mid) {
    static node tmp[M];
    static bool exist[M];
    int top=0;
    priority_queue<node>Q;
    for(int i=1; i<=n; i++) {
        Q.push((node) {ind[i],i});
        exist[i]=true;
    }
    bool flag=true;
    while(flag) {
        flag=false;
        while(!Q.empty() && Q.top().d-Dec[Q.top().x]<mid) {
            now=Q.top(); Q.pop();
            Dec[now.x]=0; exist[now.x]=false;
            for(int i=0; i<E[now.x].size(); i++)if(exist[E[now.x][i]])
                Dec[E[now.x][i]]++;
            flag=true;
        }
        if(Q.empty())return false;
        top=0;
        while(!Q.empty()) {
            tmp[++top]=Q.top(); Q.pop();
            tmp[top].d-=Dec[tmp[top].x];
            Dec[tmp[top].x]=0;
        }
        for(int i=1; i<=top; i++)
            Q.push(tmp[i]);
    }
    return true;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1; i<=m; i++) {
        int x,y;
        cin>>x>>y;
        E[x].push_back(y);
        E[y].push_back(x);
        ind[x]++;
        ind[y]++;
    }
    int Mx=INT_MIN;
    for(int i=1; i<=n; i++)
        tomax(Mx,ind[i]);
    int L=0,R=Mx,mid,ans=-1;
    while(L<=R) {
        mid=(L+R)>>1;
        if(Check(mid)) {
            L=mid+1;
            ans=mid;
        } else R=mid-1;
    }
    cout<<ans<<endl;
    return 0;
}
