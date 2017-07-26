//���� Nim�� sg�������
//GCD ��չGCD �й�ʣ�ඨ�� ������ ��С��
//����� ����λ�� ȫ���� ������ ŷ������ �����ӷֽ�
//���� FFT Catalan ���ɺ��� �û� ��˹��Ԫ
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF=0x3f3f3f3f;
//std::ios::sync_with_stdio(false);
//freopen("test.txt","r",stdin);

/*
����
1. ������ֹ״̬��P״̬
2. ��һ������P״̬��״̬ΪN״̬
3. ÿһ����������N״̬��״̬ΪP״̬
�����ж�=��
���:��С����ö��x������x��������һ���ɴ��״̬����
û��P״̬������״̬�������о���N״̬���������P״̬

Ferguson:
���������ӣ�һ��ʼ����һ����m���Ƕ���һ����n���ǡ���������
״̬��Ϊ(m, n)��ÿ���߲��ǽ�һ��������ն�����һ�����ӵ�һЩ���õ�����յĺ�
���У�ʹ���������Ӹ�������һ����
m,n��Ϊ����,P;m,n����һ��Ϊż��,N

Chomp:
��һ��m �� n���̣�ÿ�ο���ȡ��һ�������õ����ұߺ��������
�з����õ����½ǵĸ���(1, 1)����
��m=n=1,P;����֮��,���־��б�ʤ����

Bash:
ֻ��һ��n����Ʒ�������������������Ʒ��ȡ��涨ÿ������ȡ1�������ȡm��
n%(m+1)!=0,����ȡ�߿϶���ʤ

Wythoff:
������ʯ�ӣ�һ���� m ������һ���� n ����
˫������ȡ��һЩʯ�ӣ��Ϸ���ȡ�����������֣�
1. ��һ��ʯ����ȡ�������ţ�
2. ������ʯ����ȡ����ͬ��������
�� k ��P״̬��
(floor(k*(sqrt(5)+1)*0.5)+k,floor(k*(sqrt(5)+1)*0.5))

Fibonacci:
˫������ȡn��ʯ�ӣ���������������
1. ���ֲ����ڵ�һ�ΰ����е�ʯ��ȡ�ꣻ
2. ֮��ÿ�ο���ȡ��ʯ�������� 1 �����ָ�ȡ��ʯ������ 2 ��֮�䣨���� 1 �Ͷ��ָ�ȡ��ʯ������ 2 ����
��� n ��쳲�����������P����֮��N��

Nim:
�����Ѹ����ɸ���Ʒ��������������ĳһ��ȡ������
��Ʒ���涨ÿ������ȡһ�������߲��ޣ����ȡ���ߵ�ʤ
Bouton����:XxorYxor...(Nim��)=0,P״̬;������N״̬

����ż����Ϸ:
��n�ѻ��ÿ���������ѡһ���á����κ�����£��������ż
������񣬵�����ȫ�����ߣ��������������񣬿���ȫ�����ߣ�Ҳ������ż������
��
g(2k) = k-1,��g(2k -1) = k

Lasker��s Nim��Ϸ:
��Nim��Ϸ���ƣ���ÿ�ο��԰�һ�ѷ�Ϊ������Ϊ�յĶѣ���
�����κλ��
g(4k+1)=4k+1,g(4k+2)=4k+2,g(4k+3)=4k+4,
g(4k+4)=4k+3

Kayles��Ϸ:
��һ�ѻ���ų�һ�š�ÿ�ο�������һ�����������������������
����һ���м䲻���п�϶�������ȡ�Ļ�ʤ
g(y + z)��x = 72��ʼ,��12Ϊ����ѭ����

Dawson������Ϸ:
��һ�и����˫�������ڸ����ﻮ�棬��ֹ��һ���Ѿ���X��
���ڸ����ﻮ�档���ܻ����䡣��һ�ѵ��м仮���൱��ȡ�����������Ժ�����ֳ�
���ѣ��ڱ��ϻ�X�൱���õ�2�����ӻ���1�����ӡ�
�����һ������x = 51�� SG������34Ϊ����ѭ��

����ķ�Ӳ����Ϸ�������ģ�һЩӲ���ų�һ�У��е����泯�ϣ��еķ��泯
�ϡ�ÿ�ο���ѡ��һЩӲ�ҷ�����������䷴�棬��������棩��Ϊ������Ϸ������
�޽�����ȥ�����踽�ӹ涨ÿ�η�ת�����ұ�һöӲ�ұ����Ǵ�����H��������T����
����ÿ�β��������ұߵ�H���������ƣ���������Ӳ�ұ��T���޷������ƶ�

Mock Turtle��Ϸ:
ÿ�ο��Է�ת1���� 2����3��Ӳ�ң��������ұ�һ������
��H��T��
��0��ʼ��ţ������Ʊ�ʾ��1�ĸ���Ϊ������������Ϊodious����
���x��odious������g(x) = 2x������g(x) = 2x + 1

Ruler��Ϸ�����Է������ö����Ӳ�ң�������һö�����Ǵ�H����T
��1��ʼ��ţ�g(x)��������x��2�����������

Acrostic Twins��Ϸ��
ÿ�η�����Ӳ�ң�Ҫôͬһ�У�Ҫôͬһ�У��������·���
�Ǹ�������H����T
g(x,y)=x xor y

Tartan���� ���g1(x)��G1��SG������ g2(x)��G2��SG��������G1 �� G2��SG��
��ֵΪ�� g(x, y)=g1(x),g2(y)��Nim��
*/
//HDU3404 Nim��
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int sg[20][20];
int f(int,int);//����һ�£���Ϊf��g����Ƕ�׵���
int g(int x, int y)//����2^x��2^y��nim��
{
    if(sg[x][y] != -1)//�鱸��¼
    {
        return sg[x][y];
    }
    if(!x)//x==0Ҳ����1��2^y��nim��������2^y
    {
        return sg[x][y] = 1<<y;
    }
    if(!y)//ͬ��
    {
        return sg[x][y] = 1<<x;
    }
    int ans=1,k=1,t;
    int x1=x,y1=y;
    while(x||y)//�ٽ�x��y��Ϊ�����ƣ����������Щ��ͨ�˻��ģ�����Ӧ������λ��ͬ�ģ�
    {
        t = 1<<k;//�Ӵ�λ�õ������յ���2^k
        if((x&1||y&1) && !((x&1)&&(y&1)))//��λ��ͬ
        {
            ans *= t;
        }
        x >>= 1;
        y >>= 1;
        k <<= 1;//�Ӵ�λ�õ���ָ��(����Ҳ��2����)
    }
    k = 1;
    x = x1;
    y = y1;
    while(x||y)//������Щ��ͬ��fermat 2-power �������ѵó�������nim��
    {
        t = 1<<k;
        if((x&1)&&(y&1))//��λ��ͬ
        {
            ans = f(ans,t/2*3);
        }
        x >>= 1;
        y >>= 1;
        k <<= 1;//�Ӵ�λ�õ���ָ��(����Ҳ��2����)
    }
    return (sg[x1][y1] = ans);
}
int f(int x, int y)//�����ά��nim��
{
    if(!x || !y)return 0;
    if(x == 1)return y;
    if(y == 1)return x;
    int ans = 0;
    for(int i = x,a = 0; i; i>>=1,a++)//��ɣ���x��y�ֽ�󣩰������ɼ������
    {
        if((i&1)==0)continue;//��λ��bit����1�ż��㣬��������
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
xor=Nim��
g(x)Ϊ�����ں�̵㺯��ֵ�����С�����С
�Ǹ�����������Ǻ�̵㺯��ֵ����ΪS����g(x) = mex(S)������mex(S)Ϊ����S��
����С�Ǹ����������磬���x��3����̵㣬 gֵ�ֱ�Ϊ0, 1, 1, 2, 4, 7����g(x) = 3��
��Ϊ3�ǵ�һ��û�г����ں�̵㺯��ֵ�еķǸ���������������̬��gֵ��ȻΪ0����
����ֵ������˳����������ݵ��ƹ�ϵ������һ��������ͼ�� SG������Ȼ��Ψһȷ��
�ġ�
����ֵ���������Ϸ��Grundyֵ������һ����0��nim�ͣ���ô��Ȼ����Ϸ��ĳ������д���һ������ʹ��nim�ͱ�Ϊ0��
����Ӧ��ִ�������������ô�������ǵĶ��־ͱ����ٴ�ʹ��nim�ͷ�0�����գ����ǽ���Ϊ�����һ����Ϸִ�����һ���������ˣ����nim�ͱ�Ϊ0.
���ಫ����Ϸ��һ���Խⷨ��
��һ��nԪ��(a1, a2, ��, an)����������Ϸ�����е�һ�����档
�÷���#S����ʾ����S����Ӧ�Ķ���������
�÷���$(x)����ʾ����(x)����һ�����п��ܳ��ֵľ���ļ��ϡ�
���弯��g(x)����$(x)={S1, S2, ��, Sk}����g(x)={#S1, #S2, ��, #Sk}������
��Ǹ�������Ϊȫ��������G(x)��ʾ����g(x)�Ĳ�����
���庯��f(n)��f(n)=min{G(n)}����f(n)���ڼ���G(n)�е���С����
�����S=(a1, a2, ��, an)��#S=f(a1)+f(a2)+��+f(an)�����ö��������ļӷ���
��#S��0�����������б�ʤ���ԣ���#S=0����������б�ʤ���ԡ�
*/
//sg function
int f[1000]={0,0,1,1};//��ʼ��ǰ4��
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
        if(g[k]!=k)//���䲹������Сֵ
        {
            f[i]=k;//�ҵ�f[i]
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
        if(s==0)printf("��ȡ����\n");
        else printf("��ȡ��Ӯ\n");
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
//Tartan���� ���g1(x)��G1��SG������ g2(x)��G2��SG��������G1 �� G2��SG��
//��ֵΪ�� g(x, y) = g1(x) xor g2(y)
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
//���һ��x,yʹ��ax+by=gcd(a,b)=d
//a*x+b*y=1 ���x��Ϊa%b����Ԫ,y��Ϊb%a����Ԫ
//A,B������ʱ��A^B mod C = A^(B mod phi(C)+phi(C))
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
//�����
LL combi(LL n,LL m)
{
    if (n==1||m==0||n==m) return dp[n][m]=1;
    if (dp[n][m]) return dp[n][m];
    return dp[n][m]=(c(n-1,m-1)%MOD+c(n-1,m)%MOD+MOD)%MOD;
}
//Stirling��ʽ��n!��λ��(n=1ʱ����)
res=(LL)((log10(sqrt(4.0*acos(0.0)*n))+n*(log10(n)-log10(exp(1.0))))+1);
//ȫ����
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
int phi[MAXN];//ŷ������
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
//ŷ������
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
// Miller_Rabin �㷨������������
//�ٶȿ죬���ҿ����ж� <2^63����
//****************************************************************
const int S=20;//����㷨�ж�������SԽ���д����ԽС
//���� (a*b)%c.   a,b����long long������ֱ����˿��������
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
//����  x^n %c
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
//��aΪ��,n-1=x*2^t      a^(n-1)=1(mod n)  ��֤n�ǲ��Ǻ���
//һ���Ǻ�������true,��һ������false
bool check(long long a,long long n,long long x,long long t)
{
    long long ret=pow_mod(a,x,n);
    long long last=ret;
    for(int i=1; i<=t; i++)
    {
        ret=mult_mod(ret,ret,n);
        if(ret==1&&last!=1&&last!=n-1) return true;//����
        last=ret;
    }
    if(ret!=1) return true;
    return false;
}
// Miller_Rabin()�㷨�����ж�
//����������true.(������α�����������ʼ�С)
//��������false;
bool Miller_Rabin(long long n)
{
    if(n<2)return false;
    if(n==2)return true;
    if((n&1)==0) return false;//ż��
    long long x=n-1;
    long long t=0;
    while((x&1)==0)
    {
        x>>=1;
        t++;
    }
    for(int i=0; i<S; i++)
    {
        long long a=rand()%(n-1)+1;//rand()��Ҫstdlib.hͷ�ļ�
        if(check(a,n,x,t))
            return false;//����
    }
    return true;
}
//************************************************
//pollard_rho �㷨�����������ֽ�
//************************************************
long long factor[100];//�������ֽ������շ���ʱ������ģ�
int tol;//�������ĸ���������С���0��ʼ
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
//��n���������ӷֽ�
void findfac(long long n)
{
    if(Miller_Rabin(n))//����
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
//FFT O(nlogn)����ʽ�˷�
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
//Catalan��
//����n�����öԽ����ʷ�Ϊ�����εķ�����ΪCn
//n�����ĳ˻�a1a2...an�Ĳ�ͬ��Ϸ�����ΪCn+1
//����������ƽ��ĸ����ϣ��ӵ�(0, 0)����(n, n)�ɴ�ֱ��ˮƽ�߶���
//�ɵ�·����Ҫ���м��(a, b)����a �� b����������y=x�������ߣ�����·��
//����ΪCn+2
//C2-C10��ֵ�ֱ�Ϊ1, 1, 2, 5, 14, 42, 132, 429, 1430
//����a[i]��������ci,b[i]�д�ų���,����2
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
���ɺ���
Fibonacci���ĵ��ƹ�ʽ��Fn=Fn1+Fn2,�߽���F1=F2=1,���������ɺ�����A(x),��
A(x) = F0 + F1x + F2x2 + F3x3 +...
xA(x) = 0 + F0x + F1x2 + F2x3 + ...
x2A(x) = 0 + 0 + F0x2 + F1x3 + ...
��һ����ʽ��ȥ��������ʽ����x2�͸�����ȫ����ȥ�������
���������ǵõ���Fn�����ɺ���

����������ˮ����ƻ��ֻ��ѡ������3�����㽶����������4�ı���������ֻ��ѡ2,3,5��
��������������������ɺ�����:
(1+x+x^2+x^3)(x^4+x^8+x^12+...)(x^2+x^3+x^5)
ѡ20��ˮ���������������ʽ��x^20���ϵ��
ѡ20��ˮ����������:(1+(1/1!)x+(1/2!)x^2+(1/3!)x^3)((1/4!)x^4+(1/8!)x^8+
(1/12!)x^12+...)((1/2!)x^2+(1/3!)x^3+(1/5!)x^5)
*/
/*
����һ���û�f��������s�任���Լ�������Ϊf�Ĳ����㡣f�Ĳ�������Ŀ��ΪC(f)
Burnside����:�ȼ�����ĿΪ����C(f)��ƽ��ֵ
Polya ����
�� G �� p �������һ���û�Ⱥ���� k ����ɫȥȾ�� p ��������һ��Ⱦɫ������Ⱥ G ����
���±�Ϊһ�ַ�����������������������ͬһ�ַ����������Ĳ�ͬȾɫ������Ϊ��
L=1/|G|*sum(k^c(f)),f����G
C(f)Ϊѭ���� |G|��ʾȺ���û�������

����n��Ԫ�ص�ѭ���ھ�����ЩСѭ���ڳ��ȵ���С������
�ҳ����е�Сѭ�����Ӷ�ΪO��n������Ϊÿ��λ����౻����һ��

���� n ��λ�õ������� n ����ת�û��� n �ַ�ת�û�
������ת�û���
C(fi ) =gcd(n,i),i ��ʾ��ת i �ű�ʯ�Ժ� i=0 ʱ gcd(n,0)=n
���ڷ�ת�û���
��� n Ϊż�������� n/2 ���û�C(f)=n/2,�� n/2 ���û�C(f)=n/2+`
��� n Ϊ���������� n ���û�C(f)=n/2
*/
#define eps 1e-9
const int MAXN=220;
double a[MAXN][MAXN],x[MAXN];//���̵���ߵľ���͵�ʽ�ұߵ�ֵ�����֮��x��ľ��ǽ��
int equ,var;//��������δ֪������
/*
*����0��ʾ�޽⣬ 1��ʾ�н�
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
