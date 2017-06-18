/*
���˴���ֿ⣬��������ң����ֱ�Ӱ�colorдpoint���ˣ�Ȼ��������ʱ��дһ�Ѵ��롭��
��һ�νӴ�����ɨ�裬�Ȱѵ㰴��ԽǶ�����ö����˵㣬Ȼ��ά��������ֱ��������Ķ�Ӧ���ų�һ��ֱ��
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1005;
struct point
{
    int x,y;double rad;
}midp[maxn],p[maxn];
int n,color[maxn];
bool xmul(point a,point b)
{
    return a.x*b.y-a.y*b.x>=0;
}
bool cmp(point a,point b)
{
    return a.rad<b.rad;
}
int main()
{
    //freopen("test.txt","r",stdin);
    int n;
    while(~scanf("%d",&n)&&n)
    {
        if(n<=2)
        {
            printf("2\n");
            continue;
        }
        for(int i=0;i<n;i++)
            scanf("%d%d%d",&midp[i].x,&midp[i].y,color+i);
        int ans=0;
        for(int i=0;i<n;i++)
        {
            int cnt=0;
            for(int j=0;j<n;j++)
            {
                if(j==i) continue;
                p[cnt].x=midp[j].x-midp[i].x;
                p[cnt].y=midp[j].y-midp[i].y;
                if(color[j])p[cnt].x=-p[cnt].x,p[cnt].y=-p[cnt].y;
                p[cnt].rad=atan2(p[cnt].y,p[cnt].x);
                cnt++;
            }
            sort(p,p+cnt,cmp);
            int l=0,r=0,num=2;
            while(l<cnt)
            {
                if(l==r){r=(r+1)%cnt;num++;continue;}
                while(r!=l&&xmul(p[l],p[r])){r=(r+1)%cnt;num++;}
                l++;
                num--;
                ans=max(ans,num);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
