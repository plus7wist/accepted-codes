#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=50005;
char op[maxn<<3];//���������50000����㣬�����ַ����50000����̫С��RE
int vis[maxn];int nc;
char *p;int ks;
struct nodes
{
    string s;//�����string��ɼ򻯺ܶ�
    int ls,rs;int nhash;
    bool operator <(const nodes &rhs) const
    {
        if(nhash!=rhs.nhash) return nhash<rhs.nhash;
        if(ls!=rhs.ls) return ls<rhs.ls;
        return rs<rhs.rs;
}
}node[maxn];
map<nodes,int>ids;//���ٲ��ҽ��
void print(int cur)
{
    if(vis[cur])//���ʹ�����ӡ���
    {
        printf("%d",cur+1);
        return;
    }
    vis[cur]=1;
    printf("%s",node[cur].s.c_str());//stringתchar
    if(node[cur].ls!=-1)//������
    {
        printf("(");
        print(node[cur].ls);
        printf(",");
        print(node[cur].rs);
        printf(")");
    }
}
int build_tree()
{
    int u=nc++;
    nodes &cur=node[u];
    cur.ls=-1;cur.rs=-1;cur.nhash=0;cur.s="";
    while(isalpha(*p))
    {
        cur.s.push_back(*p);
        cur.nhash=cur.nhash*27+*p-'a'+1;//���hash����ѡ��ò��ûᱻ������
        p++;
    }

    if(*p=='(')//������
    {
        //cout<<p<<endl;
        p++;
        cur.ls=build_tree();
        p++;
        cur.rs=build_tree();
        p++;
    }

    if(ids.count(cur)!=0)//�ɽ��
    {
        u--,nc--;
        return ids[cur];
    }
    return ids[cur]=u;//�������
}
int main()
{
    //freopen("test.txt","r",stdin);
    int t;scanf("%d",&t);
    for(ks=1;ks<=t;ks++)
    {
        nc=0;ids.clear();memset(vis,0,sizeof(vis));
        scanf("%s",op);
        p=op;//��ŵ�ǰ��ӡλ�õ�ȫ��ָ��
        int u=build_tree();
        print(u);
        printf("\n");
    }
    return 0;
}