/**
 * ============================================================
 * 第一讲：基础算法 - 高精度除法 (High Precision Division)
 * ============================================================
 * 
 * 场景：大整数 A / 小整数 b (b > 0)
 * 输出：商 C 和 余数 r
 * 
 * 核心思想：
 * 1. 除法和加减乘不同，是从“最高位”开始算的（手算除法也是从左到右）。
 * 2. 余数 r 初始化为 0。
 *    从最高位遍历到最低位：
 *    - r = r * 10 + A[i] (上一位余数挪下来变成几十 + 当前位)
 *    - 商的当前位 = r / b
 *    - 新的余数 r = r % b
 * 3. 为了保持接口一致（C 也是 LSB at 0），最后需要 reverse 一下。
 *      标准规定：A[0] 是个位，A[1] 是十位，A[2] 是百位...
        为什么要统一？
        加减乘法：都是从低位算到高位（个位对齐）。
        如果你把个位放在 size-1，那么每次进位都要把整个数组搬移一遍，效率极低。
        为了让这四个函数能互相调用（比如 (A + B) / C），
        所有函数的输入参数和返回值必须遵守同一个存储规则。
 * 4. 同样要处理前导零。
 */

#include <iostream>
#include <vector>
#include <algorithm> // reverse

using namespace std;

// ⚡ 核心模板代码：C = A / b, r 是余数
vector<int> div(vector<int> &A, int b, int &r) {
    vector<int> C;
    r = 0;
    // 注意：这里的 vector A 是倒序的 (LSB at 0)，但除法运算习惯从高位开始
    // 所以我们从 A.size() - 1 开始遍历 (也就是 A 的最高位)
    for (int i = A.size() - 1; i >= 0; i--) {
        r = r * 10 + A[i];
        C.push_back(r / b); // 这一位商放进去
        r %= b;
    }

    // 此时 C 是从高位到低位存的（因为我们是 push_back 进去的）
    // 为了符合这套模板的习惯（LSB at 0），翻转一下
    // ❓ 为什么要翻转？
    // 除法是从高位算到低位的，所以 push_back 进去的第一位其实是最高位 (MSB)。
    // 但是我们的核心结构约定：下标 0 是个位 (LSB)。
    // 所以算完后，vector 里是 [千位, 百位, 十位, 个位]，违反了约定，必须 reverse 回来。
    reverse(C.begin(), C.end());

    // 去掉前导零
    while (C.size() > 1 && C.back() == 0) C.pop_back();

    return C;
}

/**
 * ============================================================
 * 💡 董晓算法模板 ver. (数组版 - 对比参考)
 * ============================================================
 * 
 * 下标逻辑解析：
 * 1. for(int i=la-1; ~i; i--) 
 *    - 这里的 i 是从最高位(la-1) 遍历到 (0)。
 *    - 比如 12345 / 2，先取 i=4 (万位) 参与运算。
 * 
 * 2. C[la-1-i] = r / b;
 *    - 当 i 很大(最高位)时，la-1-i 很小(接近0)。
 *    - 这意味着：计算出的最高位商，存到了数组下标 0 的位置。
 *    - 此时数组内状态：[最高位, 次高位, ..., 最低位] (Big Endian)
 * 
 * 3. reverse(C, C + lc);
 *    - 翻转后状态：[最低位, ..., 最高位] (Little Endian)
 *    - 这样就和加减乘法的存储规则统一了！
 */
/*
// 全局变量防止栈溢出
int A[100005], C[100005];

void div_dongxiao(string a, int b) {
    int la = a.size();
    
    // 1. 倒序存储被除数 A (常规操作，LSB at 0)
    for(int i = 0; i < la; i++) A[la - 1 - i] = a[i] - '0';
    
    long long r = 0;
    // 2. 核心计算
    for(int i = la - 1; i >= 0; i--) { // 从最高位开始除
        r = r * 10 + A[i];
        C[la - 1 - i] = r / b; // ⚠️ 注意：这里把最高位的商存到了 C[0]
        r %= b;
    }
    
    // 3. 翻转与去前导零
    int lc = la; // 商的位数最多和被除数一样
    reverse(C, C + lc); // 翻转回来，变成 LSB at 0
    while(lc > 1 && C[lc - 1] == 0) lc--; // 董晓习惯用 lc 代表长度(或边界)，这里指有效长度
    
    // 4. 输出
    for(int i = lc - 1; i >= 0; i--) printf("%d", C[i]);
    cout << endl << r << endl;
}
*/

/**
 * ⚡ 极简优化版 (User's Insight)
 * 既然用了数组，我们完全可以直接把商填到正确的下标 i 上！
 * 这样就不需要 reverse 了。
 */
// void div_optimized(string a, int b) {
//     int la = a.size();
//     for(int i = 0; i < la; i++) A[la - 1 - i] = a[i] - '0';
    
//     long long r = 0;
//     // 直接把商填入 C[i]，这一位就是原本 A[i] 对应的权重位
//     for(int i = la - 1; i >= 0; i--) { 
//         r = r * 10 + A[i];
//         C[i] = r / b; 
//         r %= b;
//     }
    
//     // 去前导零 (此时最高位就在 la-1)
//     int lc = la;
//     while(lc > 1 && C[lc - 1] == 0) lc--;
    
//     for(int i = lc - 1; i >= 0; i--) printf("%d", C[i]);
//     cout << endl << r << endl;
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string a;
    int b;
    // cout << "Input large number A and int b: ";
    if (cin >> a >> b) {
        vector<int> A;
        for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');

        int r;
        auto C = div(A, b, r);

        for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
        cout << endl << r << endl; // AcWing 题目常要求输出商换行后再输出余数
    }

    return 0;
}
