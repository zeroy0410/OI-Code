#include<bits/stdc++.h>
#define M 100005
using namespace std;
struct node{
    int sum;
    int lmi,lmx,rmi,rmx;
    node operator + (node a){
        node c;
        c.sum=sum+a.sum;
        c.lmi=min(lmi,sum+a.lmi);
        c.lmx=max(lmx,sum+a.lmx);
        c.rmi=min(a.rmi,a.sum+rmi);
        c.rmx=max(a.rmx,a.sum+rmx);
        return c;
    }
    void Swap(){
        swap(lmi,rmi);
        swap(lmx,rmx);
    }
    void inv(){
        sum*=-1;
        lmi*=-1;rmi*=-1;
        lmx*=-1;rmx*=-1;
        swap(lmi,lmx);
        swap(rmi,rmx);
    }
    void place(int s){
        lmi=rmi=min(0,s);
        lmx=rmx=max(0,s);
        sum=s;
    }
};
struct Splay{
    int ch[M][2],fa[M],rt,tot,sz[M];
    int stk[M],top;
    node po[M];
    bool swp[M],inv[M];
    int tag[M],val[M];
    void plac(int x,int t){
        inv[x]=0;
        val[x]=tag[x]=t;
        po[x].place(t*sz[x]);
    }
    void rev(int x){
        if(!tag[x]){
            val[x]*=-1;
            po[x].inv();
            inv[x]^=1;
        }else plac(x,tag[x]*-1);
    }
    void Swap(int x){
        swap(ch[x][0],ch[x][1]);
        po[x].Swap();
        swp[x]^=1;
    }
    void clear(){rt=tot=0;}
    void Up(int p){
        sz[p]=sz[ch[p][0]]+sz[ch[p][1]]+1;
        po[p].place(val[p]);
        if(ch[p][0])po[p]=po[ch[p][0]]+po[p];
        if(ch[p][1])po[p]=po[p]+po[ch[p][1]];
    }
    void Down(int p){
        if(swp[p]){
            Swap(ch[p][0]);
            Swap(ch[p][1]);
            swp[p]=0;
        }
        if(tag[p]){
            plac(ch[p][0],tag[p]);
            plac(ch[p][1],tag[p]);
            tag[p]=0;
        }
        if(inv[p]){
            rev(ch[p][0]);
            rev(ch[p][1]);
            inv[p]=0;
        }
    }
    void rotate(int x){
        int y=fa[x],z=fa[y],k=x==ch[y][1];
        Down(y);Down(x);
        if(z)ch[z][y==ch[z][1]]=x;fa[x]=z;
        ch[y][k]=ch[x][!k];if(ch[x][!k])fa[ch[x][!k]]=y;
        ch[x][!k]=y;fa[y]=x;
        Up(y);Up(x);
    }
    void splay(int x,int w){
        for(int y=x;;y=fa[y]){
            stk[++top]=y;
            if(y==w)break;
        }while(top)Down(stk[top--]);
        while(fa[x]!=w){
            int y=fa[x],z=fa[y];
            if(z!=w)(y==ch[z][1]&&x==ch[y][1])?rotate(y):rotate(x);
            rotate(x);
        }
        if(!w)rt=x;
    }
    int find(int x){
        x++;
        int u=rt;
        while(1){
            Down(u);
            if(sz[ch[u][0]]+1==x)return u;
            else if(sz[ch[u][0]]>=x)u=ch[u][0];
            else x-=sz[ch[u][0]]+1,u=ch[u][1];
        }
        return u;
    }
    void Replace(int l,int r,int c){
        int L=find(l-1),R=find(r+1);
        splay(L,0);splay(R,L);
        int t=ch[R][0];
        plac(t,c);Down(t);
        Up(R);Up(L);
        splay(t,0);
    }
    void Swap(int l,int r){
        int L=find(l-1),R=find(r+1);
        splay(L,0);splay(R,L);
        int t=ch[R][0];
        Swap(t);Down(t);
        Up(R);Up(L);
        splay(t,0);
    }
    void Invert(int l,int r){
        int L=find(l-1),R=find(r+1);
        splay(L,0);splay(R,L);
        int t=ch[R][0];
        rev(t);Down(t);
        Up(R);Up(L);
        splay(t,0);       
    }  
    int Query(int l,int r){
        int L=find(l-1),R=find(r+1);
        splay(L,0);splay(R,L);
        int t=ch[R][0];
        int mn=po[t].lmi,s=po[t].sum;
        int res=(1-mn)/2;
        s+=res*2;
        res+=s/2;
        splay(t,0);
        return res;
    }
}T;
int n,m;
char S[M],op[15];
int main(){
    freopen("brackets.in","r",stdin);
    freopen("brackets.out","w",stdout);
    scanf("%d%d",&n,&m);
    scanf("%s",S+1);
    T.rt=1;
    for(int i=1;i<=n+1;i++)T.fa[i+1]=i,T.ch[i][1]=i+1;
    for(int i=0;i<=n+1;i++)T.val[i+1]=(S[i]=='(')?1:-1;
    for(int i=n+1;i>=0;i--)T.Up(i+1);
    while(m--){
        int a,b;
        scanf("%s",op+1);
        scanf("%d%d",&a,&b);
        if(op[1]=='R'){
            scanf("%s",op+1);
            T.Replace(a,b,(op[1]=='(')?1:-1);
        }
        else if(op[1]=='S')T.Swap(a,b);
        else if(op[1]=='I')T.Invert(a,b);
        else printf("%d\n",T.Query(a,b));
    }
    return 0;
}