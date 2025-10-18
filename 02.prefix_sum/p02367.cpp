#include <bits/stdc++.h>
using namespace std;

int main()
{
    int student_number, counts;
    cin >> student_number >> counts;

    vector<int> scores(student_number + 1, 0);
    vector<int> diff_scores(student_number + 1, 0);
    for (int i = 1; i <= student_number; i++)
    {
        cin >> scores[i];
        diff_scores[i] = scores[i] - scores[i - 1];  // 计算差分数组
    }

    for (int i = 1; i <= counts; i++)

    {
        int x, y, z;
        cin >> x >> y >> z;
        diff_scores[x] += z;
        diff_scores[y + 1] -= z;
    }

    int min = 101;  // scores are within [0,100]
    for (int i = 1; i <= student_number; i++)
    {
        diff_scores[i] += diff_scores[i - 1];
        if (diff_scores[i] < min)
        {
            min = diff_scores[i];
        }
    }

    cout << min << endl;
    return 0;
}