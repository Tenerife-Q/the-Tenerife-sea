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
// ==========================================
/*
 * [破局核心]
 * 普通的中国剩余定理 (CRT) 具有极其严格的前提：模数必须“两两互质”，否则逆元无法计算，算法瘫痪。
 * EXCRT 彻底打破了“模数互质”的限制，通过将多个方程两两合并，把 N 个方程逐步收缩为 1 个。
 *
 * [数学推导与物理意义]
 * 假设我们要合并两个方程：
 * 1. x ≡ a1 (mod m1)  =>  x = k1 * m1 + a1
 * 2. x ≡ a2 (mod m2)  =>  x = k2 * m2 + a2
 *
 * 令两式相等得：k1 * m1 - k2 * m2 = a2 - a1 
 * 这是一个标准的二元一次不定方程。我们借助 exgcd(m1, m2) 求出 d = gcd(m1, m2)，
 * 随之判定是否有解，并求出其特解与通解，最后生成能够同时满足前两个方程的新周期（新模数）与新起跑线（新余数）。
 */

LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) { x = 1, y = 0; return a; }
    LL d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// m: 模数数组，a: 余数数组。返回 -1 无解。
LL excrt(int n, vector<LL>& m, vector<LL>& a) {
    bool has_ans = true;
    
    // 初始化：用首个方程作为原始基底。此时 x ≡ a1 (mod m1) 
    LL m1 = m[0], a1 = a[0]; 

    for (int i = 1; i < n; i++) {
        LL m2 = m[i], a2 = a[i];
        LL k1, k2;
        
        // 【Step 1】目标等式：k1 * m1 - k2 * m2 = (a2 - a1)
        // 调用 exgcd 求出最大公约数 d，并附带解出基础等式 k1*m1 + k2*m2 = d 的一组解
        LL d = exgcd(m1, m2, k1, k2);
        
        // 【Step 2】裴蜀定理校验
        // 若等式右边的常数 (a2 - a1) 不能被系统公约数 d 整除，则方程必定无解。
        if ((a2 - a1) % d != 0) {
            has_ans = false;
            break;
        }

        // 【Step 3】求目标等式的【特解】(Particular Solution)
        // 我们利用等比例放大，将基础解放大 (a2 - a1) / d 倍，得到真正的 k1 特解
        k1 *= (a2 - a1) / d;

        // 【Step 4】利用通解性质执行收割：挑选出最安全的【最小非负整数特解】
        // 增量周期 t 为什么是 m2/d？
        // 根据非齐次方程的通解 = 特解 + 齐次方程(m1*k1 - m2*k2 = 0)的解。
        // 两边除以d后：(m1/d)*k1 = (m2/d)*k2。由于 (m1/d) 和 (m2/d) 必定互质，
        // 从而推导出 k1 的增长步长必须是 t = m2/d 的整数倍。
        // 所以 k1 真正的【通解】集合为：k1_new = k1 + y * t（y为任意整数）。
        // 
        // 既然通解有无数个（选哪个代入下一步在数学上都对），我们面临两个工程问题：
        // 1. 防溢出：如果 k1 极大，下一步 a1 = m1 * k1 会直接撑爆 long long。
        // 2. 防负数：如果 k1 是负数，下一步算出的新余数 a1 也是负数，会破坏后续同余逻辑。
        // 破局方案：在 C++ 中，% t 操作本质上就是在不断加/减 t。
        // 语句 `(k1 % t + t) % t` 的真正物理含义是：自动加上或减去若干个周期 t，
        // 在无限个通解中，帮你找出那个唯一落在 [0, t-1] 区间内、绝对安全的极小正数代表！
        LL t = m2 / d;
        k1 = (k1 % t + t) % t;

        // 【Step 5】生成新世代的合并方程，降维规模并进入下一轮
        // a) 算出这个确定的 k1 对应的最小数 x，这是自然界中第一个同时满足上述两个规律的数
        //    这个数将作为新方程的新常数项（新余数）
        a1 = m1 * k1 + a1;

        // b) 由于既要是 m1 的周期，又要是 m2 的周期，所以共同的新周期必然是两者的最小公倍数 (LCM)
        //    LCM(m1, m2) = m1 * m2 / d
        //    计算时必须先除后乘防止溢出，并加上 abs 防错
        m1 = abs(m1 / d * m2);
    }

    // 历经 N-1 次循环吞噬，最终只剩下一个唯一的规律方程：x ≡ a1 (mod m1)
    // 答案就是我们最后求出的那个被小心翼翼限制在 [0, m1-1] 内的基底 a1
    if (has_ans) return (a1 % m1 + m1) % m1;
    else return -1;
}

/*
LL excrt(int n, vector<int>& m, vector<int>& a) {
    bool has_ans = true;
    LL m1 = m[0], a1 = a[0];
    for(int i = 1; i <  n; i++ ) {
        LL m2 = m[i], a2 = a[i];
        LL k1, k2;
        LL d = exgcd(m1, m2, k1, k2);
        if((a2 - a1) % d != 0) {
            has_ans = false;
            break;
        }
        k1 *= (a2 - a1) / d;
        LL t = m2 / d;
        k1 = (k1 % t + t) % t;
        a1 = m1 * k1 + a1;
        m1 = abs(m1 / d * m2);
    }
    if (has_ans) return (a1 % m1 + m1) % m1;
    else return -1;
}

*/


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
