#include <bits/stdc++.h>
using namespace std;

const int MAX=200'010;

int s[MAX];

int main() 
{
    int n, c;
    cin>>n>>c;

    for(int i=0; i<n; i++)
    {
        cin>>s[i];
    }   

    sort(s, s+n);
    int l=0, r=0;

    long long count=0;

    for(int i=0;i<n;i++)
    {
        while(s[i]-s[l]>c&&l<n)
        {
            l++;
        }
        while(s[i]-s[r]>=c&&r<n)
        {
            r++;
        }
        if(s[i]-s[l]==c)
        {
            count+=r-l;
        }
        
    }

    cout<<count<<endl;
    return 0;
}