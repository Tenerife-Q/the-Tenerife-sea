/**
 * ============================================================
 * 第一讲：基础算法 - 浮点数二分
 * ============================================================
 * 
 * 核心思想：
 * 浮点数二分没有整数二分那么多边界问题（不需要 +1），非常简单。
 * 只需要保证循环次数足够，或者区间足够小。
 * 
 * 常见应用：
 * - 求三次方根
 * - 0/1 分数规划问题等
 */

#include <iostream>
#include <iomanip> // fixed, setprecision
using namespace std;

int main() {
    double x;
    // 练习：输入一个数，求它的三次方根
    // cout << "Input a float number: ";
    if(cin >> x) {
        // 确定范围：例如 -10000 到 10000
        double l = -10000, r = 10000;
        
        // 精度控制：比如要求保留 6 位小数，我们就多算两位，到 1e-8
        while (r - l > 1e-8) {
            double mid = (l + r) / 2;
            if (mid * mid * mid >= x) r = mid;
            else l = mid;
        }

        cout << fixed << setprecision(6) << l << endl;
    }

    return 0;
}
