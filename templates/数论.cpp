//博弈 Nim积 sg函数打表
//GCD 扩展GCD 中国剩余定理 快速幂 大步小步
//组合数 排列位数 全排列 素数表 欧拉函数 质因子分解
//矩阵 FFT Catalan 生成函数 置换 高斯消元
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF=0x3f3f3f3f;
//std::ios::sync_with_stdio(false);
//freopen("test.txt","r",stdin);

/*
博弈
1. 所有终止状态是P状态
2. 能一步到达P状态的状态为N状态
3. 每一步都将到达N状态的状态为P状态
不能行动=输
打表:从小到大枚举x，检查从x出发所有一步可达的状态中有
没有P状态（必输状态）。若有就是N状态，否则就是P状态

Ferguson:
有两个盒子，一开始其中一个有m个糖而另一个有n个糖。把这样的
状态记为(m, n)。每次走步是将一个盒子清空而把另一个盒子的一些糖拿到被清空的盒
子中，使得两个盒子各至少有一颗糖
m,n都为奇数,P;m,n至少一个为偶数,N

Chomp:
有一个m × n棋盘，每次可以取走一个方格并拿掉它右边和上面的所
有方格。拿到左下角的格子(1, 1)者输
当m=n=1,P;除此之外,先手均有必胜策略

Bash:
只有一堆n个物品，两个人轮流从这堆物品中取物，规定每次至少取1个，最多取m个
n%(m+1)!=0,则先取者肯定获胜

Wythoff:
有两堆石子，一堆有 m 个，另一堆有 n 个。
双方轮流取走一些石子，合法的取法有如下两种：
1. 在一堆石子中取走任意多颗；
2. 在两堆石子中取走相同多的任意颗
第 k 个P状态是
(floor(k*(sqrt(5)+1)*0.5)+k,floor(k*(sqrt(5)+1)*0.5))

Fibonacci:
双方轮流取n个石子，满足以下条件：
1. 先手不能在第一次把所有的石子取完；
2. 之后每次可以取的石子数介于 1 到对手刚取的石子数的 2 倍之间（包含 1 和对手刚取的石子数的 2 倍）
如果 n 是斐波那契数，则P；反之，N。

Nim:
有三堆各若干个物品，两个人轮流从某一堆取任意多的
物品，规定每次至少取一个，多者不限，最后取光者得胜
Bouton定理:XxorYxor...(Nim和)=0,P状态;否则是N状态

奇数偶数游戏:
有n堆火柴，每次你可以任选一堆拿。在任何情况下，你可以拿偶
数根火柴，但不能全部拿走；如果有奇数根火柴，可以全部拿走（也可以拿偶数根火
柴）
g(2k) = k-1,且g(2k -1) = k

Lasker’s Nim游戏:
和Nim游戏类似，但每次可以把一堆分为两个不为空的堆（不
拿走任何火柴）
g(4k+1)=4k+1,g(4k+2)=4k+2,g(4k+3)=4k+4,
g(4k+4)=4k+3

Kayles游戏:
有一堆火柴排成一排。每次可以拿走一根或者连续的两根（必须紧
挨在一起，中间不能有空隙），最后取的获胜
g(y + z)从x = 72开始,以12为周期循环。

Dawson棋盘游戏:
在一列格子里，双方轮流在格子里划叉，禁止在一个已经有X的
相邻格子里划叉。不能画者输。在一堆的中间划叉相当于取走三个格子以后把它分成
两堆，在边上画X相当于拿掉2个格子或者1个格子。
在最后一个例外x = 51后， SG函数以34为周期循环

经典的翻硬币游戏是这样的：一些硬币排成一列，有的正面朝上，有的反面朝
上。每次可以选择一些硬币翻过来（正面变反面，反面变正面）。为了让游戏不会无
限进行下去，还需附加规定每次翻转的最右边一枚硬币必须是从正面H翻到反面T。这
样，每次操作后“最右边的H”都会左移，最终所有硬币变成T，无法继续移动

Mock Turtle游戏:
每次可以翻转1个、 2个或3个硬币，其中最右边一个必须
是H到T。
从0开始编号，二进制表示中1的个数为奇数的数，称为odious数，
如果x是odious数，则g(x) = 2x，否则g(x) = 2x + 1

Ruler游戏：可以翻任意多枚连续硬币，但最右一枚必须是从H翻到T
从1开始编号，g(x)是能整除x的2的最大整数幂

Acrostic Twins游戏：
每次翻两个硬币，要么同一行，要么同一列，其中右下方的
那个必须由H翻成T
g(x,y)=x xor y

Tartan定理： 如果g1(x)是G1的SG函数， g2(x)是G2的SG函数，则G1 × G2的SG函
数值为： g(x, y)=g1(x),g2(y)的Nim积
*/
//HDU3404 Nim积
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int sg[20][20];
int f(int,int);//声明一下，因为f与g互相嵌套调用
int g(int x, int y)//计算2^x与2^y的nim积
{
    if(sg[x][y] != -1)//查备忘录
    {
        return sg[x][y];
    }
    if(!x)//x==0也就是1与2^y的nim积，等于2^y
    {
        return sg[x][y] = 1<<y;
    }
    if(!y)//同上
    {
        return sg[x][y] = 1<<x;
    }
    int ans=1,k=1,t;
    int x1=x,y1=y;
    while(x||y)//再将x和y分为二进制，这里计算那些普通乘积的（即对应二进制位不同的）
    {
        t = 1<<k;//从此位得到的最终的数2^k
        if((x&1||y&1) && !((x&1)&&(y&1)))//该位不同
        {
            ans *= t;
        }
        x >>= 1;
        y >>= 1;
        k <<= 1;//从此位得到的指数(本身也是2的幂)
    }
    k = 1;
    x = x1;
    y = y1;
    while(x||y)//计算那些相同的fermat 2-power 数，与已得出的数的nim积
    {
        t = 1<<k;
        if((x&1)&&(y&1))//该位相同
        {
            ans = f(ans,t/2*3);
        }
        x >>= 1;
        y >>= 1;
        k <<= 1;//从此位得到的指数(本身也是2的幂)
    }
    return (sg[x1][y1] = ans);
}
int f(int x, int y)//计算二维的nim积
{
    if(!x || !y)return 0;
    if(x == 1)return y;
    if(y == 1)return x;
    int ans = 0;
    for(int i = x,a = 0; i; i>>=1,a++)//完成（将x和y分解后）按分配律计算其积
    {
        if((i&1)==0)continue;//该位（bit）是1才计算，否则跳过
        for(int j = y,b = 0; j; j>>=1,b++)
        {
            if((j&1)==0)continue;
            ans ^= g(a,b);
        }
    }
    return ans;
}
int main()
{
    int x,y,t;
    int n,ans;
    scanf("%d",&t);
    while(t--)
    {
        memset(sg,-1,sizeof(sg));
        scanf("%d",&n);
        ans = 0;
        while(n--)
        {
            scanf("%d%d",&x,&y);
            ans ^= f(x,y);

        }
        puts(ans ? "Have a try, lxhgww." : "Don't waste your time.");
    }
    return 0;
}
/*
xor=Nim和
g(x)为“不在后继点函数值集合中”的最小
非负整数。如果记后继点函数值集合为S，则g(x) = mex(S)，其中mex(S)为不在S内
的最小非负整数。例如，如果x有3个后继点， g值分别为0, 1, 1, 2, 4, 7，则g(x) = 3，
因为3是第一个没有出现在后继点函数值中的非负整数。这样，终态的g值显然为0，而
其他值由拓扑顺序给出。根据递推关系，对于一个给定的图， SG函数显然是唯一确定
的。
如果轮到我们且游戏的Grundy值给出了一个非0的nim和，那么必然在游戏的某个组分中存在一个操作使得nim和变为0。
我们应该执行这个操作，那么接着我们的对手就被迫再次使得nim和非0。最终，我们将成为在最后一个游戏执行最后一个操作的人，最后将nim和变为0.
此类搏弈游戏的一般性解法：
用一个n元组(a1, a2, …, an)，来描述游戏过程中的一个局面。
用符号#S，表示局面S所对应的二进制数。
用符号$(x)，表示局面(x)的下一步所有可能出现的局面的集合。
定义集合g(x)：设$(x)={S1, S2, …, Sk}，则g(x)={#S1, #S2, …, #Sk}。　　
令非负整数集为全集，集合G(x)表示集合g(x)的补集。
定义函数f(n)：f(n)=min{G(n)}，即f(n)等于集合G(n)中的最小数。
设局面S=(a1, a2, …, an)，#S=f(a1)+f(a2)+…+f(an)，采用二进制数的加法。
若#S≠0，则先行者有必胜策略；若#S=0，则后行者有必胜策略。
*/
//sg function
int f[1000]={0,0,1,1};//初始化前4个
int g[500],c[1000];
int main()
{
    int i,j,k,m,n,s;
    for(i=4;i<=1000;i++)
    {
        m=0;
        for(j=1;j<=i/2;j++)
        {
            g[m++]=f[j-1]^f[i-j-1];
        }
        sort(g,g+m);
        for(k=0;;k++)
        if(g[k]!=k)//找其补集的最小值
        {
            f[i]=k;//找到f[i]
            break;
        }
    }
    while(scanf("%d",&n)!=EOF&&n)
    {
        for(i=0;i<n;i++)
            scanf("%d",c+i);
        s=0;
        for(i=0;i<n;i++)
         s=s^f[c[i]];
        if(s==0)printf("先取者输\n");
        else printf("先取者赢\n");
    }
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=(1<<20);
int sg[maxn];
int vis[23];
void print()
{
    for(int i=0; i<maxn; i++)
    {
        memset(vis,0,sizeof(vis));
        int lst=-1;
        for(int j=0; j<20; j++) //offset
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
//Tartan定理： 如果g1(x)是G1的SG函数， g2(x)是G2的SG函数，则G1 × G2的SG函
//数值为： g(x, y) = g1(x) xor g2(y)
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
//A,B不互质时，A^B mod C = A^(B mod phi(C)+phi(C))
LL exgcd(LL a,LL b,LL &x,LL &y)
{
    if (b==0)
    {
        x=1,y=0;
        return a;
    }
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
    if(!b)
    {
        d=a;
        x=1;
        y=0;
    }
    else
    {
        exgcd(b,a%b,d,y,x);
        y-=x*(a/b);
    }
}
int china(int n,int a[],int m[])
{
    int M=1,dummy;
    for(int i=0; i<n; i++) M*=m[i];
    for(int i=0; i<n; i++)
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
    LL a=x/T;
LL b=x%T:
         LL c=y/T;
    LL d=y%T;
    LL e=a*c/T;
    LL f=a*c%T;
    LL v=((a*d+b*c)%n+e*t)%n;
    LL g=v/T;
    LL h=v%T;
    LL ans=(((f+g)*t%n+b*d)%n+h*T);
    while(ans<0) ans+=n;
    return ans;
}
LL powmod(LL a,LL n,LL p)
{
    LL ans=1,d=a%p;
    do
    {
        if(n&1) ans=mulmod(ans,d,p);
        d=mulmod(d,d,p);
    }
    while(n>>=1);
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
          e=1;
    x [1]=0;
    for (i=1; i<m; i++)
    {
        e=mulmod(e,a,n);
        if(!x.count(e)) x[e]=i;
    }
    for (i=0; i<m; i++)
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
//Stirling公式求n!的位数(n=1时特判)
res=(LL)((log10(sqrt(4.0*acos(0.0)*n))+n*(log10(n)-log10(exp(1.0))))+1);
//全排列
void range(int a[],int k,int n)
{
    if(k==n)
    {
        for(int i=1; i<=n; i++)
            printf("%d",a[i]);
        printf("\n");
    }
    for(int i=k; i<=n; i++)
    {
        swap(a[k],a[i]);
        range(a,k+1,n);
        swap(a[k],a[i]);
    }
}
//prime&euler
int t;
int cnt=0;
int prime[MAXN];
bool vis[MAXN];
int phi[MAXN];//欧拉函数
void Prime(int n)
{
    int cnt=0;
    memset(vis,0,sizeof(vis));
    for(int i=2; i<n; i++)
    {
        if(!vis[i])
        {
            prime[cnt++]=i;
            phi[i]=i-1;
        }
        for(int j=0; j<cnt&&i*prime[j]<n; j++)
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
//欧拉函数
int main()
{
    int n,i,sum;
    while(scanf("%d",&n)!=EOF)
    {
        sum=n;
        for(i=2; i*i<=n; i++)
        {
            if(n%i==0)
                sum=sum*(i-1)/i;
            while(n%i==0)
                n/=i;
        }
        if(n>1)
            sum=sum*(n-1)/n;
        printf("%d\n",sum);
    }
    return 0;
}
//****************************************************************
// Miller_Rabin 算法进行素数测试
//速度快，而且可以判断 <2^63的数
//****************************************************************
const int S=20;//随机算法判定次数，S越大，判错概率越小
//计算 (a*b)%c.   a,b都是long long的数，直接相乘可能溢出的
//  a,b,c <2^63
long long mult_mod(long long a,long long b,long long c)
{
    a%=c;
    b%=c;
    long long ret=0;
    while(b)
    {
        if(b&1)
        {
            ret+=a;
            ret%=c;
        }
        a<<=1;
        if(a>=c)a%=c;
        b>>=1;
    }
    return ret;
}
//计算  x^n %c
long long pow_mod(long long x,long long n,long long mod)//x^n%c
{
    if(n==1)return x%mod;
    x%=mod;
    long long tmp=x;
    long long ret=1;
    while(n)
    {
        if(n&1) ret=mult_mod(ret,tmp,mod);
        tmp=mult_mod(tmp,tmp,mod);
        n>>=1;
    }
    return ret;
}
//以a为基,n-1=x*2^t      a^(n-1)=1(mod n)  验证n是不是合数
//一定是合数返回true,不一定返回false
bool check(long long a,long long n,long long x,long long t)
{
    long long ret=pow_mod(a,x,n);
    long long last=ret;
    for(int i=1; i<=t; i++)
    {
        ret=mult_mod(ret,ret,n);
        if(ret==1&&last!=1&&last!=n-1) return true;//合数
        last=ret;
    }
    if(ret!=1) return true;
    return false;
}
// Miller_Rabin()算法素数判定
//是素数返回true.(可能是伪素数，但概率极小)
//合数返回false;
bool Miller_Rabin(long long n)
{
    if(n<2)return false;
    if(n==2)return true;
    if((n&1)==0) return false;//偶数
    long long x=n-1;
    long long t=0;
    while((x&1)==0)
    {
        x>>=1;
        t++;
    }
    for(int i=0; i<S; i++)
    {
        long long a=rand()%(n-1)+1;//rand()需要stdlib.h头文件
        if(check(a,n,x,t))
            return false;//合数
    }
    return true;
}
//************************************************
//pollard_rho 算法进行质因数分解
//************************************************
long long factor[100];//质因数分解结果（刚返回时是无序的）
int tol;//质因数的个数。数组小标从0开始
long long gcd(long long a,long long b)
{
    if(a==0)return 1;//???????
    if(a<0) return gcd(-a,b);
    while(b)
    {
        long long t=a%b;
        a=b;
        b=t;
    }
    return a;
}
long long Pollard_rho(long long x,long long c)
{
    long long i=1,k=2;
    long long x0=rand()%x;
    long long y=x0;
    while(1)
    {
        i++;
        x0=(mult_mod(x0,x0,x)+c)%x;
        long long d=gcd(y-x0,x);
        if(d!=1&&d!=x) return d;
        if(y==x0) return x;
        if(i==k)
        {
            y=x0;
            k+=k;
        }
    }
}
//对n进行素因子分解
void findfac(long long n)
{
    if(Miller_Rabin(n))//素数
    {
        factor[tol++]=n;
        return;
    }
    long long p=n;
    while(p>=n)p=Pollard_rho(p,rand()%(n-1)+1);
    findfac(p);
    findfac(n/p);
}
int main()
{
    long long n;
    while(scanf("%I64d",&n)!=EOF)
    {
        tol=0;
        findfac(n);
        for(int i=0; i<tol; i++)printf("%I64d ",factor[i]);
        printf("\n");
        if(Miller_Rabin(n))printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
//matrix
typedef struct node
{
    LL m[N][N];
    void Init()
    {
        memset(m,0,sizeof(m));
        for(int i=0; i<N; i++)
            m[i][i]=1;
    }
} matrix;
matrix mul(matrix a,matrix b)
{
    matrix ans;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
        {
            ans.m[i][j]=0;
            for(int k=0; k<N; k++)
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
//FFT O(nlogn)多项式乘法
#include<iostream>
#include<cstdio>
#include<complex>
#include<cmath>
using namespace std;
typedef double lf;
const lf pi=acos(-1);
const int maxn=300005;
complex<lf>a[maxn],b[maxn],c[maxn];
int rev[maxn],n=1;
void init()
{
    for(int i=0; i<n; i++)
        rev[i]=(rev[i>>1]>>1)+((i&1)?(n>>1):0);
}
void fft(complex<lf>*y,int flag)
{
    for(int i=1; i<n; i++)
        if(i<rev[i])
            swap(y[i],y[rev[i]]);
    for(int k=2; k<=n; k<<=1)
    {
        complex<lf>tmp(cos(2*pi/k),flag*sin(2*pi/k));
        for(int i=0; i<n; i+=k)
            complex<lf>x(1,0);
        {
            for(int j=0; j<(k>>1); j++,x*=tmp)
            {
                complex<lf>y0=y[i+j],y1=y[i+j+(k>>1)];
                y[i+j]=y0+x*y1;
                y[i+j+(k>>1)]=y0-x*y1;
            }
        }
    }
}
int main()
{
    int n1,n2;
    scanf("%d%d",&n1,&n2);
    for(int i=0; i<=n1; i++)
        for(int i=0; i<=n1; i++)
            scanf("%lf",&a[i].real());
    for(int i=0; i<=n2; i++)
        scanf("%lf",&b[i].real());
    while(n<=n1+n2)n<<=1;
    init();
    fft(a,1),fft(b,1);
    for(int i=0; i<n; i++)
        c[i]=a[i]*b[i];
    fft(c,-1);
    for(int i=0; i<=n1+n2; i++)
        printf("%d ",(int)(c[i].real()/n+0.5));
    return 0;
}
//Catalan数
//将正n边形用对角线剖分为三角形的方法数为Cn
//n个数的乘积a1a2...an的不同结合方法数为Cn+1
//在整数坐标平面的格子上，从点(0, 0)到点(n, n)由垂直和水平线段组
//成的路径，要求中间点(a, b)满足a ≤ b（即必须在y=x的上面走），则路径
//条数为Cn+2
//C2-C10的值分别为1, 1, 2, 5, 14, 42, 132, 429, 1430
//以下a[i]中逆序存放ci,b[i]中存放长度,特判2
void catalan()
{
    int i, j, len, carry, temp;
    a[1][0]=b[1]=1;
    len=1;
    for(i=2; i<=100; i++)
    {
        for(j=0; j<len; j++)
            a[i][j]=a[i-1][j]*(4*(i-1)+2);
        carry=0;
        for(j=0; j<len; j++)
        {
            temp=a[i][j]+carry;
            a[i][j]=temp%10;
            carry=temp/10;
        }
        while(carry)
        {
            a[i][len++]=carry%10;
            carry/=10;
        }
        carry=0;
        for(j=len-1; j>=0; j--)
        {
            temp=carry*10+a[i][j];
            a[i][j]=temp/(i+1);
            carry=temp%(i+1);
        }
        while(!a[i][len-1])
            len--;
        b[i]=len;
    }
}
/*
生成函数
Fibonacci数的递推公式是Fn=Fn1+Fn2,边界是F1=F2=1,设它的生成函数是A(x),则
A(x) = F0 + F1x + F2x2 + F3x3 +...
xA(x) = 0 + F0x + F1x2 + F2x3 + ...
x2A(x) = 0 + 0 + F0x2 + F1x3 + ...
第一个等式减去后两个等式，则x2和更高项全部消去，因此有
这样，我们得到了Fn的生成函数

假设有三种水果，苹果只能选不超过3个，香蕉个数必须是4的倍数，桃子只能选2,3,5个
则这个排列组合问题的生成函数是:
(1+x+x^2+x^3)(x^4+x^8+x^12+...)(x^2+x^3+x^5)
选20个水果的组合数就是上式中x^20项的系数
选20个水果的排列数:(1+(1/1!)x+(1/2!)x^2+(1/3!)x^3)((1/4!)x^4+(1/8!)x^8+
(1/12!)x^12+...)((1/2!)x^2+(1/3!)x^3+(1/5!)x^5)
*/
/*
对于一个置换f，若方案s变换到自己，称它为f的不动点。f的不动点数目记为C(f)
Burnside引理:等价类数目为所有C(f)的平均值
Polya 定理
设 G 是 p 个对象的一个置换群，用 k 种颜色去染这 p 个对象，若一种染色方案在群 G 的作
用下变为一种方案，则这两个方案当作是同一种方案，这样的不同染色方案数为：
L=1/|G|*sum(k^c(f)),f属于G
C(f)为循环节 |G|表示群的置换方法数

所有n个元素的循环节就是这些小循环节长度的最小公倍数
找出所有的小循环复杂度为O（n），因为每个位置最多被遍历一次

对于 n 个位置的手镯，有 n 种旋转置换和 n 种翻转置换
对于旋转置换：
C(fi ) =gcd(n,i),i 表示旋转 i 颗宝石以后。 i=0 时 gcd(n,0)=n
对于翻转置换：
如果 n 为偶数：则有 n/2 个置换C(f)=n/2,有 n/2 个置换C(f)=n/2+`
如果 n 为奇数：则有 n 个置换C(f)=n/2
*/
#define eps 1e-9
const int MAXN=220;
double a[MAXN][MAXN],x[MAXN];//方程的左边的矩阵和等式右边的值，求解之后x存的就是结果
int equ,var;//方程数和未知数个数
/*
*返回0表示无解， 1表示有解
*/
int Gauss()
{
    int i,j,k,col,max_r;
    for(k=0,col=0; k<equ&&col<var; k++,col++)
    {
        max_r=k;
        for(i=k+1; i<equ; i++)
            if(fabs(a[i][col])>fabs(a[max_r][col]))
                max_r=i;
        if(fabs(a[max_r][col])<eps)return 0;
        if(k!=max_r)
        {
            for(j=col; j<var; j++)
                swap(a[k][j],a[max_r][j]);
            swap(x[k],x[max_r]);
        }
        x[k]/=a[k][col];
        for(j=col+1; j<var; j++)a[k][j]/=a[k][col];
        a[k][col]=1;
        for(i=0; i<equ; i++)
            if(i!=k)
            {
                x[i]-=x[k]*a[i][k];
                for(j=col+1; j<var; j++)a[i][j]-=a[k][j]*a[i][col];
                a[i][col]=0;
            }
    }
    return 1;
}
