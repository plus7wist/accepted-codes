#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<math.h>
#include<string.h>
#include<queue>
#include<vector>
#include<map>
#include<iostream>
#include<string>
#define LL long long
using namespace std;
LL bell[100005];
int main()
{
//freopen("test.txt","r",stdin);
    int n,k;
    scanf("%d%d",&n,&k);//n�����ɷ�k�����ӣ�ÿ������2��
    for(int i=0;i<n;i++) scanf("%I64d",&bell[i]);//����
    LL ans=bell[n-1];
    if(n<=k){printf("%I64d\n",ans);return 0;}//������
    else if(n/k<2)//���ַ���
    {
        for(int i=0;i<(n%k);i++)
            ans=max(ans,bell[i]+bell[2*(n%k)-i-1]);//ǰ2*n%kҪ����
    }
    else//ȫ����
    {
        for(int i=0;i<n/2;i++)
            ans=max(ans,bell[i]+bell[n-i-1]);//��β����
    }
    printf("%I64d\n",ans);
    return 0;
}