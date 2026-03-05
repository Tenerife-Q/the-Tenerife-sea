# 第四章 数学知识 (Mathematics) - ICPC/算法竞赛核心

## 学习规划与路线图

恭喜你完成了前三章（基础算法、数据结构、搜索与图论）的学习！作为 ICPC 队伍中主攻数学方向的选手，第四章是你真正的“主战场”。在竞赛中，数学题（特别是数论和组合数学）通常是拉开区分度的关键，而且与**密码学**（Cryptography）紧密相关。

结合 AcWing 基础课、洛谷的基础课程，以及你前三章的代码积累，我为你整理了以下层次分明的学习计划。

### 核心知识模块划分

#### 一、 基础数论（密码学前置基石）
数论是密码系统（如 RSA、Diffie-Hellman、椭圆曲线加密）的数学基础。
1. **质数 (Primes)**
   - 质数的判定（试除法）
   - 分解质因数（试除法）
   - 质数筛法（埃氏筛、**线性筛/欧拉筛**）
2. **约数 (Divisors)**
   - 求所有约数（试除法）
   - 约数个数与约数之和（算术基本定理）
   - 最大公约数 (GCD) 与 最小公倍数 (LCM)
3. **欧拉函数 (Euler's Totient Function)**
   - 求单个数的欧拉函数
   - 筛法求欧拉函数

#### 二、 高阶数论与同余方程（现代密码学核心组件）
在公钥密码学中，同余、逆元和快速幂是加密和解密算法的绝对核心。
1. **快速幂 (Fast Exponentiation)**
   - 快速幂求 $a^k \pmod p$
   - 快速幂求乘法逆元 (Fermat's Little Theorem)
2. **扩展欧几里得算法 (Extended Euclidean Algorithm, EXGCD)**
   - 求解贝祖等式 $ax + by = \gcd(a, b)$
   - 求解线性同余方程 $ax \equiv b \pmod m$
3. **中国剩余定理 (Chinese Remainder Theorem, CRT)**
   - 求解一元线性同余方程组

#### 三、 线性代数与组合数学
1. **高斯消元 (Gaussian Elimination)**
   - 求解线性方程组
   - 异或线性方程组（常用于博弈论或开关问题）
2. **组合数 (Combinatorics)**
   - 递推求组合数 $O(N^2)$
   - 预处理阶乘求组合数 $O(N \log N)$
   - 卢卡斯定理 (Lucas Theorem) 求解大组合数取模
   - 卡特兰数 (Catalan Number)
3. **容斥原理 (Inclusion-Exclusion Principle)**
   - 集合的交并问题

#### 四、 博弈论 (Game Theory)
1. **Nim 游戏**
   - 异或和结论 ($a_1 \oplus a_2 \oplus \dots \oplus a_n \neq 0$)
2. **SG 函数 (Sprague-Grundy Theorem)**
   - 有向图游戏与 SG 函数计算
   - 多个独立游戏和的 SG 定理

---

### 与前三章的联动
- **基础算法**：你已经学过的高精度乘除法（[07_high_precision_mul](Algo_cpp_ex/acwing_01_basics/07_high_precision_mul.cpp) 和 [08_high_precision_div](Algo_cpp_ex/acwing_01_basics/08_high_precision_div.cpp)）在处理大整数运算（如 RSA 算法的大素数）时非常关键；位运算巧用常常用于快速幂和状态压缩。
- **数据结构**：哈希表（[11_hash_table](Algo_cpp_ex/acwing_02_data_structures/11_hash_table.cpp)）常用于优化数论算法，比如大步小步算法 (Baby-step Giant-step, BSGS求解离散对数)。
- **搜索与图论**：欧拉图问题、最短路常与计数问题结合。

---

我们将依次实现这些模块的标准模板库 (STL) 和核心代码。现在开始第一部分：**基础数论**。
