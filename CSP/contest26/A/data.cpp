#include<bits/stdc++.h>
using namespace std;
int main(){
    srand(time(NULL));
    int n=1e9,m=200;
    cout<<n<<' '<<m<<endl;
    for(int i=1;i<=m;i++)
        printf("%d\n",rand()%n+1);
    return 0;
}