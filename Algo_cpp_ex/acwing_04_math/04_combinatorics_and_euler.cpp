/**
 * 模块：第四讲 数学知识
 * 主题：组合数学与欧拉函数 (Combinatorics & Euler's Function)
 * ICPC 核心考点：快速计算组合数 $C_a^b \pmod p$、容斥原理以及与互质相关的计数。
 */

#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

const int mod = 1e9 + 7;

// ==========================================
/*
 * 1. 欧拉函数的数学原理与公式推导 (Euler's Totient Function)
 *
 * [定义]：
 * 欧拉函数记为 \phi(N)，表示在 1~N 的正整数中，与 N 互质的数的个数。
 * (互质意味着两者的最大公约数 gcd(a, N) = 1)
 *
 * [公式推导：基于容斥原理]：
 * 任意正整数 N 都可以唯一分解为质因数的乘积：N = p_1^{k_1} * p_2^{k_2} * ... * p_m^{k_m}
 * 要找出与 N 互质的数，等价于从 N 个数中剔除掉所有这些质因子 p_i 的倍数。
 *
 * 以 N = 12 (质因子为 2 和 3) 为例：
 * 1. 总数：12 个。
 * 2. 减去倍数：2 的倍数有 12/2=6 个，3 的倍数有 12/3=4 个。剩余 12 - 6 - 4。
 * 3. 加回公倍数(容斥原理)：既是 2 又是 3 的倍数（6 的倍数）被减了两次，需加回 12/6=2 个。
 * \phi(12) = 12 - 12/2 - 12/3 + 12/6 = 12 * (1 - 1/2 - 1/3 + 1/6)
 *          = 12 * (1 - 1/2) * (1 - 1/3)
 *
 * 推广至一般情况，欧拉函数通用乘积公式为：
 * \phi(N) = N * \prod_{i=1}^{m} (1 - 1/p_i)
 *
 * [核心结论]：
 * 欧拉函数的值只与 N 包含了【哪些种类的质因数】有关，而与某个质因数出现的次数(幂次)无关。
 */
int phi(int n) {
    int res = n; // 对应公式外面的基数 N

    // 用 O(\sqrt{n}) 的时间揪出它所有的质因子底座
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) { // 发现质因子 i
            
            // [工程细节：防溢出与精度丢失]
            // 数学公式为：res = res * (1 - 1/i)
            // 必须写成 res = res / i * (i - 1)
            // - 若写成 res * (1 - 1/i)：整数除法 1/i 直接变 0，导致全错。
            // - 若写成 res * (i - 1) / i：大数连乘极易导致中间态 int 溢出。
            // 由于 res 此时必定包含 i 这个因子，先除以 i 绝无精度损失！
            res = res / i * (i - 1); 
            
            // 剔除同类质因子，保证每个种类只乘一次削减率
            while (n % i == 0) n /= i; 
        }
    }
    
    // 边界处理：最多只存在一个大于 sqrt(N) 的质因子，补上其削减率
    if (n > 1) res = res / n * (n - 1);
    
    return res;
}

/*
 * 2. 线性筛法批量求 1~N 欧拉函数 (O(N) 预处理)
 *
 * [需求场景]：
 * 若需要在一个甚至多个测试集中随时查询 1~N 中每个数的欧拉函数，逐个计算的时间复杂度将退化为 O(N*\sqrt{N})。
 * 此时我们需要利用【积性性质】并借助“欧拉筛（线性筛素数）”的 O(N) 线性遍历底座来批量预处理。
 * 
 * [数学前置：积性函数]：
 * 若 gcd(a, b) = 1 (即 a 与 b 互质)，则必有 \phi(a * b) = \phi(a) * \phi(b)。
 */
const int N = 100010;
int primes[N], cnt;
bool st[N];
int euler[N]; // euler[i] 存储 \phi(i) 的值

