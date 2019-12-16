#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>

#define ll long long
#define db double
#define rg register int

using namespace std;

int n,m,q;
int d[1000005]; //并查集里面节点到其联通块的根的距离
int g[1000005]; //当前联通块的gcd，如天天爱跑步
int fa[1000005]; //并查集

inline int qr(){
    register char ch; register bool sign=0; rg res=0;
    while(!isdigit(ch=getchar()))if(ch=='-')sign=1;
    while(isdigit(ch))res=res*10+(ch^48),ch=getchar();
    if(sign)return -res; else return res;
}

inline int gcd(int a,int b){
    if(b==0)return a; return gcd(b,a%b);
}

inline int getfa(int x){
    if(x==fa[x])return x;
    rg to=getfa(fa[x]); //注意顺序，防止信息被覆盖
    d[x]=(d[x]+d[fa[x]])%m; //更新当前节点到根的距离
    return fa[x]=to; //最后再赋值
}

inline void exgcd(int a,int b,int &x,int &y){ //扩展欧几里得
    if(b==0) x=1,y=0; //直接构造一组解
    else exgcd(b,a%b,y,x),y-=a/b*x; //我们不需要求gcd，只要解方程就好
}

int main(){
    n=qr(); m=qr(); q=qr();
    for(rg i=1;i<=n;++i) fa[i]=i,g[i]=m;
    for(rg i=1;i<=q;++i){
        rg op=qr(),u=qr(),v=qr(),w=qr();
        rg fx=getfa(u),fy=getfa(v); //查找根
        if(op==1){
            if(fx!=fy){ fa[fx]=fy; //合并
                d[fx]=((ll)d[u]+d[v]+w)%m; //一个联通块只有一个根，所以另一个需要改距离
                g[fy]=gcd(gcd(g[fx],g[fy]),2*w); //更新联通块的gcd
            }else g[fx]=gcd(gcd(g[fx],((ll)d[u]+d[v]+w)%m),2*w); //新加了一个环，合并环的贡献
        } else{ //请注意大小写！！！！！！
            rg ans=0,b=qr()%g[fx],c=qr(); //读入
            if(fx!=fy){puts("0"); continue;} //不连通意味着不能到达
            rg A=b,B=g[fx],G=gcd(A,B),C=(ll)d[u]+d[v]-w+B; //列出同余方程的系数
            // 同余方程： C + x*A = 0 (mod B)   ->   x*A + y*B = C (mod g[fx])
			cout<<A<<' '<<B<<' '<<C<<' '<<G<<endl;
            if(C%G){puts("0"); continue;} //方程无解，请参见扩欧的做法
            rg x,y; A/=G; B/=G; C/=G; //请参见扩欧的解方程的步骤
            exgcd(A,B,x,y); x=((ll)x*C%B+B)%B; //解出同余方程
            if(x<c)ans=(c-1-x)/B+1; //注意我们找的是x的最小解，循环长度是模数B！ （同余方程性质）
            printf("%d\n",ans); //输出答案
        }
    }
    return 0;
}
