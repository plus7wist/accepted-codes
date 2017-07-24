//���� hash ˫��BFS STL Maxsum LCS LIS
//���� ���� ���� ��λ
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<math.h>
#include<string.h>
#include<queue>
#include<vector>
#include<map>
using namespace std;
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define rer(i,l,u) for(int (i)=(int)(l);(i)<=(int)(u);++(i))
#define reu(i,l,u) for(int (i)=(int)(l);(i)<(int)(u);++(i))
static const int INF = 0x3f3f3f3f; static const long long INFL = 0x3f3f3f3f3f3f3f3fLL;
const int MAXN=1005;const int MOD=1e9+7;
typedef vector<int> vi; typedef pair<int, int> pii; typedef vector<pair<int, int> > vpii; typedef long long LL;
//����
int len;
int a[]= {1,2,3,3,4,5};
int upperbound(int key)
{
    int l=0,r=len-1;
    //cout<<l<<' '<<r<<endl;
    while(l<r)
    {
        int mid=l+(r-l)/2;
        if(key>=a[mid]) l=mid+1;
        else r=mid;
    }
    return l;
}
int lowerbound(int key)
{
    int l=0,r=len-1;
    //cout<<l<<' '<<r<<endl;
    while(l<r)
    {
        int mid=l+(r+1-l)/2;
        if(key>=a[mid]) l=mid;
        else r=mid-1;
    }
    return l;
}
//DJB hash
LL hashed(char str[])
{
    int len=strlen(str);
    LL hasher=5381;
    for(int i=0; i<len; i++)
        hasher=((hasher<<5)+hasher)+str[i];
    return hasher;
}
//d-BFS
bool doubleBFS(int a,int b)
{
    memset(vis1,0,sizeof(vis1));
    memset(vis2,0,sizeof(vis2));
    queue<int>q1,q2;
    q1.push(a);
    q2.push(b);
    while(!q1.empty()||!q2.empty())
    {
        int s1=q1.size();
        int s2=q2.size();
        while(q1--)
        {
            int fr=q1.front();
            q1.pop();
            if(!vis[fr])
            {
                vis[fr]=1;
                q.push(get_next(fr));
            }
        }
        while(q2--)
        {
            //...
        }
    }
}
//STL
vector<int> ivec(10,1);
for(vector<int>::iterator iter=ivec.begin();iter!=ivec.end();++iter)
{
    *iter=2; //ʹ�� * ���ʵ�������ָ���Ԫ��
}
multimap<int,char*>::iterator i,iend;
iend=m.end();
for(i=m.begin();i!=iend;i++)
{
    cout<<(*i).second<<"�ļ�Ǯ��"
    <<(*i).first<<"Ԫ/��\n";
}
//Maxsum
int a[n];
int solve()
{
    int cur=0;int mx=0;
    for(int i=0;i<n;i++)
    {
        if(cur+a[i]>=0) cur+=a[i];
        else cur=0;
        mx=max(mx,cur);
    }
    return mx;
}
//LCS
///O(n^2)
char a[m];char b[n];int d[n];//(n<m)
int solve()
{
    for(int i=0;i<=n;i++) d[i]=0;
    for(int i=1;i<=m;i++)
    {
        int lst=0;int len;
        for(int j=1;j<=n;j++)
        {
            if(a[i]==b[j]) len=lst+1;
            else len=max(d[j],d[j-1]);
            lst=d[j];
            d[j]=len;
        }
    }
    return d[n];
}
/*O(nlogn);���ǰ�a�����е�ÿ��Ԫ����b�г��ֵ�λ�ñ����������ٰ��ս������У����к��ٴ���a��ÿ����ӦԪ�أ��Ǿ�ת��Ϊ��������µ����е�������������ˡ��磺a[] = {a, b, c,} b[] = {a,b,c,b,a,d},��ôa�е�a��b��c��b�г��ֵ�λ�÷ֱ����
{0,4},{1,3},{2}�ֱ𰴽������к����a���о���{4,0,2,3,1},֮����Ҫ���ս������У�Ŀ�ľ���Ϊ����ÿ��Ԫ��ֻȡ��һ�Ρ�
���������������Ҫ������������������ˣ�Ҳ������LIS
int a[LEN], b[LEN];
int loc[LEN], n;
void calLoc()
{
    int i;
    for(i = 1; i <= n; i++)
        loc[b[i]] = i;
}
int LIS()
{
    int i, k, l, r, mid;
    a[1] = b[1], k = 1;
    for(i = 2; i <= n; i++)
    {
        if(a[k] < b[i]) a[++k] = b[i];
        else {
            l = 1; r = k;
            while(l <= r)
            {
                mid = ( l + r ) / 2;
                if(a[mid] < b[i])
                    l = mid + 1;
                else
                    r = mid - 1;
            }
            a[l] = b[i];
        }
    }
    return k;
}
int main()
{
    int i;
    while(scanf("%d", &n) != EOF)
    {
        for(i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for(i = 1; i <= n; i++)
            scanf("%d", &b[i]);
        calLoc();
        for(i = 1; i <= n; i++)
            b[i] = loc[a[i]];
                printf("%d\n", LIS());
    }
    return 0;
}
*/
///LIS
int a[n];int g[n];int d[n];
int solve()
{
    for(int i=0; i<n; i++)
    {
        int j=lower_bound(g,g+n,a[i])-g;
        d[i]=j+1;
        g[j]=a[i];
    }
    return d[n-1];
}
//�����������еĺ�
int a[maxn];int dp[maxn];
int solve()
{
    int ans=0;
    for(int i=0;i<n;i++)
    {
        dp[i]=a[i];
        for(int j=0;j<i;j++)
            if(a[i]>a[j])
            dp[i]=max(dp[i],dp[j]+a[i]);
        ans=max(ans,dp[i]);
    }
    return ans;
}
///����
int t;//ѭ������
int cnt=0;
int money;int dp[MAXN];
void cpack(int cost,int value)
{
    for(int i=money;i<=cost;i++)
        dp[i]=min(dp[i],dp[i-cost]+value);
}
void zopack(int cost,int value)
{
    for(int i=cost;i>=money;i--)
        dp[i]=max(dp[i],dp[i-cost]+value);
}
void mpack(int cost,int value,int num)
{
    if(cost*num>=money)
    {
        cpack(cost,value);
        return;
    }
    for(int k=1;k<num;k*=2)
    {
        zopack(k*cost,k*value);
        num-=k;
    }
    zopack(num*cost,num*value);
}
///����DP-ʯ�ӹ鲢
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 210
int dp[N][N],sum[N];
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        int a[N];sum[0]=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum[i]=sum[i-1]+a[i];
        }
        memset(dp,0,sizeof(dp));
        int i,j,l,k;
        for(l = 2; l <= n; ++l)
        {
            for(i = 1; i <= n - l + 1; ++i)
            {
                j = i + l - 1;
                dp[i][j] = 2100000000;
                for(k = i; k < j; ++k)
                {
                    dp[i][j] = std::min(dp[i][j],dp[i][k] + dp[k + 1][j] + sum[j] - sum[i-1]);
                }
            }
        }
        printf("%d\n", dp[1][n]);
    }
    return 0;
}
///����DP
struct node
{
    int v;
    int next;
}tree[MAXN];
int vis[MAXN],head[MAXN],dp[MAXN][2];
int ptr,n;
void init()
{
    ptr=0;
    memset(dp,0,sizeof(dp));
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
}
void addedge(int x,int y)//y is x's son
{
    tree[ptr]=(node){y,head[x]};
    head[x]=ptr++;
}
void treedp(int cur)
{
    vis[cur]=1;
    for(int i=head[cur];i!=-1;i=tree[i].next)
    {
        int v=tree[i].v;
        if(!vis[v])
        {
            treedp(v);
            dp[cur][1]+=dp[v][0];
            dp[cur][0]+=max(dp[v][1],dp[v][0]);
        }
    }
}
int main()
{
    int n,a,b;
    while(scanf("%d",&n)!=EOF)
    {
        init();
        for(int i=1;i<=n;i++) scanf("%d",&dp[i][1]);
        while(scanf("%d%d",&a,&b),a+b)
        {
            addedge(a,b);
            addedge(b,a);
        }
        treedp(1);
        printf("%d\n",max(dp[1][0],dp[1][1]));
    }
    return 0;
}
///��λDP
int dfs(int i, int s, bool e) {
    if(i==-1) return s==target_s;
    if(!e && ~f[i][s]) return f[i][s];
    int res = 0;
    int u = e?num[i]:9;
    for(int d = first?1:0; d <= u; ++d)
       res += dfs(i-1, new_s(s, d), e&&d==u);
   return e?res:f[i][s]=res;
}
���У�
fΪ���仯���飻
iΪ��ǰ�����ĵ�iλ��Ȩ�ر�ʾ����Ҳ������ʣ��i+1λ����������
sΪ֮ǰ���ֵ�״̬�����Ҫ������������ʲô״̬��Ҳ�����ټ�һ��Ŀ��״̬t֮�࣬for��ʱ��ö����t����
e��ʾ֮ǰ�����Ƿ����Ͻ��ǰ׺������������ܷ��������
forѭ��ö������ʱ��Ҫע���Ƿ���ö��0���Լ�0����״̬��Ӱ�죬�е���Ŀǰ��0���м��0�ǵȼ۵ģ����еĲ��ǣ����ں��߿�����dfsʱ�ټ�һ��״̬����z����ʾǰ���Ƿ�ȫ����ǰ��0��Ҳ���Կ��Ƿ�����λ��Ȼ������ͳ��ʱ��ö��һ��λ����It depends.
���ǹؼ�������ô���״̬����Ȼ������֮��״̬һ�۾Ϳ��������
��
ע�⣺
����������������ʵĻ�����hdu 4376����������solve(r)-solve(l-1)��״̬��ƻ���ӹ��졣
//������������6��2
int dp[7][3];
int digit[7];
int todigit(int n)
{
    int len=0;
    while(n)
    {
        digit[len++]=n%10;
        n/=10;
    }
    digit[len]=0;
    return len-1;
}
int dfs(int pos,int status,int limit)
{
    if(pos<0) return status!=2;
    if(!limit&&~dp[pos][status]) return dp[pos][status];
    int ans=0;
    int len=limit?digit[pos]:9;
    for(int i=0;i<=len;i++)
    {
        int ts=status;
        if(i==4) ts=2;
        else if(ts==0&&i==6) ts=1;
        else if(ts==1&&i==2) ts=2;
        else if(ts==1&&i!=2&&i!=6) ts=0;
        ans+=dfs(pos-1,ts,limit&&i==len);
    }
    return limit?ans:dp[pos][status]=ans;
}
int main()
{
    int a,b;
    while(scanf("%d%d",&a,&b)&&a+b)
    {
        memset(dp,-1,sizeof(dp));
        int ans=dfs(todigit(b),0,1)-dfs(todigit(a-1),0,1);
        printf("%d\n",ans);
    }
    return 0;
}
