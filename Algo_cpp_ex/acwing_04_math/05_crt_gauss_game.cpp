/**
 * 模块：第四讲 数学知识
 * 主题：中国剩余定理、高斯消元与博弈论 (CRT, Gauss, Game Theory)
 * 进阶：这些是 ICPC 中中高难度题目的核心。
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long LL;
const double eps = 1e-8; // 高斯消元浮点精度

// ==========================================
// 1. 扩展中国剩余定理 (Extended CRT)
// 一般的中国剩余定理 (CRT) 要求模数 $m_1, m_2, \dots$ 互质
// 当模数不满足互质条件时，必须使用 exgcd 两两合并方程：
// $x \equiv a_1 \pmod{m_1}$ 和 $x \equiv a_2 \pmod{m_2}$
// 满足的话，则必然存在 $k_1, k_2$ 使得 $x = k_1 * m_1 + a_1 = k_2 * m_2 + a_2$
// 即 $k_1 m_1 - k_2 m_2 = a_2 - a_1$，利用 exgcd 判断是否有解，若有解则可以把两个方程合并。

LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) { x = 1, y = 0; return a; }
    LL d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// m: 模数数组，a: 余数数组。返回 -1 无解。
LL excrt(int n, vector<LL>& m, vector<LL>& a) {
    bool has_ans = true;
    LL m1 = m[0], a1 = a[0]; // 当前的线性同余等式合并结果 x == a1 (mod m1)

    for (int i = 1; i < n; i++) {
        LL m2 = m[i], a2 = a[i];
        LL k1, k2;
        // 目标方程：$k1 * m1 - k2 * m2 = a2 - a1$
        LL d = exgcd(m1, m2, k1, k2);
        
        // 由裴蜀定理，方程有解的充要条件是 gcd(m1,m2) 整除右手边的常数 (a2-a1)
        if ((a2 - a1) % d) {
            has_ans = false;
            break;
        }

        // 求 k1 的特解
        // $k1 = k1 * ((a2 - a1) / d)$
        k1 *= (a2 - a1) / d;

        // k1 的通解为 k1 + k * (m2 / d)。我们需要 k1 在最小非负整数中
        LL t = m2 / d;
        k1 = (k1 % t + t) % t;

        // 更新 a1 和 m1 (即把方程组规模缩小 1)
        // 合并后的通式 $x = a1 + k1 * m1$ （新方程的右边 a_new）
        a1 = m1 * k1 + a1;

        // 合并后的新模数 $m_{new} = lcm(m1, m2) = m1 * m2 / gcd(m1, m2) = m1 * (m2 / d)$
        // 注意溢出所以用 `abs(m1 / d * m2)`
        m1 = abs(m1 / d * m2);
    }

    if (has_ans) return (a1 % m1 + m1) % m1;
    else return -1;
}

// ==========================================
// 2. 高斯消元法 (Gaussian Elimination) O(N^3)
// 化为上三角矩阵求唯一解、无穷多解或无解 (常用于概率期望 DP)

// 这里给出浮点数线性方程组的骨架
int gauss(int n, vector<vector<double>>& a) {
    int c, r; // c: col, r: row
    for (c = 0, r = 0; c < n; c++) {
        int t = r;
        for (int i = r + 1; i < n; i++)
            if (fabs(a[i][c]) > fabs(a[t][c])) t = i;

        if (fabs(a[t][c]) < eps) continue; // 当前列全是0，无法消元

        // 把绝对值最大行换到最顶端
        for (int i = c; i <= n; i++) swap(a[t][i], a[r][i]);

        // 化首位为1
        for (int i = n; i >= c; i--) a[r][i] /= a[r][c];

        // 把下面所有行的第 c 列消为 0
        for (int i = r + 1; i < n; i++)
            if (fabs(a[i][c]) > eps)
                for (int j = n; j >= c; j--)
                    a[i][j] -= a[r][j] * a[i][c];

        r++;
    }

    if (r < n) {
        for (int i = r; i < n; i++)
            if (fabs(a[i][n]) > eps) 
                return 2; // 无解：出现 0 == 常数
        return 1; // 无穷多组解
    }

    // 回代求最后的所有解倒推
    for (int i = n - 1; i >= 0; i--)
        for (int j = i + 1; j < n; j++)
            a[i][n] -= a[i][j] * a[j][n];

    return 0; // 有唯一解
}

// ==========================================
// 3. 博弈论 Nim 游戏 (Game Theory)
// n 堆石子，每次取任意多个，可以取一堆。
// 结论：当 $a_1 \oplus a_2 \oplus \dots \oplus a_n \neq 0$ 时，先手必胜。
bool nim_game(const vector<int>& piles) {
    int res = 0;
    for (int p : piles) {
        res ^= p;
    }
    return res != 0;
}

int main() {
    // Nim 游戏，如果石子堆有两个，分别是 2, 3，异或和不为0，先手必胜。
    cout << "Nim Game (2, 3) 结果: " << (nim_game({2, 3}) ? "先手必胜" : "后手必胜") << endl;
    return 0;
}
