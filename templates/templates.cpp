//二分 Kruskal Dijkstra Bellman-Ford Floyd
//割顶和桥 BCC SCC Dinic MCMF LCA 树
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
//LCA
/*
 * LCA  (POJ 1330)
 * 在线算法 DFS + ST O(nlogn)
 */
const int MAXN = 10010;
int rmq[2*MAXN];//rmq数组，就是欧拉序列对应的深度序列
struct ST
{
    int mm[2*MAXN];
    int dp[2*MAXN][20];//最小值对应的下标
    void init(int n)
    {
        mm[0] = -1;
        for(int i = 1;i <= n;i++)
        {
            mm[i] = ((i&(i-1)) == 0)?mm[i-1]+1:mm[i-1];
            dp[i][0] = i;
        }
        for(int j = 1; j <= mm[n];j++)
            for(int i = 1; i + (1<<j) - 1 <= n; i++)
                dp[i][j] = rmq[dp[i][j-1]] < rmq[dp[i+(1<<(j-1))][j-1]]?dp[i][j-1]:dp[i+(1<<(j-1))][j-1];
    }
    int query(int a,int b)//查询[a,b]之间最小值的下标
    {
        if(a > b)swap(a,b);
        int k = mm[b-a+1];
        return rmq[dp[a][k]] <= rmq[dp[b-(1<<k)+1][k]]?dp[a][k]:dp[b-(1<<k)+1][k];
    }
};
//边的结构体定义
struct Edge
{
    int to,next;
};
Edge edge[MAXN*2];
int tot,head[MAXN];

int F[MAXN*2];//欧拉序列，就是dfs遍历的顺序，长度为2*n-1,下标从1开始
int P[MAXN];//P[i]表示点i在F中第一次出现的位置
int cnt;

ST st;
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v)//加边，无向边需要加两次
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
void dfs(int u,int pre,int dep)
{
    F[++cnt] = u;
    rmq[cnt] = dep;
    P[u] = cnt;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        int v = edge[i].to;
        if(v == pre)continue;
        dfs(v,u,dep+1);
        F[++cnt] = u;
        rmq[cnt] = dep;
    }
}
void LCA_init(int root,int node_num)//查询LCA前的初始化
{
    cnt = 0;
    dfs(root,root,0);
    st.init(2*node_num-1);
}
int query_lca(int u,int v)//查询u,v的lca编号
{
    return F[st.query(P[u],P[v])];
}
bool flag[MAXN];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int N;
    int u,v;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        init();
        memset(flag,false,sizeof(flag));
        for(int i = 1; i < N;i++)
        {
            scanf("%d%d",&u,&v);
            addedge(u,v);
            addedge(v,u);
            flag[v] = true;
        }
        int root;
        for(int i = 1; i <= N;i++)
            if(!flag[i])
            {
                root = i;
                break;
            }
        LCA_init(root,N);
        scanf("%d%d",&u,&v);
        printf("%d\n",query_lca(u,v));
    }
    return 0;
}
/*
 * POJ 1470
 * 给出一颗有向树，Q个查询
 * 输出查询结果中每个点出现次数
 */
/*
 * LCA离线算法，Tarjan
 * 复杂度O(n+Q);
 */
const int MAXN = 1010;
const int MAXQ = 500010;//查询数的最大值

//并查集部分
int F[MAXN];//需要初始化为-1
int find(int x)
{
    if(F[x] == -1)return x;
    return F[x] = find(F[x]);
}
void bing(int u,int v)
{
    int t1 = find(u);
    int t2 = find(v);
    if(t1 != t2)
        F[t1] = t2;
}
//************************
bool vis[MAXN];//访问标记
int ancestor[MAXN];//祖先
struct Edge
{
    int to,next;
}edge[MAXN*2];
int head[MAXN],tot;
void addedge(int u,int v)
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

struct Query
{
    int q,next;
    int index;//查询编号
}query[MAXQ*2];
int answer[MAXQ];//存储最后的查询结果，下标0~Q-1
int h[MAXQ];
int tt;
int Q;

void add_query(int u,int v,int index)
{
    query[tt].q = v;
    query[tt].next = h[u];
    query[tt].index = index;
    h[u] = tt++;
    query[tt].q = u;
    query[tt].next = h[v];
    query[tt].index = index;
    h[v] = tt++;
}

void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
    tt = 0;
    memset(h,-1,sizeof(h));
    memset(vis,false,sizeof(vis));
    memset(F,-1,sizeof(F));
    memset(ancestor,0,sizeof(ancestor));
}

void LCA(int u)
{
    ancestor[u] = u;
    vis[u] = true;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        int v = edge[i].to;
        if(vis[v])continue;
        LCA(v);
        bing(u,v);
        ancestor[find(u)] = u;
    }
    for(int i = h[u];i != -1;i = query[i].next)
    {
        int v = query[i].q;
        if(vis[v])
        {
            answer[query[i].index] = ancestor[find(v)];
        }
    }
}

bool flag[MAXN];
int Count_num[MAXN];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    int u,v,k;
    while(scanf("%d",&n) == 1)
    {
        init();
        memset(flag,false,sizeof(flag));
        for(int i = 1;i <= n;i++)
        {
            scanf("%d:(%d)",&u,&k);
            while(k--)
            {
                scanf("%d",&v);
                flag[v] = true;
                addedge(u,v);
                addedge(v,u);
            }
        }
        scanf("%d",&Q);
        for(int i = 0;i < Q;i++)
        {
            char ch;
            cin>>ch;
            scanf("%d %d)",&u,&v);
            add_query(u,v,i);
        }
        int root;
        for(int i = 1;i <= n;i++)
            if(!flag[i])
            {
                root = i;
                break;
            }
        LCA(root);
        memset(Count_num,0,sizeof(Count_num));
        for(int i = 0;i < Q;i++)
            Count_num[answer[i]]++;
        for(int i = 1;i <= n;i++)
            if(Count_num[i] > 0)
                printf("%d:%d\n",i,Count_num[i]);
    }
    return 0;
}

//笛卡儿树(Cartesian Tree) 是一种特殊的堆，它根据一个长度为n的数组A建立。
//它的根是A的最小元素位置i，而左子树和右子树分别为A[1. . . i-1]和A[i+1. . . n]的笛卡儿树
//RMQ定理 数组A的Cartesian树记为C(A)，则RMQ(A, i, j) = LCA(C(A), i, j)
/*树的性质
以i为根的子树直径d[i] 以i为根的子树深度g[i] 结点i在原树中的深度depth[i]
g[i] = max{depth[i], g[j]}
d[i]= max{g[u]+g[v], d[j]}
设T(u, v)为原树删除边(u, v)后以v为顶点的有根树（ u为0表示不删除任何边），
d[u, v]为T(u, v)的深度，则有递推式d[u, v] = max{0, d[v, w] + 1}，
其中w是v不等于u的儿子
则每个结点i的最远点离它的距离就是d[0, i]，时间复杂度为O(n)
*/
