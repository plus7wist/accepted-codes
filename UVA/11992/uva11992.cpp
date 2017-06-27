//本题同样是数组开小不判RE，直接WA，如果Udebug没有问题，但是却wa，
//可能是输出格式问题(win和linux,int和longlong)或者数组大小问题
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
    void pushup(int cur,int curl,int curr)
    {
        if(curr>curl)
        {
            sumv[cur]=sumv[lson]+sumv[rson];
            minv[cur]=min(minv[lson],minv[rson]);
            maxv[cur]=max(maxv[lson],maxv[rson]);
        }
        if(setv[cur]>=0)
        {
            minv[cur]=maxv[cur]=setv[cur];
            sumv[cur]=setv[cur]*(curr-curl+1);
        }
        if(addv[cur]!=0)
        {
            minv[cur]+=addv[cur];
            maxv[cur]+=addv[cur];
            sumv[cur]+=addv[cur]*(curr-curl+1);
        }
    }
    void pushdown(int cur)
    {
        if(setv[cur]>=0)
        {
            setv[lson]=setv[rson]=setv[cur];
            addv[lson]=addv[rson]=0;
            setv[cur]=-1;
        }
        if(addv[cur]!=0)
        {
            addv[lson]+=addv[cur];
            addv[rson]+=addv[cur];
            addv[cur]=0;
        }
    }
    //y1,y2 is Left,Right,L is curl,R is curr
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
}nds[25];
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
