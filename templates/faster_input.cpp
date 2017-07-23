#include<bits/stdc++.h>
const int INF = 0x3f3f3f3f, MAXN = 1000000;
char buf[MAXN], *ps = buf, *pe = buf+1;
inline void rnext()
{
    if(++ps == pe)
        pe = (ps = buf)+fread(buf,1,sizeof(buf),stdin);
}
template <class T>
inline bool read(T &ans)
{
	  ans = 0;
	  T f = 1;
    if(ps == pe) return false;
    do{
        rnext();
		if('-' == *ps) f = -1;
    }while(!isdigit(*ps) && ps != pe);
    if(ps == pe) return false;
    do
    {
        ans = (ans<<1)+(ans<<3)+*ps-48;
        rnext();
    }while(isdigit(*ps) && ps != pe);
	  ans *= f;
    return true;
}
int a[100];int b[100];
int main()
{
    std::ios::sync_with_stdio(false);
    for(int i=0;i<100;i++)
    {
        read(a[i]);
        cin>>b[i];
    }
    return 0;
}
