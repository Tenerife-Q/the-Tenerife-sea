/**
 * ============================================================
 * 第一讲：基础算法 - 高精度减法 (High Precision Subtraction)
 * ============================================================
 * 
 * 核心思想：
 * 1. 同样倒序存储。
 * 2. 保证总是用 "大数 - 小数"。如果 A < B，则算 -(B - A)。
 * 3. 模拟借位：
 *    - t = A[i] - B[i] - t (t 这里表示上一位的借位，初始为 0)
 *    - 如果 t < 0，说明不够减，向高位借 1 (t+10)，且下一轮借位为 1。
 *    - 如果 t >= 0，说明够减，结果就是 t，下一轮借位为 0。
 *    - 统一写法：digit = (t + 10) % 10。
 * 4. 处理前导零：
 *    比如 123 - 120 = 003，vector 里是 [3, 0, 0]，需要去掉末尾的 0，保留 [3]。
 *    注意：如果是 0 - 0 = 0，要保留一个 0。
 */

#include <iostream>
#include <vector>

using namespace std;

// 判断是否有 A >= B
bool cmp(vector<int> &A, vector<int> &B) {
    if (A.size() != B.size()) return A.size() > B.size(); // 位数不同，位数多的更大
    // 位数相同，从高位开始比较
    for (int i = A.size() - 1; i >= 0; i--) {
        if (A[i] != B[i]) return A[i] > B[i];
    }
    return true; // A == B
}

// ⚡ 核心模板代码：C = A - B (前提 A >= B)
vector<int> sub(vector<int> &A, vector<int> &B) {
    vector<int> C;
    int t = 0; // 借位
    for (int i = 0; i < A.size(); i++) {
        t = A[i] - t; // 上一位的借位
        if (i < B.size()) t -= B[i]; // 减去 B 的对应位

        // 此时 t 包含了本位减法结果
        // 结果位是 (t + 10) % 10
        // 如果 t < 0: t+10 是借位后的正值
        // 如果 t >= 0: t+10%10 还是 t 自身
        C.push_back((t + 10) % 10);

        if (t < 0) t = 1; // 需要向下一位借 1
        else t = 0;
    }

    // 去掉前导零 (vector 末尾的零)
    // 比如结果是 003 (vector: 3, 0, 0)，需要 pop 掉两个 0
    // 留一个 0 以防结果就是 0
    while (C.size() > 1 && C.back() == 0) C.pop_back();

    return C;
}

/**
 * ============================================================
 * 💡 董晓算法模板 ver. (对比参考)
 * ============================================================
 * 
 * 对比分析：
 * 1. 借位逻辑：
 *    - AcWing: 使用借位变量 t，不修改原数组。
 *    - DongXiao: 直接修改被减数数组 a[i+1]--，更直观粗暴。
 * 2. 比较逻辑：
 *    - AcWing: 比较 vector，通用性强。
 *    - DongXiao: 直接比较 string (先比长度，再比字典序)，代码更短。
 * 3. 细节：
 *    - DongXiao 版本在计算每一位时，先处理借位 (a[i+1]--)，再算差值，逻辑紧凑。
 */
/*
bool cmp_dongxiao(string a, string b) {
    if (a.size() < b.size()) return true;
    if (a.size() == b.size() && a < b) return true;
    return false;  
}

void sub_dongxiao(string sa, string sb) {
    int la = sa.size(), lb = sb.size(), m = max(la, lb);
    vector<int> a(m + 1, 0), b(m + 1, 0), c(m + 1, 0);
    for (int i = 0; i < la; i++) a[i] = sa[la - 1 - i] - '0';
    for (int i = 0; i < lb; i++) b[i] = sb[lb - 1 - i] - '0';

    for (int i = 0; i < m; i++) {
        // 如果当前位不够减，向高位借 1，当前位 +10
        if (a[i] < b[i]) {
            a[i + 1]--;
            a[i] += 10;
        }
        c[i] = a[i] - b[i];
    }
    
    while (!c[m] && m) m--; 去除前导零 
    当m不等于0且首位为0时，C数组长度m自减
    
    for (int i = m; i >= 0; i--) printf("%d", c[i]);
}
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string a, b;
    if (cin >> a >> b) {
        vector<int> A, B;
        for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
        for (int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');

        if (cmp(A, B)) {
            auto C = sub(A, B);
            for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
        } else {
            // A < B，计算 -(B - A)
            auto C = sub(B, A);
            cout << "-";
            for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
        }
        cout << endl;
    }

    return 0;
}
