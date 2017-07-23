//树状数组 RMQ 线段树 treap splay
//主席树
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF=0x3f3f3f3f;
//BIT O(logn)
int vis[maxs];
int lowbit(int x){return x & -x;}
void add(int x,int v)
{
    while(x<=maxs)
    {
        vis[x]+=v;
        x+=lowbit(x);
    }
}
int sum(int x)
{
    int ret=0;
    while(x>0)
    {
        ret+=vis[x];
        x-=lowbit(x);
    }
    return ret;
}
//RMQ O(nlogn)
const int maxn=100010;
int st[20][maxn];
void RMQinit(int n)
{
    for(int i=1;i<=n;i++) scanf("%d",&st[0][i]);
    for(int i=1;i<18;i++)
        for(int j=1;j<=n;j++)
            if(j+(1<<i)-1>n) continue;
            else st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i-1)]);
}
int RMQ(int L,int R)
{
    int k=0;
    while((1<<(k+1))<=R-L+1) k++;
    return max(st[k][L],st[k][R-(1<<k)+1]);
}
//sequence tree O(logn)
#include<bits/stdc++.h>
using namespace std;
#define lson (cur*2)
#define rson (cur*2+1)
typedef long long LL;
const int INF=0x3f3f3f3f;
int Left;int Right;int v;int op;
const int maxn=(20005)<<4;
struct Node
{
    int sumv[maxn];int minv[maxn];int maxv[maxn];
    int addv[maxn];int setv[maxn];
    void pushup(int cur,int curl,int curr)//更新当前结点
    {
        if(curr>curl)//根据子结点的值，更新当前结点的值
        {
            sumv[cur]=sumv[lson]+sumv[rson];
            minv[cur]=min(minv[lson],minv[rson]);
            maxv[cur]=max(maxv[lson],maxv[rson]);
        }
        if(setv[cur]>=0)//如果当前结点有置数标记，根据置数标记的值，更新当前结点的值
        {
            minv[cur]=maxv[cur]=setv[cur];
            sumv[cur]=setv[cur]*(curr-curl+1);
        }
        if(addv[cur]!=0)//如果当前结点有加法标记，根据加法标记的值，更新当前结点的值（先置后加）
        {
            minv[cur]+=addv[cur];
            maxv[cur]+=addv[cur];
            sumv[cur]+=addv[cur]*(curr-curl+1);
        }
    }
    void pushdown(int cur)//向子结点传递标记
    {
        if(setv[cur]>=0)//如果当前结点有置数标记，把标记传给子结点，清空【子结点的加法标记】，和当前结点的置数标记
        {
            setv[lson]=setv[rson]=setv[cur];
            addv[lson]=addv[rson]=0;
            setv[cur]=-1;
        }
        if(addv[cur]!=0)//如果当前结点有加法标记，把标记传给子结点，清空当前结点的加法标记
        {
            addv[lson]+=addv[cur];
            addv[rson]+=addv[cur];
            addv[cur]=0;
        }
    }
    void update(int cur,int curl,int curr)
    {
        if(Left<=curl&&Right>=curr)
        {
            if(op==1) addv[cur]+=v;
            else
            {
                setv[cur]=v;
                addv[cur]=0;
            }
        }
        else
        {
            pushdown(cur);
            int mid=curl+(curr-curl)/2;
            if(Left<=mid) update(lson,curl,mid);
            else pushup(lson,curl,mid);
            if(Right>mid) update(rson,mid+1,curr);
            else pushup(rson,mid+1,curr);
        }
        pushup(cur,curl,curr);
    }
    int query(int cur,int curl,int curr,int &sm,int &mn,int &mx)
    {
        pushup(cur,curl,curr);
        if(Left<=curl&&Right>=curr)
        {
            sm=sumv[cur];
            mn=minv[cur];
            mx=maxv[cur];
        }
        else
        {
            pushdown(cur);
            int mid=curl+(curr-curl)/2;
            int lsm=0,lmn=INF,lmx=-INF;
            int rsm=0,rmn=INF,rmx=-INF;
            if(Left<=mid) query(lson,curl,mid,lsm,lmn,lmx);
            else pushup(lson,curl,mid);
            if(Right>mid) query(rson,mid+1,curr,rsm,rmn,rmx);
            else pushup(rson,mid+1,curr);
            sm=lsm+rsm;
            mn=min(lmn,rmn);
            mx=max(lmx,rmx);
        }
    }
}nds[25];//开二维矩阵，row=25（实际上可以拼接成一维线段树）
int main()
{
    //freopen("test.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int r,c,m;
    int q,w,x,y,z;
    while(scanf("%d%d%d",&r,&c,&m)==3)
    {

        memset(nds,0,sizeof(nds));
        for(int i=1;i<=r;i++)
        {
            memset(nds[i].setv,-1,sizeof(nds[i].setv));
            nds[i].setv[1]=0;
        }
        while(m--)
        {
            scanf("%d%d%d%d%d",&op,&w,&Left,&y,&Right);
            if(op==3)
            {
                int sm=0,mn=INF,mx=-INF;
                for(int i=w;i<=y;i++)
                {
                    int tsm,tmn,tmx;
                    nds[i].query(1,1,c,tsm,tmn,tmx);
                    sm+=tsm;mn=min(mn,tmn);mx=max(mx,tmx);
                }
                printf("%d %d %d\n",sm,mn,mx);
            }
            else
            {
                scanf("%d",&v);
                for(int i=w;i<=y;i++) nds[i].update(1,1,c);
            }
        }
    }
    return 0;
}
//Treap
struct treap
{
	int l,r,rnd,val;//son,priority,val
}t[1005];
void rturn(int &k)//left son to root
{
	int tmp=t[k].l;t[k].l=t[tmp].r;t[tmp].r=k;k=tmp;
}
void lturn(int &k)//right son to root
{
	int tmp=t[k].r;t[k].r=t[tmp].l;t[tmp].l=k;k=tmp;
}
void insert(int &k,int x)//current root,key
{
	if(k==0)
	{
		k=++cnt;
		t[k].val=x;t[k].rnd=rand();
		t[k].l=t[k].r=-1;
		return;
	}
    if(t[k].val==x)return;
	else if(x>t[k].val)
	{
		insert(t[k].r,x);
		if(t[t[k].r].rnd<t[k].rnd)lturn(k);//if right has larger rnd,move to root
	}
	else
	{
		insert(t[k].l,x);
		if(t[t[k].l].rnd<t[k].rnd)rturn(k);
	}
}
void remove(int &k,int x)
{
    if(x==t[k].val)
    {
        if(t[k].l!=-1&&t[k].r==-1) t[k]=t[k].l;
        else if(t[k].l==-1&&t[k].r!=-1) t[k]=t[k].r;
        else
        {
            int d=(t[t[k].l].rnd>t[t[k].r].rnd)?1:0;
            if(d)//left to root,remove from right
            {
                rturn(k);
                remove(t[k].r,x);
            }
            else
            {
                lturn(k);
                remove(t[k].l,x);
            }
        }
    }
    else if(x>t[k].val) remove(t[k].r,x);
	else remove(t[k].l,x);
}
void query(int k,int val)
{
    if(!k)return;
    if(t[k].val==val){return k;}
    if(t[k].val>val)query(t[k].l,val);
    else query(t[k].r,val);
}
//Splay
const int maxn=1005;
int n,size,root;
int ch[maxn][2],num[maxn],fa[maxn];
void pushup(int x){};
void rotate(int x,int &k)//exchange x with its father
{
    int y=fa[x],z=fa[y],l,r;
    if(ch[y][0]==x)l=0;else l=1;r=l^1;
    if(y==k)k=x;
    else{if(ch[z][0]==y)ch[z][0]=x;else ch[z][1]=x;}
    fa[x]=z;fa[y]=x;fa[ch[x][r]]=y;
    ch[y][l]=ch[x][r];ch[x][r]=y;
}
void splay(int x,int &k)// move x to k
{
	int y,z;
	while(x!=k)
	{
		y=fa[x],z=fa[y];
		if(y!=k)
		{
			if((ch[y][0]==x)^(ch[z][0]==y))rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
void insert(int x,int v)
{
    int y;
    while(true)
    {
        y=ch[x][num[x]<v];
        if(y==0)//new node
        {
            y=++size;
            num[y]=v;
            ch[y][0]=ch[y][1]=0;
            fa[y]=x;
            ch[x][num[x]<v]=y;
            break;
        }
        x=y;
    }
    splay(y,root);//move to root after insertion
}
void remove(int x)
{
	splay(x,root);
	if(ch[x][0]*ch[x][1]==0)//x has one child,make it root
	{root=ch[x][0]+ch[x][1];}
	else
	{
		int k=ch[x][1];
		while(ch[k][0])k=ch[k][0];//most left one in right tree
		ch[k][0]=ch[x][0];fa[ch[x][0]]=k;//k replace x
		root=ch[x][1];//right tree to root
	}
	fa[root]=0;
}
int pre(int x)//most right one in left tree
{
    int tmp=ch[x][0];
    while(ch[tmp][1])tmp=ch[tmp][1];
    return num[tmp];
}
int suc(int x)//most left one in right tree
{
    int tmp=ch[x][1];
    while(ch[tmp][0])tmp=ch[tmp][0];
    return num[tmp];
}
void merge(int left,int right)
{
    splay(left,num[left]);
    ch[left][1]=right;
    pushup(left);
}
void split(int &o,int k,int &left,int &right)
{
    splay(o,k);
    left=o;
    right=ch[o][1];
    ch[o][1]=0;
    pushup(left);
}
