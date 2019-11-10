#include<bits/stdc++.h>
#define M 800005
using namespace std;
struct Tree{
    int ch[2],rk,fa,sz,cnt,fr;
}T[M];
struct Query{
    int op,x;
}Q[M];
int tot,rt,mn,n,m;
int A[M],len;
map<int,int>RK;
void Up(int x){
    T[x].sz=T[T[x].ch[0]].sz+T[T[x].ch[1]].sz+T[x].cnt;
}
void rotate(int x){
    int y=T[x].fa,z=T[y].fa;
    int k=T[y].ch[1]==x;
    T[z].ch[T[z].ch[1]==y]=x;
    T[x].fa=z;
    T[y].ch[k]=T[x].ch[k^1];
    T[T[x].ch[k^1]].fa=y;
    T[x].ch[k^1]=y;
    T[y].fa=x;
    Up(y),Up(x);
}
void splay(int x,int to){
    while(T[x].fa!=to){
        int y=T[x].fa,z=T[y].fa;
        if(z!=to)
            (T[z].ch[1]==y)^(T[y].ch[1]==x)?rotate(x):rotate(y);
        rotate(x);
    }if(!to)rt=x;
}
void Insert(int Rk,int Sz,int Fr){
    int u=rt,f=0;
    while(u)f=u,u=T[u].ch[Rk>T[u].rk];
    u=++tot;
    T[u].fa=f;
    T[u].rk=Rk;
    T[u].sz=T[u].cnt=Sz;
    T[u].fr=Fr;
    if(f)T[f].ch[Rk>T[f].rk]=u;
    splay(u,0);
}
int find(int x){
    int u=rt;
    while(T[u].rk!=x)u=T[u].ch[x>T[u].rk];
    return u;
}
void Del(int x){//É¾µã
    splay(x,0);
    int pre=T[x].ch[0];
    while(T[pre].ch[1])pre=T[pre].ch[1];
    int nxt=T[x].ch[1];
    while(T[nxt].ch[0])nxt=T[nxt].ch[0];
    splay(pre,0);
    splay(nxt,pre);
    T[nxt].ch[0]=0;
    Up(nxt),Up(pre);
}
void Top(int x){
    Del(find(RK[x]));
    RK[x]=--mn;
    Insert(RK[x],1,x);
}
int Get(int x){
    int u=rt;
    while(1){
        int SZ=T[T[u].ch[0]].sz;
        if(SZ>=x)u=T[u].ch[0];
        else {
            x-=SZ;
            if(x<=T[u].cnt)return T[u].fr+x-1;
            else x-=T[u].cnt,u=T[u].ch[1];
        }
    }
}
int main(){
    for(int _=(scanf("%d",&_),_),kase=0;_;_--){
        tot=rt=len=0;RK.clear();mn=1;
        memset(T,0,sizeof(T));
        
        scanf("%d%d",&n,&m);
        A[++len]=1;A[++len]=n+1;
        char op[10];
        for(int i=1,x;i<=m;i++){
            scanf("%s%d",op,&x);
            if(op[0]=='T')Q[i].op=0,A[++len]=x,A[++len]=x+1;
            else if(op[0]=='R')Q[i].op=1;
            else Q[i].op=2,A[++len]=x,A[++len]=x+1;
            Q[i].x=x;
        }
        sort(A+1,A+len+1);
        len=unique(A+1,A+len+1)-A-1;
        for(int i=1;i<len;i++){
            Insert(i,A[i+1]-A[i],A[i]);
            RK[A[i]]=i;
        }
        Insert(-2e9,0,0);Insert(2e9,0,0);
        printf("Case %d:\n",++kase);
        for(int i=1;i<=m;i++){
            int x=Q[i].x;
            if(Q[i].op==0)Top(x);
            else if(Q[i].op==1)printf("%d\n",Get(x));
            else{
                int t=find(RK[x]);
                splay(t,0);
                printf("%d\n",T[T[t].ch[0]].sz+1);
            }
        }
    }
    return 0;
}
