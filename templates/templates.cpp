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
//无根树转有根树
//vector<int>G[maxn]存放边
//主程序中p[root]=-1,dfs(root,-1);
void dfs(int u,int fa)//递归转化以u为根的子树，u的父节点为fa
{
    int d=G[u].size();
    for(int i=0;i<d;i++)
    {
        int v=G[u][i];
        if(v!=fa) dfs(v,p[v]=u);
    }
}
//Kruskal O(ElogE)
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
int Kruskal(int cnt,vector<Edge>e,vector<Edge>&use)//cnt:cc的数量
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
    int ans=Kruskal(n,edge,need);
    return ans;
}
//Dijkstra O(ElogV)
const int maxn=1005;const int INF=0x3f3f3f3f;
struct Edge
{
    int from,to,dist;
    Edge(int u,int v,int d):from(u),to(v),dist(d){}
};
struct HeapNode
{
    int d,u;
    HeapNode(int dd,int uu):d(dd),u(uu){}
    bool operator <(const HeapNode &rhs) const
    {
        return d>rhs.d;
    }
};
struct dijkstra
{
    int n,m;
    vector<Edge>edges;vector<int>G[maxn];bool done[maxn];int d[maxn];int p[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=0;i<n;i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from,int to,int dist)
    {
        edges.push_back(Edge(from,to,dist));
        m=edges.size();G[from].push_back(m-1);
    }
    void Dijkstra(int s)
    {
        priority_queue<HeapNode> Q;
        for(int i=0;i<n;i++){d[i]=INF;done[i]=0;}
        d[s]=0;
        Q.push(HeapNode(0,s));
        while(!Q.empty())
        {
            HeapNode x=Q.top();Q.pop();
            int u=x.u;if(done[u]) continue;
            done[u]=1;int sz=G[u].size();
            for(int i=0;i<sz;i++)
            {
                Edge&e=edges[G[u][i]];
                if(d[e.to]>d[u]+e.dist)
                {
                    d[e.to]=d[u]+e.dist;
                    p[e.to]=G[u][i];
                    Q.push(HeapNode(d[e.to],e.to));
                }
            }
        }
    }
};
//Bellman-Ford O(EV)
const int maxn=1005;const int INF=0x3f3f3f3f;int n,m;
int inq[maxn];int cnt[maxn];int d[maxn];int p[maxn];
vector<int>G[maxn];
struct Edge
{
    int from,to,dist;
    Edge(int u,int v,int d):from(u),to(v),dist(d){}
};vector<Edge>edges;
bool BellmanFord(int s)
{
    queue<int>Q;
    memset(inq,0,sizeof(inq));
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<n;i++) d[i]=INF;d[s]=0;
    inq[s]=1;Q.push(s);
    while(!Q.empty())
    {
        int u=Q.front();Q.pop();
        inq[u]=0;int sz=G[u].size();
        for(int i=0;i<sz;i++)
        {
            Edge&e=edges[G[u][i]];
            if(d[u]<INF&&d[e.to]>d[u]+e.dist)
            {
                d[e.to]=d[u]+e.dist;
                p[e.to]=G[u][i];
                if(!inq[e.to])
                {
                    Q.push(e.to);
                    inq[e.to]=1;
                    if(++cnt[e.to]>n) return 0;
                }
            }
        }
    }
    return 1;
}
//Floyd
const int maxn=1005;const int INF=0x3f3f3f3f;int n,m;
int d[maxn][maxn];
void floyd()
{
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(d[i][k]<INF&&d[k][j]<INF)
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
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
//DFS
vector<int>G[maxn];int vis[maxn];int cc;int n;
void dfs(int u)
{
    vis[u]=1;
    //previsit(u);
    int d=G[u].size();
    for(int i=0;i<d;i++)
    {
        int v=G[u][i];
        if(!vis[v]) dfs(v);
    }
    //postvisit(u);
}
void find_cc()
{
    cc=0;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;i++)
        if(!vis[i])
        dfs(i),cc++;
}
bool isbip(int u)
{
    int d=G[u].size();
    for(int i=0;i<d;i++)
    {
        int v=G[u][i];
        if(color[v]==color[i]) return 0;
        if(!color[v])
        {
            color[v]=3-color[i];
            if(!isbip(v)) return 0;
        }
    }
    return 1;
}
///无向图的割顶,桥,BCC
vector<int>G[maxn];
vector<pair<int,int> >bridges;
int iscut[maxn];int pre[maxn];int low[maxn];
int dfs_clock=0;
int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    int child=0;int sz=G[u].size();
    for(int i=0;i<sz;i++)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            child++;
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
            if(lowv>=pre[u])
            {
                iscut[u]=1;
                if(lowv!=pre[u])bridges.push_back(pair<int,int>(v,u));
            }
        }
        else if(pre[v]<pre[u]&&v!=fa)//visited,less pre,not father(back edge)
            lowu=min(lowu,pre[v]);
    }
    if(fa<0&&child==1) iscut[u]=0;
    low[u]=lowu;
    return lowu;
}
int pre[maxn],iscut[maxn],bccno[maxn],dfs_clock,bcc_cnt;
vector<int>G[maxn],bcc[maxn];
struct Edge
{
    int u;int v;
};
stack<Edge>S;
int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    int child=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        Edge e=(Edge){u,v};
        if(!pre[v])
        {
            S.push(e);
            child++;
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
            if(lowv>=pre[u])//find new cut
            {
                iscut[u]=1;
                bcc_cnt++;bcc[bcc_cnt].clear();//initialize current bcc
                while(1)
                {
                    Edge x=S.top();S.pop();//last visited edge
                    if(bccno[x.u]!=bcc_cnt)//point not in bcc,add
                    {
                        bcc[bcc_cnt].push_back(x.u);
                        bccno[x.u]=bcc_cnt;
                    }
                    if(bccno[x.v]!=bcc_cnt)//point not in bcc,add
                    {
                        bcc[bcc_cnt].push_back(x.v);
                        bccno[x.v]=bcc_cnt;
                    }
                    if(x.u==u&&x.v==v) break;
                }
            }
            else if(pre[v]<pre[u]&&v!=fa)//back edge
            {
                S.push(e);
                lowu=min(lowu,pre[v]);
            }
        }
    }
    if(fa<0&&child==1) iscut[u]=0;
    return lowu;
}
void find_bcc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    dfs_clock=bcc_cnt=0;
    for(int i=0;i<n;i++)
    {
        if(!pre[i]) dfs(i,-1);
    }
}
///有向图SCC
vector<int>G[maxn];
int pre[maxn],lowlink[maxn],sccno[maxn],dfs_clock,scc_cnt;
stack<int>S;
void dfs(int u)
{
    pre[u]=lowlink[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i>G[u].size();i++)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            dfs(v);
            lowlink[u]=min(lowlink[u],lowlink[v]);
        }
        else if(!sccno[v])
        {
            lowlink[u]=min(lowlink[u],pre[v]);
        }
    }
    if(lowlink[u]==pre[u])
    {
        scc_cnt++;
        while(1)
        {
            int x=S.top();S.pop();
            sccno[x]=scc_cnt;
            if(x==u) break;
        }
    }
}
void find_scc(int n)
{
    dfs_clock=scc_cnt=0;
    memset(sccno,0,sizeof(sccno));
    memset(pre,0,sizeof(pre));
    for(int i=0;i<n;i++)
        if(!pre[i]) dfs(i);
}
//Dinic
struct Edge {
  int from, to, cap, flow;
};

