#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,m,A[M];
char s[M];
int Get(char c){
    return c=='('?1:-1;
}
namespace Px{
    struct node{
        int sum;
        int lmn,lmx;
        int rmn,rmx;
        node operator +(node a){
            node c;
            c.sum=sum+a.sum;
            c.lmn=min(  lmn,sum+a.lmn);
            c.lmx=max(  lmx,sum+a.lmx);
            c.rmn=min(a.rmn,a.sum+rmn);
            c.rmx=max(a.rmx,a.sum+rmx);
            // printf("%d %d %d %d\n",c.lmn,c.lmx,c.rmn,c.rmx);
            return c;
        }
        void SWAP(){
            swap(lmn,rmn);
            swap(lmx,rmx);
        }
        void inv(){
            sum*=-1;
            lmn*=-1,lmx*=-1;
            rmn*=-1,rmx*=-1;
            swap(lmn,lmx);
            swap(rmn,rmx);
        }
        void PLACE(int s){
            lmn=min(0,s);
            rmn=min(0,s);
            lmx=max(0,s);
            rmx=max(0,s);
            sum=s;
        }
    };
    struct Tree{
        int ch[2],fa;
        int val,sz;
        node x;
        bool swp,inv;
        int tag;
        void plac(int t){
            inv=0;
            val=tag=t;
            x.PLACE(t*sz);
        }
        void rev(){
            if(tag==0){
                val*=-1;
                x.inv();
                inv^=1;
            }else plac(tag*-1);
        }
        void Swap(){
            swap(ch[0],ch[1]);
            x.SWAP();
            swp^=1;
        }
    }T[M];
    void Up(int p){
        int ls=T[p].ch[0];
        int rs=T[p].ch[1];
        T[p].sz=T[ls].sz+1+T[rs].sz;
        T[p].x.PLACE(T[p].val);
        if(ls)T[p].x=T[ls].x+T[p].x;
        if(rs)T[p].x=T[p].x+T[rs].x;
    }
    void Down(int p){
        if(T[p].swp){
            T[T[p].ch[0]].Swap();
            T[T[p].ch[1]].Swap();
            T[p].swp=0;
        }
        if(T[p].tag!=0){
            T[T[p].ch[0]].plac(T[p].tag);
            T[T[p].ch[1]].plac(T[p].tag);
            T[p].tag=0;
        }
        if(T[p].inv){
            T[T[p].ch[0]].rev();
            T[T[p].ch[1]].rev();
            T[p].inv=0;
        }
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
    int stk[M],top,rt;
    void splay(int x,int to){
        for(int y=x;y!=to;y=T[y].fa)stk[++top]=y;
        while(top)Down(stk[top--]);
        while(T[x].fa!=to){
            int y=T[x].fa,z=T[y].fa;
            if(z!=to)
                rotate((T[y].ch[1]==x)^(T[z].ch[1]==y)?y:x);
            rotate(x);
        }if(!to)rt=x;
    }
    int find(int kth){
        int p=rt;
        kth++;
        while(1){
            Down(p);
            if(T[T[p].ch[0]].sz>=kth)p=T[p].ch[0];
            else {
                kth=kth-(T[T[p].ch[0]].sz+1);
                if(kth==0)return p;
                p=T[p].ch[1];
            }
        }
    }
    void Replace(int a,int b,int c){
        int t1=find(a-1),t2=find(b+1);
        splay(t1,0),splay(t2,t1);
        int t=T[t2].ch[0];
        T[t].plac(c);Down(t);
        Up(t2),Up(t1);
        splay(t,0);
    }
    void Swap(int a,int b){
        int t1=find(a-1),t2=find(b+1);
        splay(t1,0),splay(t2,t1);
        int t=T[t2].ch[0];
        T[t].Swap();Down(t);
        Up(t2),Up(t1);
        splay(t,0);
    }
    void Invert(int a,int b){
        int t1=find(a-1),t2=find(b+1);
        splay(t1,0),splay(t2,t1);
        int t=T[t2].ch[0];
        T[t].rev();Down(t);
        Up(t2),Up(t1);
        splay(t,0);
    }
    int Query(int a,int b){
        int t1=find(a-1),t2=find(b+1);
        splay(t1,0),splay(t2,t1);
        int t=T[t2].ch[0];
        int mn=T[t].x.lmn;
        int s=T[t].x.sum;
        // printf("%d %d\n",mn,s);
        int res=(1-mn)/2;
        s+=res*2;
        res+=s/2;
        splay(t,0);
        return res;
    }
    void solve(){
        rt=1;
        for(int i=1;i<=n+1;i++)T[i+1].fa=i,T[i].ch[1]=i+1;
        for(int i=0;i<=n+1;i++)T[i+1].val=A[i];
        for(int i=n+1;i>=0;i--)Up(i+1);
        char op[20];
        for(int i=1,a,b;i<=m;i++){
            scanf("%s%d%d",op,&a,&b);
            if(op[0]=='R'){
                scanf("%s",op);
                Replace(a,b,Get(op[0]));
            }else if(op[0]=='S')Swap(a,b);
            else if(op[0]=='I')Invert(a,b);
            else printf("%d\n",Query(a,b));
        }
    }
}
int main(){
    freopen("brackets.in","r",stdin);
    freopen("brackets.out","w",stdout);
    scanf("%d%d",&n,&m);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++)
        A[i]=Get(s[i]);
    if(n<=3000&&m<=3000)P1::solve();
    else Px::solve();
    return 0;
}