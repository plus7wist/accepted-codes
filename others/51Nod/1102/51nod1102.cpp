#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF=0x3f3f3f3f;
const int maxn=50000+5;
LL l[maxn],r[maxn],a[maxn];
int main()
{
    //freopen("test.txt","r",stdin);
    int n;
    while(scanf("%d",&n)==1)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%I64d",a+i);
            l[i]=i;r[i]=i;
        }
        for(int i=1;i<=n;i++)
        {
            while(l[i]>=1&&a[i]<=a[l[i]-1])
                l[i]=l[l[i]-1];
        }
        for(int i=n;i>=1;i--)
        {
            while(r[i]<=n&&a[i]<=a[r[i]+1])
                r[i]=r[r[i]+1];
        }
        LL ans=0;
        for(int i=1;i<=n;i++)
        {
            ans=max(ans,(r[i]-l[i]+1)*a[i]);
        }
        printf("%I64d\n",ans);
    }
    return 0;
}