bool operator < (const Edge& a, const Edge& b) {
  return a.from < b.from || (a.from == b.from && a.to < b.to);
}

struct Dinic {
  int n, m, s, t;
  vector<Edge> edges;    // 边数的两倍
  vector<int> G[maxn];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
  bool vis[maxn];         // BFS使用
  int d[maxn];           // 从起点到i的距离
  int cur[maxn];        // 当前弧指针

  void ClearAll(int n) {
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void ClearFlow() {
    for(int i = 0; i < edges.size(); i++) edges[i].flow = 0;
  }

  void AddEdge(int from, int to, int cap) {
    edges.push_back((Edge){from, to, cap, 0});
    edges.push_back((Edge){to, from, 0, 0});
    m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
  }

  bool BFS() {
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(s);
    vis[s] = 1;
    d[s] = 0;
    while(!Q.empty()) {
      int x = Q.front(); Q.pop();
      for(int i = 0; i < G[x].size(); i++) {
        Edge& e = edges[G[x][i]];
        if(!vis[e.to] && e.cap > e.flow) {
          vis[e.to] = 1;
          d[e.to] = d[x] + 1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }

  int DFS(int x, int a) {
    if(x == t || a == 0) return a;
    int flow = 0, f;
    for(int& i = cur[x]; i < G[x].size(); i++) {
      Edge& e = edges[G[x][i]];
      if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap-e.flow))) > 0) {
        e.flow += f;
        edges[G[x][i]^1].flow -= f;
        flow += f;
        a -= f;
        if(a == 0) break;
      }
    }
    return flow;
  }

