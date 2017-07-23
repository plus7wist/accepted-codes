//二分 hash LCS LIS 双重BFS sg函数打表
//GCD 扩展GCD 中国剩余定理 快速幂 大步小步
//组合数 排列位数 全排列 素数表 欧拉函数 质因子分解
//矩阵 FFT Catalan 生成函数 置换
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF=0x3f3f3f3f;
//二分
int len;int a[]={1,2,3,3,4,5};
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
//Nim:XxorYxor...=0,P状态;否则是N状态
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
LL exgcd(LL a,LL b,LL &x,LL &y)
{
    if (b==0) { x=1,y=0;return a;}
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
    e=1;x [1]=0;
    for (i=1;i<m;i++){e=mulmod(e,a,n);if(!x.count(e)) x[e]=i;}
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
//Stirling公式求n!的位数(n=1时特判)
res=(LL)((log10(sqrt(4.0*acos(0.0)*n))+n*(log10(n)-log10(exp(1.0))))+1);
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
        if(b&1){ret+=a;ret%=c;}
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
    for(int i=1;i<=t;i++)
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
    while((x&1)==0){x>>=1;t++;}
    for(int i=0;i<S;i++)
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
        if(i==k){y=x0;k+=k;}
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
        for(int i=0;i<tol;i++)printf("%I64d ",factor[i]);
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
	for(int i=0;i<n;i++)
		rev[i]=(rev[i>>1]>>1)+((i&1)?(n>>1):0);
}
void fft(complex<lf>*y,int flag)
{
	for(int i=1;i<n;i++)
		if(i<rev[i])
			swap(y[i],y[rev[i]]);
	for(int k=2;k<=n;k<<=1)
    {
		complex<lf>tmp(cos(2*pi/k),flag*sin(2*pi/k));
		for(int i=0;i<n;i+=k)
			complex<lf>x(1,0);
		{
			for(int j=0;j<(k>>1);j++,x*=tmp)
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
	for(int i=0;i<=n1;i++)
	for(int i=0;i<=n1;i++)
		scanf("%lf",&a[i].real());
	for(int i=0;i<=n2;i++)
		scanf("%lf",&b[i].real());
	while(n<=n1+n2)n<<=1;
	init();
	fft(a,1),fft(b,1);
	for(int i=0;i<n;i++)
		c[i]=a[i]*b[i];
	fft(c,-1);
	for(int i=0;i<=n1+n2;i++)
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
    for(i=2;i<=100;i++)
    {
        for(j=0;j<len;j++)
        a[i][j]=a[i-1][j]*(4*(i-1)+2);
        carry=0;
        for(j=0;j<len;j++)
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
        for(j=len-1;j>=0;j--)
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
对于 n 个位置的手镯，有 n 种旋转置换和 n 种翻转置换
对于旋转置换：
C(fi ) =gcd(n,i),i 表示旋转 i 颗宝石以后。 i=0 时 gcd(n,0)=n
对于翻转置换：
如果 n 为偶数：则有 n/2 个置换C(f)=n/2,有 n/2 个置换C(f)=n/2+`
如果 n 为奇数：则有 n 个置换C(f)=n/2
*/
