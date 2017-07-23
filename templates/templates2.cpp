#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF=0x3f3f3f3f;
//DJB hash
LL hashed(char str[])
{
    int len=strlen(str);
    LL hasher=5381;
    for(int i=0;i<len;i++)
        hasher=((hasher<<5)+hasher)+str[i];
    return hasher;
}
//LCS
char a[m];char b[n];int d[n];
int solve()
{
    for(int i=0;i<=n;i++) d[i]=0;
    for(int i=1;i<=m;i++)
    {
        int t=0;int v;
        for(int j=1;j<=n;j++)
        {
            if(a[i]==b[j]) v=t+1;
            else v=max(d[j],d[j-1]);
            t=d[j];
            d[j]=v;
        }
    }
    return d[n];
}
//LIS
int a[n];int g[n];int d[n];
int solve()
{
    for(int i=0;i<n;i++)
    {
        int j=lower_bound(g,g+n,a[i])-g;
        d[i]=j+1;
        g[j]=a[i];
    }
    return d[n-1];
}
//d-BFS
bool doubleBFS(int a,int b)
{
    memset(vis1,0,sizeof(vis1));
    memset(vis2,0,sizeof(vis2));
    queue<int>q1,q2;
    q1.push(a);q2.push(b);
    while(!q1.empty()||!q2.empty())
    {
        int s1=q1.size();int s2=q2.size();
        while(q1--)
        {
            int fr=q1.front();q1.pop();
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
//sg function
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=(1<<20);
int sg[maxn];int vis[23];
void print()
{
    for(int i=0;i<maxn;i++)
    {
        memset(vis,0,sizeof(vis));
        int lst=-1;
        for(int j=0;j<20;j++)//offset
            if(!((i>>j)&1)) lst=j;//destination pos
            else if (~lst)
            {
                vis[sg[i^(1<<j)^(1<<lst)]]=1;//move j to lst
            }
        for(int j=0;;j++)
            if(!vis[j])
            {
                sg[i]=j;
                break;
            }
        //printf("%d %d\n",i,sg[i]);
    }
}
int main()
{
    print();
    //freopen("test.txt","r",stdin);
    int t,n,m,tmp;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        int ans=0;
        while(n--)
        {
            scanf("%d",&m);
            int cur=0;//set of current row
            while(m--)
            {
                scanf("%d",&tmp);
                cur^=1<<(20-tmp);
            }
            ans^=sg[cur];//tot ans
        }
        if(ans) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}
//GCD
LL gcd(LL a,LL b)
{
    while(b)
    {
        LL t=a%b;
        a=b;
        b=t;
    }
    return a;
}
//extend GCD
//求解一组x,y使得ax+by=gcd(a,b)=d
//a*x+b*y=1 求得x即为a%b的逆元,y即为b%a的逆元
LL exgcd(LL a,LL b,LL &x,LL &y)
{
    if (b==0) { x=1,y=0; return a; }
    LL d=exgcd(b,a%b,x,y);
    LL tmp=x;
    x=y;
    y=tmp-a/b*y;
    return d;
}
//Chinese remainder
//x identically equals a1(mod m1),x identically equals a2(mod a2)...
//get x
void exgcd(int a,int b,int &d,int &x,int &y)
{
    if(!b){d=a;x=1;y=0;}
    else
    {
        exgcd(b,a%b,d,y,x);
        y-=x*(a/b);
    }
}
int china(int n,int a[],int m[])
{
    int M=1,dummy;
    for(int i=0;i<n;i++) M*=m[i];
    for(int i=0;i<n;i++)
    {
        int w=M/m[i];
        exgcd(m[i],w,dummy,dummy,y);
        x=(x+y*w*a[i])%M;
    }
    return (n+x%M)%M;
}
//fast pow
LL fpow(LL a,LL b)
{
    LL ans=1;
    while(b)
    {
        if(b&1) ans=(ans*a)%mod;
        a=(a*a)%mod;
        b/=2;
    }
    return ans;
}
//safer a^n mod p
LL mulmod(LL x,LL y,LL n)
{
    LL T=floor(sqrt(n)+0.5);
    LL t=T*T-n;
    LL a=x/T;LL b=x%T:LL c=y/T;LL d=y%T;
    LL e=a*c/T;LL f=a*c%T;
    LL v=((a*d+b*c)%n+e*t)%n;
    LL g=v/T;LL h=v%T;
    LL ans=(((f+g)*t%n+b*d)%n+h*T);
    while(ans<0) ans+=n;
    return ans;
}
LL powmod(LL a,LL n,LL p)
{
    LL ans=1,d=a%p;
    do{
        if(n&1) ans=mulmod(ans,d,p);
        d=mulmod(d,d,p);
    }while(n>>=1);
    return ans;
}
//BSGS
//x^y identically equals z(mod p),given x,z,p,get y
LL inv(LL a,LL b)
{
    LL ret,dummy;
    exgcd(a,b,ret,dummy);
    return dummy;
}
LL logmod(LL a,LL b,LL n)
{
    map<int,int>x;
    int m=(int)ceil(sqrt(n));
    int v=inv()
    e = 1; x [1] = 0;
    for (i=1;i<m;i++){e=mulmod(e,a,n); if(!x.count(e)) x[e]=i;}
    for (i=0;i<m;i++)
    {
        if(x.count(b)) return i*m+x[b];
        b= mulmod(b,v,n);
    }
}
//组合数
LL combi(LL n,LL m)
{
    if (n==1||m==0||n==m) return dp[n][m]=1;
    if (dp[n][m]) return dp[n][m];
    return dp[n][m]=(c(n-1,m-1)%MOD+c(n-1,m)%MOD+MOD)%MOD;
}
//全排列
void range(int a[],int k,int n)
{
    if(k==n)
    {
        for(int i=1;i<=n;i++)
            printf("%d",a[i]);
        printf("\n");
    }
    for(int i=k;i<=n;i++)
    {
        swap(a[k],a[i]);
        range(a,k+1,n);
        swap(a[k],a[i]);
    }
}
//prime&euler
int t;int cnt=0;
int prime[MAXN];bool vis[MAXN];
int phi[MAXN];//欧拉函数
void Prime(int n)
{
    int cnt=0;
    memset(vis,0,sizeof(vis));
    for(int i=2;i<n;i++)
    {
        if(!vis[i])
        {
            prime[cnt++]=i;
            phi[i]=i-1;
        }
        for(int j=0;j<cnt&&i*prime[j]<n;j++)
        {
            LL k=i*prime[j];
            vis[k]=1;
            if(i%prime[j]==0)
            {
                phi[k]=phi[i]*prime[j];
                break;
            }
            else phi[k]=phi[i]*(prime[j]-1);
        }
    }
}
//matrix
typedef struct node
{
    LL m[N][N];
    void Init()
    {
        memset(m,0,sizeof(m));
        for(int i=0;i<N;i++)
            m[i][i]=1;
    }
}matrix;
matrix mul(matrix a,matrix b)
{
    matrix ans;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            ans.m[i][j]=0;
            for(int k=0;k<N;k++)
                ans.m[i][j]+=(a.m[i][k]*b.m[k][j])%MOD;
            ans.m[i][j]%=MOD;
        }
    return ans;
}
matrix pow(matrix a,int n)
{
    matrix ans;
    ans.Init();
    while(n)
    {
        if(n%2)
            ans=mul(ans,a);
        n/=2;
        a=mul(a,a);
    }
    return ans;
}