  int Maxflow(int s, int t) {
    this->s = s; this->t = t;
    int flow = 0;
    while(BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }

  vector<int> Mincut() { // call this after maxflow
    vector<int> ans;
    for(int i = 0; i < edges.size(); i++) {
      Edge& e = edges[i];
      if(vis[e.from] && !vis[e.to] && e.cap > 0) ans.push_back(i);
    }
    return ans;
  }

  void Reduce() {
    for(int i = 0; i < edges.size(); i++) edges[i].cap -= edges[i].flow;
  }
};
//ISAP
struct Edge {
  int from, to, cap, flow;
};

bool operator < (const Edge& a, const Edge& b) {
  return a.from < b.from || (a.from == b.from && a.to < b.to);
}

struct ISAP {
  int n, m, s, t;
  vector<Edge> edges;
  vector<int> G[maxn];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
  bool vis[maxn];        // BFS使用
  int d[maxn];           // 从起点到i的距离
  int cur[maxn];        // 当前弧指针
  int p[maxn];          // 可增广路上的上一条弧
  int num[maxn];        // 距离标号计数

  void AddEdge(int from, int to, int cap) {
    edges.push_back((Edge){from, to, cap, 0});
    edges.push_back((Edge){to, from, 0, 0});
    m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
  }

  bool BFS() {
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(t);
    vis[t] = 1;
    d[t] = 0;
    while(!Q.empty()) {
      int x = Q.front(); Q.pop();
      for(int i = 0; i < G[x].size(); i++) {
        Edge& e = edges[G[x][i]^1];
        if(!vis[e.from] && e.cap > e.flow) {
          vis[e.from] = 1;
          d[e.from] = d[x] + 1;
          Q.push(e.from);
        }
      }
    }
    return vis[s];
  }

