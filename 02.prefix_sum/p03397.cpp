#include <bits/stdc++.h>
using namespace std;

int main()
{
    int size, carpets_count;
    cin>>size>>carpets_count;

    vector<vector<int>> ranges(size+2, vector<int>(size+2, 0));

    for(int i=1;i<=carpets_count;i++)
    {
        int x1, y1, x2, y2;
        cin>>x1>>y1>>x2>>y2;

        ranges[x1][y1]++;
        ranges[x1][y2+1]--;
        ranges[x2+1][y1]--;
        ranges[x2+1][y2+1]++;
    }

    for(int i=1;i<=size;i++)
    {
        for(int j=1;j<=size;j++)
        {
            ranges[i][j]=ranges[i][j]+ranges[i-1][j]+ranges[i][j-1]-ranges[i-1][j-1];
            cout<<ranges[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}