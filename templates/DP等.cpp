//���� hash ˫��BFS STL Maxsum LCS LIS
//���� ���� ���� ��λ ���仯����
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
int maxsum()
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
///O(n^2),a,b start from 1
char a[m];char b[n];int d[n];//(n<m)
int LCS()
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
int LIS()
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
int LISsum()
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
//LCIS
int LCIS()
{
    int F[MAXLEN];
    memset(F,0,sizeof(F));
    for(int i=1;i<=Len1;++i)
    {
        int max=0;
        for(int j=1;j<=Len2;++j)
        {
            if(Seq2[j]<Seq1[i])  { max=MAX(max,F[j]); }
            if(Seq1[i]==Seq2[j]) { F[j]=max+1; }
        }
    }
    int ans=-1;
    for(int i=1;i<=Len1;++i)
    {
        ans=MAX(ans,F[i]);
    }
    return ans;
}
///����
int t;//ѭ������
int cnt=0;
int volume;int dp[MAXN];
//��ȫ���� O(VN)
void cpack()
{
    for(int i=0;i<n;i++)
    {
        //for(int j=c[i];j<=v;j++)
            //dp[i]=max(dp[i],dp[i-c[j]]+v[j]);
        cpack(c[i],v[i]);
    }
}
void cpack(int cost,int value)
{
    for(int i=cost;i<=volume;i++)
        dp[i]=min(dp[i],dp[i-cost]+value);
}
//01���� O(VN)
void zopack()
{
    for(int i=0;in;i++)
    {
        //for(int j=v;j>=c[i];j--)
            //dp[i]=max(dp[i],dp[i-c[j]]+v[j]);
        zopack(c[i],v[i]);
    }
}
void zopack(int cost,int value)
{
    for(int i=volume;i>=cost;i--)
        dp[i]=max(dp[i],dp[i-cost]+value);
}
//���ر��� O(V*sum(logMi)),Mi is ith amount
void mpack()
{
    for(int i=0;i<n;i++)
    {
        mpack(c[i],v[i],m[i]);
    }
}
void mpack(int cost,int value,int num)
{
    if(cost*num>=volume)
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
//�������ǡ�ÿ�������ɼ�����Ʒ�ܷ��������������ı�������ֻ�뿼������������
//�����ԣ����迼��ÿ����Ʒ�ļ�ֵʱ�����ر�������ͬ���� O(V N) ���Ӷȵ��㷨��
//���� F[N][0 . . . V ] ���Ƕ��ر�������������Ĵ�
void mpack(int cost,int value,int num)
{
    for(int i=1;i<=volume;i++) dp[0][i]=-1;
    dp[0][0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=volume;j++)
            if(dp[i-1][j]>=0) dp[i][j]=m[i];
            else dp[i][j]=-1;
        for(int j=0;j<=volume-c[i];j++)
            if(dp[i][j]>0) d[i][j+c[i]]=max(dp[i][j+c[i]],dp[i][j]-1);
    }

}
//��ά������������������Ƽ���
void zopack(int cost1,int cost2,int value)
{
    for(int i=volume1;i>=cost1;i--)
        for(int j=volume2;j>=vost2;j--)
        dp[i][j]=max(dp[i][j],dp[i-cost1][j-cost2]+value);
}
//��ʱ������ά���á���������������һ�������ķ�ʽ�����ģ����ֻ��ȡ U ����Ʒ��
//���鱳��
//��Ʒ������Ϊ K �飬ÿ���е���Ʒ�����ͻ�����ѡһ��
void gpack()
{
    for(int kk=1;kk<=k;kk++)
    {
        for(int i=v;i<=0;i--)
            for(int j=0;j<size[k];j++)
            dp[i]=max(dp[i],dp[i-c[j]]+w[j]);
    }
}
//��������
//��Ʒ i ��������Ʒ j����ʾ��ѡ��Ʒ i�������ѡ��Ʒ j
#include<stdio.h>
#include<algorithm>
#include <iostream>
using namespace std;
const int maxn=1000+10;
int w[maxn],b[maxn];
int f[maxn];
int max(int a,int b)
{
    return a>b? a:b;
}
int main()
{
    int n,v;
    int i,j,k;
    int t1,t2;
    while(scanf("%d%d",&n,&v)!=EOF)
    {
        for(i=1; i<=n; i++)
        {
            scanf("%d%d",&w[i],&b[i]);
        }
        memset(f,0,sizeof(f));
        for(i=1; i<=n; i++)
            if(b[i]==i)//�ҳ�����
            {
                memset(c,0,sizeof(c));
                for(t2=1; t2<=n; t2++) //�Ը�������01��������ʹ������ͬ����µõ��ļ�ֵ���
                    if(b[t2]==i&&b[t2]!=t2)
                    {
                        for(t1=v-1; t1>=0; t1--)
                            if(t1-1>=0)
                                c[t1]=max(c[t1],c[t1-1]+w[t2]);
                    }
                c[v]=c[v-1]+w[i];
                for(j=v; j>=0; j--)
                    for(k=1; k<=v; k++) //��ʱ�����൱��"V����Ʒ"��ÿ������Ʒ������൱Ϊ'k',"��ֵΪ"��c[k-1]+w[i],(iΪ����)
                    {
                        if(j-k>=0)
                            f[j]=max(f[j],f[j-k]+w[i]+c[k-1]);
                    }
            }
        printf("%d\n",f[v]);
    }
    return 0;
}
/*
������Ʒ
�ڱ�������Ϊ V �ı��������У�������Ʒ��һ��������Ϊ 0 . . . V�е������ĺ��� h������������ķ���Ϊ v ʱ���ܵõ��ļ�ֵ���� h(v)
���� 0. . .V �е�ÿһ������ v��������÷���v ���䵽 h �� l �е�����ֵ f(v)��Ҳ��
f(v) = max{h(k) + l(v ? k) | 0 �� k �� v}
*/
/*
���Բ�װ������ʼ��ʱDPȫ��Ϊ0���ɣ���ΪINF����δװ��Ʒ�ĸ�״̬���ɽ��ܣ�
����ֵ�����С�����ŷ���
�Ȱ���Ʒ����� x �� N + 1 - x �ı任�����������ʱ��
�任��������������Ʒ��ŵı任�󣬿��԰���ǰ�澭���ת�Ʒ�������ֵ��ֻ������
������ʱҪע�⣬��� F [i, v] = F [i - 1, v] �� F [i, v] = F [i - 1][v - Ci] + Wi ��������
Ӧ�ð��պ����������������ѡ������Ʒ i�������ԭ���ı�� N - 1 - i
�󷽰�������״̬ת�Ʒ����е� max �ĳ� sum
�����ŷ���������ʼ��gΪ0,���dp[v]=dp[v],g[v]+=g[v];dp[v]=dp[v-c[i]],g[v]+=g[v-c[i]]
*/
//��k���
int main()
{
     int T;
     scanf("%d",&T);
     while(T--)
     {
        int n,m,i,j,k,p,a[33],b[33];
         scanf("%d%d%d",&n,&m,&k);
         for(i=0;i<n;i++)
             scanf("%d",&w[i]);
         for(i=0;i<n;i++)
             scanf("%d",&c[i]);
         memset(dp,0,sizeof(dp));
         for(i=0;i<n;i++)
         {
             for(j=m;j>=c[i];j--)
             {
                 for(p=1;p<=k;p++)
                 {
                     a[p]=dp[j-c[i]][p]+w[i]; //��dp[i]=max(dp[j],dp[j-c[i]]+w[i])�в��������Ž⣬С��Ϊ����
                     b[p]=dp[j][p];
                 }
                 a[p]=b[p]=-1;
                 int x,y,z;
                 x=y=z=1;
                 while(z<=k&&(a[x]!=-1||b[y]!=-1))//����������ҵ���������k�ı���
                 {
                     if(a[x]>b[y])
                     {
                         dp[j][z]=a[x];
                             x++;
                     }
                     else
                     {
                         dp[j][z]=b[y];
                             y++;
                     }
                     if(dp[j][z]!=dp[j][z-1])//ȥ���ظ��˵��Ž�
                        z++;
                 }
             }
         }
         printf("%d\n",dp[m][k]);
     }
     return 0;
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
//���仯���� HDU 1428
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int MAXN=55;
const int INF=0x3f3f3f3f;
int a[MAXN][MAXN];
int dis[MAXN][MAXN];
long long dp[MAXN][MAXN];
int n;
bool used[MAXN][MAXN];

struct Node
{
    int x,y;
    int d;
    friend bool operator < (Node a,Node b)
    {
        return a.d>b.d;
    }
};
priority_queue<Node>q;

void init()
{
    while(!q.empty())q.pop();
    memset(used,false,sizeof(used));
    Node tmp,now;
    tmp.x=n;
    tmp.y=n;
    tmp.d=a[n][n];
    q.push(tmp);
    dis[n][n]=a[n][n];
    used[n][n]=true;
    while(!q.empty())
    {
        tmp=q.top();
        q.pop();
        if(tmp.x>1 && !used[tmp.x-1][tmp.y])
        {
            now.x=tmp.x-1;
            now.y=tmp.y;
            now.d=tmp.d+a[now.x][now.y];
            q.push(now);
            dis[now.x][now.y]=now.d;
            used[now.x][now.y]=true;
        }
        if(tmp.x<n && !used[tmp.x+1][tmp.y])
        {
            now.x=tmp.x+1;
            now.y=tmp.y;
            now.d=tmp.d+a[now.x][now.y];
            q.push(now);
            dis[now.x][now.y]=now.d;
            used[now.x][now.y]=true;
        }
        if(tmp.y>1 && !used[tmp.x][tmp.y-1])
        {
            now.x=tmp.x;
            now.y=tmp.y-1;
            now.d=tmp.d+a[now.x][now.y];
            q.push(now);
            dis[now.x][now.y]=now.d;
            used[now.x][now.y]=true;
        }
        if(tmp.y<n && !used[tmp.x][tmp.y+1])
        {
            now.x=tmp.x;
            now.y=tmp.y+1;
            now.d=tmp.d+a[now.x][now.y];
            q.push(now);
            dis[now.x][now.y]=now.d;
            used[now.x][now.y]=true;
        }
    }
}

long long solve(int x,int y)
{
    if(dp[x][y]!=-1)return dp[x][y];
    dp[x][y]=0;
    if(x>1&&dis[x][y]>dis[x-1][y])dp[x][y]+=solve(x-1,y);
    if(x<n&&dis[x][y]>dis[x+1][y])dp[x][y]+=solve(x+1,y);
    if(y>1&&dis[x][y]>dis[x][y-1])dp[x][y]+=solve(x,y-1);
    if(y<n&&dis[x][y]>dis[x][y+1])dp[x][y]+=solve(x,y+1);
    return dp[x][y];

}

int main()
{
    while(scanf("%d",&n)==1)
    {
        for(int i=1;i<=n;i++)
          for(int j=1;j<=n;j++)
          {
              scanf("%d",&a[i][j]);
              dp[i][j]=-1;
          }
        dp[n][n]=1;
        init();
        printf("%I64d\n",solve(1,1));
    }
    return 0;
}
