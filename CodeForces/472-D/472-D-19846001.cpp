/*
��1��Ϊ����������������������ֹ�ϵ��
1.һ����λ����һ����������ϡ����㵽1�ľ���֮�����ֵ����������롣
2.��������ĳһ����Ĳ�ͬ�����ϡ����㵽1����֮�ͼ�ȥ��������������ĳ���㵽1�ľ��롣
*/
#include<iostream>  
#include<cstdio>  
#include<cstdlib>  
#include<string.h>  
#include<math.h>  
#include<algorithm>  
#include<vector>  
#include<queue>  
#include<map>  
using namespace std;  
int n;  
long long mp[2005][2005];  
map <long long,int> m;  
int main()  
{  
    int n;  
    cin>>n;  
    for(int i=1;i<=n;i++)  
        for(int j=1;j<=n;j++)  
            scanf("%I64d",&mp[i][j]);  
    for(int i=1;i<=n;i++)  
        for(int j=1;j<=n;j++)  
        {  
            if((i==j && mp[i][j]) || (i!=j && mp[i][j]==0) || mp[i][j]!=mp[j][i])  
            {  
                cout<<"NO"<<endl;  
                return 0;  
            }  
        }  
    for(int i=1;i<=n;i++)  
        m[2*mp[1][i]]=1;  
    for(int i=1;i<=n;i++)  
    {  
        for(int j=1;j<=n;j++)  
        {  
            if((mp[i][j]==abs(mp[1][i]-mp[1][j])) || m[mp[1][j]+mp[1][i]-mp[i][j]])continue;  
            cout<<"NO"<<endl;  
            return 0;  
        }  
    }  
    cout<<"YES"<<endl;  
    return 0;  
}