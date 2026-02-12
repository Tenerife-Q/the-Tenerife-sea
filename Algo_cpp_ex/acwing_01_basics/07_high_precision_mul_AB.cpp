/**
 * ============================================================
 * 第一讲：基础算法 - 高精度乘法 (A * B) - 进阶版
 * ============================================================
 * 
 * 算法来源：参考董晓算法模板
 * 复杂度：O(N * M)
 * 
 * 💡 为什么这个算法思想很厉害？
 * 1. 数学抽象：
 *    它直击了乘法的本质——多项式卷积。
 *    A = a[i]*10^i, B = b[j]*10^j
 *    A*B 的每一项就是 (a[i]*b[j]) * 10^(i+j)
 *    这意味着我们不需要关心当前是第几层竖式，只需要无脑把 a[i]*b[j] 累加到 c[i+j] 即可。
 * 
 * 2. 状态压缩：
 *    它不需要“中间数组”来存每一层的乘积结果，直接在一个结果数组 c 上不断叠加、进位。
 *    把复杂的“错位相加”转化为了简单的“下标求和 (i+j)”。
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 建议开全局，有些题目数据大容易栈溢出
const int N = 100005; // 假设最大位数
int a[N], b[N], c[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string sa, sb;
    // cout << "Input two large numbers A and B: ";
    if (cin >> sa >> sb) {
        int la = sa.size();
        int lb = sb.size();

        // 1. 倒序存储
        // sa = "123" -> a=[3, 2, 1]
        for (int i = 0; i < la; i++) a[i] = sa[la - 1 - i] - '0';
        for (int i = 0; i < lb; i++) b[i] = sb[lb - 1 - i] - '0';

        // 2. 核心计算 (卷积模拟)
        // c[i+j] 的位置可能积累了多次乘积的和
        for (int i = 0; i < la; i++) {
            for (int j = 0; j < lb; j++) {
                c[i + j] += a[i] * b[j];       // 累加乘积
                c[i + j + 1] += c[i + j] / 10; // 进位直接甩给下一位
                c[i + j] %= 10;                // 当前位只留个位
            }
        }

        // 3. 确定结果长度并去除前导零
        // 两个数相乘，位数最多是 la + lb (比如 99*99=9801, 2位*2位=4位)
        // 最少是 la + lb - 1 (比如 10*10=100, 2位*2位=3位)
        int lc = la + lb;
        while (lc > 0 && c[lc] == 0) lc--; // 因为从 lc 开始看，如果是 0 就往回退

        // 4. 倒序打印
        for (int i = lc; i >= 0; i--) cout << c[i];
        cout << endl;
    }

    return 0;
}
