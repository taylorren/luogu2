#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

/**
 * UVA11572 - Unique Snowflakes
 * 问题描述：
 * Emily想要包装雪花，但一个包裹里不能有两片相同的雪花。
 * 给定一系列雪花的标记，求最大可能的包裹大小（不含重复雪花）。
 * 
 * 解题思路：
 * 1. 使用滑动窗口法，维护一个不包含重复雪花的窗口
 * 2. 用哈希表记录每种雪花上次出现的位置
 * 3. 当遇到重复雪花时，将窗口起始位置移动到上次出现位置之后
 * 4. 不断更新最大窗口大小
 */

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        int snowflakes[n];
        for (int i = 0; i < n; i++) {
            cin >> snowflakes[i];
        }
        
        unordered_map<int, int> last_pos; // 记录每种雪花上次出现的位置
        int start = 0; // 当前窗口的起始位置
        int max_size = 0; // 最大包裹大小
        
        for (int i = 0; i < n; i++) {
            int snowflake = snowflakes[i];
            
            // 如果当前雪花已经在窗口中出现过
            if (last_pos.count(snowflake) && last_pos[snowflake] >= start) {
                // 更新窗口起始位置到上次出现位置之后
                start = last_pos[snowflake] + 1;
            }
            
            // 更新当前雪花的位置
            last_pos[snowflake] = i;
            
            // 更新最大包裹大小
            max_size = max(max_size, i - start + 1);
        }
        
        cout << max_size << endl;
    }
    
    return 0;
}