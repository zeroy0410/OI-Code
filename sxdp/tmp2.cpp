#include<cstdio>
#include<algorithm>
#pragma GCC optimize(3)
#include<vector>
#include<cctype>
inline int getint() {
    char ch;
    while(!isdigit(ch=getchar()));
    int x=ch^'0';
    while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
    return x;
}
const int N=6000,inf=0x7fffffff;
struct Edge {
    int to,w;
};
int n;
std::vector<Edge> e[N];
int uu=0,vv=0,stop=0;
int v,w,d,y,u;
void find_vertex(int x,int depth,int parent) {
    if(depth>d) {
        d=depth;
        v=x;
    }
    for(register unsigned int i=0;i<e[x].size();i++) {
        if((e[x][i].to!=parent)&&(e[x][i].to!=uu)&&(e[x][i].to!=vv)) {
            find_vertex(e[x][i].to,depth+e[x][i].w,x);
        }
    }
}
void find_d(int x,int depth,int parent) {
    if(depth>y) {
        y=depth;
        u=x;
    }
    for(unsigned int i=0;i<e[x].size();i++) {
        if((e[x][i].to!=parent)&&(e[x][i].to!=stop)) {
            find_d(e[x][i].to,depth+e[x][i].w,x);
        }
    }
}
int l[N];
bool find_path(int x,int depth,int parent) {
    w++;
    l[w]=depth;
    if(x==u) return true;
    for(register unsigned int i=0;i<e[x].size();i++) {
        if(e[x][i].to!=parent) {
            if(find_path(e[x][i].to,depth+e[x][i].w,x)) return true;
        }
    }
    w--;
    return false;
}
inline int find_mid() {
    for(int i=0;i<w;i++) {
        if((l[i]<=(y>>1))&&(l[i+1]>=(y>>1))) {
            return std::min(std::max(l[i],y-l[i]),std::max(l[i+1],y-l[i+1]));
        }
    }
    return 0;
}
inline int getsum(int p) {
    w=0,d=0,y=0,v=p;
    find_vertex(p,0,0);
    find_d(v,0,0);
    find_path(v,0,0);
    return find_mid();
}
struct Edge2 {
    int from,to,w;
};
Edge2 p[N];
int w_whole;
bool find_path_whole(int x,int parent,int w) {
    p[w_whole]=(Edge2){parent,x,w};
    w_whole++;
    if(x==u) return true;
    for(register unsigned int i=0;i<e[x].size();i++) {
        if(e[x][i].to!=parent) {
            if(find_path_whole(e[x][i].to,x,e[x][i].w)) return true;
        }
    }
    w_whole--;
    return false;
}
int main() {
    n=getint();
    for(int i=1;i<n;i++) {
        u=getint(),v=getint(),w=getint();
        e[u].push_back((Edge){v,w});
        e[v].push_back((Edge){u,w});
    }
    w_whole=0,d=0,y=0;
    find_vertex(1,0,0);
    find_d(v,0,0);
    find_path_whole(v,0,0);
    int ans=inf;
    for(register int i=1;i<w_whole;i++) {
        uu=p[i].from;
        vv=p[i].to;
        int s1,s2,cmp=0;
        stop=vv;
        s1=getsum(uu);
        cmp=std::max(cmp,y);
        stop=uu;
        s2=getsum(vv);
        cmp=std::max(cmp,y);
        ans=std::min(ans,std::max(s1+p[i].w+s2,cmp));
    }
    printf("%d\n",ans);
    return 0;
}
