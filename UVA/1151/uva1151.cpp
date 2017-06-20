#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF=0x3f3f3f3f;
struct Edge
{
    int u,v,d;
    bool operator <(const Edge &rhs) const
    {
        return d<rhs.d;
    }
};
const int maxn=5005;int n;int q;
int father[maxn],x[maxn],y[maxn];
int look(int x){return father[x]==x?x:father[x]=look(father[x]);}
vector<Edge>edge,need;
vector<int>discount[10];
int cost[10];
int Kruskal(int cnt,vector<Edge>e,vector<Edge>&use)//cnt:cc������
{
    if(cnt==1) return 0;
    int mm=e.size();int ans=0;use.clear();
    for(int i=0;i<mm;i++)
    {
        int u=look(e[i].u),v=look(e[i].v);int d=e[i].d;
        if(u!=v)
        {
            father[u]=v;
            ans+=d;use.push_back(e[i]);
            if(--cnt==1) break;
        }
    }
    return ans;
}
int solve()
{
    for(int i=0;i<n;i++) father[i]=i;
    sort(edge.begin(),edge.end());
    int ans=Kruskal(n,edge,need);//��һ�� ȫͼ�ıߣ�n��cc��ÿ���㶼��һ����
    for(int mask=0;mask<(1<<q);mask++)//ö���ײ� �ö��������ֱ�ﹺ�򷽰�
    {
        for(int i=0;i<n;i++) father[i]=i;
        int cnt=n,c=0;
        for(int i=0;i<q;i++) if(mask&(1<<i))//������ײͣ����㹺����Լ��ٶ��ٸ�cc
        {
            c+=cost[i];
            for(int j=1;j<discount[i].size();j++)
            {
                int u=look(discount[i][j]),v=look(discount[i][0]);
                if(u!=v){father[u]=v;cnt--;}
            }
        }
        vector<Edge>temp;
        ans=min(ans,c+Kruskal(cnt,need,temp));//�ڶ��� �ײ��еıߺ͵�һ�εı�,�۳����������cc
    }
    return ans;
}
int main()
{
    //freopen("test.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int a,b;
    int ks,sz,tmp;scanf("%d\n",&ks);
    while(ks--)
    {
        scanf("%d%d",&n,&q);
        for(int i=0;i<q;i++)
        {
            discount[i].clear();
            scanf("%d%d",&sz,cost+i);
            for(int j=0;j<sz;j++)
            {
                scanf("%d",&tmp);
                discount[i].push_back(tmp-1);
            }
        }
        for(int i=0;i<n;i++) scanf("%d%d",x+i,y+i);
        edge.clear();need.clear();
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                int c=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
                edge.push_back((Edge){i,j,c});//ֻ��1000���㣬������ȫͼ
            }
        }
        int ans=solve();
        printf("%d\n",ans);
        if(ks) printf("\n");
    }
    return 0;
}
