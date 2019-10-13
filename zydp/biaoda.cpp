#include <iostream>
#include <cstdio>
#define re register//优化
namespace cz//自定义double类型的max函数
{
    double max(double x,double y)
    {
        return x>y?x:y;
    }
}
using namespace std;
int n,k,maxs,p[18],need[18];//need[i]是吃第i个宝物所需要吃的宝物
double dp[105][1<<15];
inline int read()//速读不说
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<3)+(x<<1)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main()
{
    k=read(),n=read();
    for(re int i=1;i<=n;i++)
    {
        p[i]=read();
        int u;
        while(scanf("%d",&u)&&u)//输入吃第i个宝物所需的宝物
            need[i]|=(1<<(u-1));
    }
    maxs=(1<<n)-1;//最大状态是全选
    for(re int i=k;i>=1;i--)//逆推
        for(re int s=0;s<=maxs;s++)//循环枚举状态
        {
            for(re int j=1;j<=n;j++)
            {
                if((need[j]&s)==need[j])//若能选宝物
                    dp[i][s]+=cz::max(dp[i+1][s],dp[i+1][s|(1<<(j-1))]+p[j]);
                else//若不能选宝物
                    dp[i][s]+=dp[i+1][s];
            }
            dp[i][s]/=n;//每个宝物被选中的概率为1/n
			cout<<i<<' '<<s<<' '<<dp[i][s]<<endl;
        }
    printf("%.6lf",dp[1][0]);
    return 0;
}
