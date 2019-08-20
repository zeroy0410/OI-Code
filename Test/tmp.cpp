#include<bits/stdc++.h>

#define FOR(x,y,z) for(int x=y,x##_=z;x<=x##_;++x)
#define DOR(x,y,z) for(int x=y,x##_=z;x>=x##_;--x)

#define clr(x,y) memset(x,y,sizeof(x))

#define read2(x,y) read(x),read(y)
#define read3(x,y,z) read(x),read(y),read(z)
#define read4(x,y,z,w) read3(x,y,z),read(w)
#define reads(str) sf("%s",str)

#define sf scanf
#define pf printf

#define db double


using namespace std;

template<class T>bool tomin(T &x,T y){return y<x?x=y,1:0;}
template<class T>bool tomax(T &x,T y){return x<y?x=y,1:0;}
template<class T>void read(T &x){
    char c;
    x=0;
    int f=1;
    while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
    do x=(x<<3)+(x<<1)+(c^48);
    while(c=getchar(),c>='0'&&c<='9');
    x*=f;
}
bool mem1;
const db Pi=acos(-1);
const int maxn=810;
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
int n;
int posx[maxn],szx;
int posy[maxn],szy;
int mp[maxn][maxn];
struct Edge{
    int x1,x2,y1,y2;
    void Rd(){
        read4(x1,y1,x2,y2);
        x1<<=1; x2<<=1; y1<<=1; y2<<=1; posx[++szx]=x1; posx[++szx]=x2; posx[++szx]=x1-1; posx[++szx]=x2+1; posy[++szy]=y1; posy[++szy]=y2; posy[++szy]=y1-1; posy[++szy]=y2+1;
    }
    void uni(){
        x1=lower_bound(posx+1,posx+szx+1,x1)-posx;
        x2=lower_bound(posx+1,posx+szx+1,x2)-posx;
        y1=lower_bound(posy+1,posy+szy+1,y1)-posy;
        y2=lower_bound(posy+1,posy+szy+1,y2)-posy;
    }
    void cvr(){
        FOR(i,x1,x2)FOR(j,y1,y2)mp[i][j]++;
    }
}A[maxn];
struct node{
    int x,y;
    db d;
    bool operator <(const node &A)const
    {
        return d>A.d;
    }
};
priority_queue<node>q;
db dis[maxn][maxn];
bool vis[maxn][maxn];
db Dis(int x1,int y1,int x2,int y2){
    return (db)(abs(posx[x1]-posx[x2])+abs(posy[y1]-posy[y2]))/min(mp[x1][y1],mp[x2][y2]);
}
void Dijk(){
    FOR(i,1,szx)FOR(j,1,szy){
        dis[i][j]=1e100;
        vis[i][j]=0;
    }
    dis[A[0].x1][A[0].y1]=0;
    while(!q.empty())q.pop();
    q.push((node){A[0].x1,A[0].y1,0});
    while(!q.empty()){
        node tmp=q.top();q.pop();
        int x=tmp.x,y=tmp.y;
        if(vis[x][y])continue;
        vis[x][y]=1;
        if(x==A[0].x2&&y==A[0].y2){
            pf("%.5lf\n",dis[x][y]/2);
            return;
        }
        FOR(i,0,3){
            int xx=x+dx[i];
            int yy=y+dy[i];
            if(mp[xx][yy]&&tomin(dis[xx][yy],dis[x][y]+Dis(x,y,xx,yy)))
                q.push((node){xx,yy,dis[xx][yy]});
        }
    }
}
bool mem2;
int main(){
    // cerr<<(&mem2-&mem1)/1024.0/1024<<endl;
    int T;
    read(T);
    while(T--){
        szx=szy=0;
        read(n);
        FOR(i,1,n)A[i].Rd();A[0].Rd();
        sort(posx+1,posx+szx+1);
        szx=unique(posx+1,posx+szx+1)-posx-1;
        sort(posy+1,posy+szy+1);
        szy=unique(posy+1,posy+szy+1)-posy-1;
        FOR(i,0,n)A[i].uni();
        clr(mp,0);
        FOR(i,1,szx)FOR(j,1,szy)mp[i][j]=1;
        FOR(i,1,n)A[i].cvr();
        Dijk();
    }
    return 0;
}
