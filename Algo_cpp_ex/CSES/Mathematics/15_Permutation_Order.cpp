/*
================================================================================
Title: Permutation Order
Time limit: 1.00 s
Memory limit: 512 MB

[English Description]
Let p(n,k) denote the kth permutation (in lexicographical order) of 1 ... n. 
For example, p(4,1) = [1,2,3,4] and p(4,2) = [1,2,4,3].

Your task is to process two types of tests:
1. Given n and k, find p(n,k)
2. Given n and p(n,k), find k

Input:
The first line has an integer t: the number of tests.
Each test is either "1 n k" or "2 n p(n,k)".

Output:
For each test, print the answer according to the example.

Constraints:
1 <= t <= 1000
1 <= n <= 20
1 <= k <= n!

--------------------------------------------------------------------------------

[中文题目描述]
标题：排列顺序 (Permutation Order)
时间限制：1.00 秒  |  内存限制：512 MB

令 p(n,k) 表示 1 到 n 按照字典序的第 k 个排列。
例如，p(4,1) = [1,2,3,4]，p(4,2) =[1,2,4,3]。

你的任务是处理以下两种类型的测试操作：
1. 已知 n 和 k，求出排列 p(n,k)
2. 已知 n 和排列 p(n,k)，求出其对应的序号 k

输入格式：
第一行包含一个整数 t：表示测试的数量。
每个测试用例的格式要么是 "1 n k"，要么是 "2 n p(n,k)"。

输出格式：
对于每个测试，按照样例输出对应的答案。

数据范围：
1 <= t <= 1000
1 <= n <= 20
1 <= k <= n!
================================================================================
*/

#include <iostream>
#include <vector>

using namespace std;

// 预处理阶乘数组，最多到 20! (20! 约为 2.43 * 10^18，在 unsigned long long 范围内)
unsigned long long fact[21];

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= 20; ++i) {
        fact[i] = fact[i - 1] * i;
    }
}

void solve() {
    int type;
    cin >> type;
    
    if (type == 1) {
        // 类型 1: 给定 n 和 k，求对应的排列 (逆康托展开)
        int n;
        unsigned long long k;
        cin >> n >> k;
        
        k--; // 转换为 0-indexed (基于 0 的索引)
        
        // S 存储当前还没被使用的数字候选集
        vector<int> S(n);
        for (int i = 0; i < n; ++i) {
            S[i] = i + 1;
        }
        
        vector<int> ans;
        for (int i = 1; i <= n; ++i) {
            // 计算当前位应该取未使用数字列表里的第几个
            int idx = k / fact[n - i];
            ans.push_back(S[idx]);
            S.erase(S.begin() + idx); // 移除已经使用的数字
            k %= fact[n - i];         // 更新剩余的排位 rank
        }
        
        // 打印结果
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
        
    } else if (type == 2) {
        // 类型 2: 给定排列，求其对应的序号 k (康托展开)
        int n;
        cin >> n;
        
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
        }
        
        // S 存储当前还没被使用的数字候选集
        vector<int> S(n);
        for (int i = 0; i < n; ++i) {
            S[i] = i + 1;
        }
        
        unsigned long long k = 0;
        for (int i = 0; i < n; ++i) {
            int idx = 0;
            // 在未使用的数字中寻找当前数字的位置（即前面有几个比它小且尚未被使用的数字）
            for (int j = 0; j < S.size(); ++j) {
                if (S[j] == p[i]) {
                    idx = j;
                    break;
                }
            }
            k += idx * fact[n - 1 - i]; // 累加跳过的排列数量
            S.erase(S.begin() + idx);   // 移除已经处理完的数字
        }
        
        // 输出 1-indexed 的序号
        cout << k + 1 << "\n";
    }
}

int main() {
    // 优化 I/O 读写速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // 初始化阶乘表
    precompute();
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    
    return 0;
}


#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;
const int N = 20;

int main() {
    int t;
    cin >> t;

    vector<ll> fact(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i;
    }

    while (t--) {
        int op;
        cin >> op;

        int n;
        cin >> n;

        ll f = fact[n];
        vector<int> numbers(n);
        iota(numbers.begin(), numbers.end(), 1);

        if (op == 1) {
            ll k;
            cin >> k;
            k--;
            for (int i = 0; i < n; i++) {
                f /= n - i;
                cout << numbers[k / f] << " ";
                numbers.erase(numbers.begin() + (k / f));
                k %= f;
            }
            cout << "\n";
        }

        if (op == 2) {
            ll k = 1;
            for (int i = 0; i < n; i++) {
                int x;
                cin >> x;
                f /= n - i;
                auto it = find(numbers.begin(), numbers.end(), x);
                k += (it - numbers.begin()) * f;
                numbers.erase(it);
            }
            cout << k << "\n";
        }
    }
}