void get_eulers(int n) {
    euler[1] = 1; // 边界：1 与它自己互质的情况记为 1
    
    for (int i = 2; i <= n; i++) {
        /*
         * [情况 1：i 是纯种质数]
         * 如果 i 坚挺到这里未被任何因数筛破 (!st[i])，说明 i 是质数。
         * 依据：对于质数 i，1 ~ i-1 的所有数均与它互质，故 \phi(i) = i - 1。
         */
        if (!st[i]) {
            primes[cnt++] = i;
            euler[i] = i - 1; 
        }
        
        // 经典的线性筛内层：用当前已知的各个素数 p_j 去构建大合数 p_j * i
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            
            if (i % primes[j] == 0) {
                /*
                 * [情况 2：基因共振 (primes[j] 早已是 i 的质因子)]
                 * 这是在 i 的体内找到了老朋友 p_j。
                 * 回顾基础乘积公式：\phi(i * p_j) = (i * p_j) * \prod(1 - 1/p_k)
                 * 因为 p_j 已经在 i 的质因数保护伞内，所以乘积项 \prod 种类完全没有增加任何新质数！
                 * 这意味着，只要将计算 \phi(i) 时的外部总基数纯数字放大 p_j 倍即可：
                 * \phi(i * p_j) = p_j * \phi(i)
                 */
                euler[primes[j] * i] = euler[i] * primes[j];
                break; // 欧拉筛防连坐特质：用最小质因数过滤保证 O(N)
            }
            
            /*
             * [情况 3：新因子碰撞 (primes[j] 并不是 i 的质因子)]
             * 说明 i 内部查无此素数 p_j，此时两者毫无杂交：gcd(i, p_j) = 1。
             * 触发【积性函数分离能力】：
             * \phi(i * p_j) = \phi(i) * \phi(p_j)
             * 由于 p_j 是质数，由情况 1 已知 \phi(p_j) = p_j - 1，直接代入替换即可：
             */
            euler[primes[j] * i] = euler[i] * (primes[j] - 1);
        }
    }
}

/*
原始线性筛代码：
void get_primes_euler(int n) {
    cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!st[i]) primes[cnt++] = i;
        for(int j = 0; primes[j] * i <= n; j++ ) {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) break;
        } 
    }
}
*/


// ==========================================
// 2. 组合数计算 (Combinatorics Calculation)
// 求 $C_a^b \pmod p$ 的三种常用计算方式

// 类型 I： $a,b \le 2000$ (数据范围较小)，适用于频繁的预处理查询 O(N^2)
int c[2010][2010]; 
void init_C() {
    for (int i = 0; i <= 2000; i++) {
        for (int j = 0; j <= i; j++) {
            if (!j) c[i][j] = 1;
            else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }
}

// 类型 II： $a,b \le 10^5$，可以预处理阶乘及其逆元 O(N log p)，查询 O(1)
int fact[N], infact[N]; // 阶乘与阶乘逆元

LL qmi_inv(LL a, LL k, LL p) {
    LL res = 1;
    while (k) {
        if (k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

void init_fact() {
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (LL)fact[i - 1] * i % mod;
        infact[i] = (LL)infact[i - 1] * qmi_inv(i, mod - 2, mod) % mod;
    }
}

// O(1) 求 C(a, b) = a! / (b! * (a-b)!) % mod
int C(int a, int b) {
    if (a < b || a < 0 || b < 0) return 0;
    return (LL)fact[a] * infact[b] % mod * infact[a - b] % mod;
}

// 卢卡斯定理 (Lucas Theorem)：用于 $a,b \le 10^{18}$ 且质数 $p \le 10^5$
// 在密码系统或极大的离散对数计算经常出现。

int main() {
    cout << "phi(12) = 1 ~ 12 之间互质的个数 = " << phi(12) << endl; 
    // 互质的是 {1, 5, 7, 11} -> 4.

    get_eulers(20);
    cout << "线性筛结果 euler[12] = " << euler[12] << endl;

    init_fact();
    cout << "组合数计算: C(5, 2)  = " << C(5, 2) << endl;

    return 0;
}
