#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF=0x3f3f3f3f;
const int maxn=100005;
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("test.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(scanf("%d",&n)==1)
    {
        int div=sqrt(2*n)+1;
        bool flag=0;
        for(int i=div;i>=2;i--)
        {
            int f=2*i;
            int a=2*n+i-i*i;
            if(a%f==0&&a/f)
            {
                flag=1;
                printf("%d\n",a/f);
            }
        }
        if(!flag) printf("No Solution\n");
    }
    return 0;
}