  void ClearAll(int n) {
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void ClearFlow() {
    for(int i = 0; i < edges.size(); i++) edges[i].flow = 0;
  }

  int Augment() {
    int x = t, a = INF;
    while(x != s) {
      Edge& e = edges[p[x]];
      a = min(a, e.cap-e.flow);
      x = edges[p[x]].from;
    }
    x = t;
    while(x != s) {
      edges[p[x]].flow += a;
      edges[p[x]^1].flow -= a;
      x = edges[p[x]].from;
    }
    return a;
  }

  int Maxflow(int s, int t, int need) {
    this->s = s; this->t = t;
    int flow = 0;
    BFS();
    memset(num, 0, sizeof(num));
    for(int i = 0; i < n; i++) num[d[i]]++;
    int x = s;
    memset(cur, 0, sizeof(cur));
    while(d[s] < n) {
      if(x == t) {
        flow += Augment();
        if(flow >= need) return flow;
        x = s;
      }
      int ok = 0;
      for(int i = cur[x]; i < G[x].size(); i++) {
        Edge& e = edges[G[x][i]];
        if(e.cap > e.flow && d[x] == d[e.to] + 1) { // Advance
          ok = 1;
          p[e.to] = G[x][i];
          cur[x] = i; // 注意
          x = e.to;
          break;
        }
      }
      if(!ok) { // Retreat
        int m = n-1; // 初值注意
        for(int i = 0; i < G[x].size(); i++) {
          Edge& e = edges[G[x][i]];
          if(e.cap > e.flow) m = min(m, d[e.to]);
        }
        if(--num[d[x]] == 0) break;
        num[d[x] = m+1]++;
        cur[x] = 0; // 注意
        if(x != s) x = edges[p[x]].from;
      }
    }
    return flow;
  }

  vector<int> Mincut() { // call this after maxflow
    BFS();
    vector<int> ans;
    for(int i = 0; i < edges.size(); i++) {
      Edge& e = edges[i];
      if(!vis[e.from] && vis[e.to] && e.cap > 0) ans.push_back(i);
    }
    return ans;
  }

  void Reduce() {
    for(int i = 0; i < edges.size(); i++) edges[i].cap -= edges[i].flow;
  }

//Min Cost Max Flow
struct Edge {
  int from, to, cap, flow, cost;
  Edge(int u, int v, int c, int f, int w):from(u),to(v),cap(c),flow(f),cost(w) {}
};

struct MCMF {
  int n, m;
  vector<Edge> edges;
  vector<int> G[maxn];
  int inq[maxn];         // 是否在队列中
  int d[maxn];           // Bellman-Ford
  int p[maxn];           // 上一条弧
  int a[maxn];           // 可改进量

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int cap, int cost) {
    edges.push_back(Edge(from, to, cap, 0, cost));
    edges.push_back(Edge(to, from, 0, 0, -cost));
    m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
  }

  bool BellmanFord(int s, int t, int& flow, int& cost) {
    for(int i = 0; i < n; i++) d[i] = INF;
    memset(inq, 0, sizeof(inq));
    d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

    queue<int> Q;
    Q.push(s);
    while(!Q.empty()) {
      int u = Q.front(); Q.pop();
      inq[u] = 0;
      for(int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
          d[e.to] = d[u] + e.cost;
          p[e.to] = G[u][i];
          a[e.to] = min(a[u], e.cap - e.flow);
          if(!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
        }
      }
    }
    if(d[t] == INF) return false;
    flow += a[t];
    cost += d[t] * a[t];
    for(int u = t; u != s; u = edges[p[u]].from) {
      edges[p[u]].flow += a[t];
      edges[p[u]^1].flow -= a[t];
    }
    return true;
  }

  // 需要保证初始网络中没有负权圈
  int MincostMaxflow(int s, int t, int& cost) {
    int flow = 0; cost = 0;
    while(BellmanFord(s, t, flow, cost));
    return flow;
  }
  //有流量上限的情况
  bool BellmanFord(int s, int t, int flow_limit, int& flow, int& cost) {
    for(int i = 0; i < n; i++) d[i] = INF;
    memset(inq, 0, sizeof(inq));
    d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

    queue<int> Q;
    Q.push(s);
    while(!Q.empty()) {
      int u = Q.front(); Q.pop();
      inq[u] = 0;
      for(int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
          d[e.to] = d[u] + e.cost;
          p[e.to] = G[u][i];
          a[e.to] = min(a[u], e.cap - e.flow);
          if(!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
        }
      }
    }
    if(d[t] == INF) return false;
    if(flow + a[t] > flow_limit) a[t] = flow_limit - flow;
    flow += a[t];
    cost += d[t] * a[t];
    for(int u = t; u != s; u = edges[p[u]].from) {
      edges[p[u]].flow += a[t];
      edges[p[u]^1].flow -= a[t];
    }
    return true;
  }

  int MincostFlow(int s, int t, int flow_limit, int& cost) {
    int flow = 0; cost = 0;
    while(flow < flow_limit && BellmanFord(s, t, flow_limit, flow, cost));
    return flow;
  }

};
