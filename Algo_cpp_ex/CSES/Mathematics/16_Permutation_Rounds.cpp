/**
 * ==============================================================================
 * Problem Name / 题目名称: Permutation Rounds / 置换轮数
 * 
 * [English Description]
 * There is a sorted array [1,2,...,n] and a permutation p_1,p_2,...,p_n. 
 * On each round, all elements move according to the permutation: 
 * the element at position i moves to position p_i.
 * After how many rounds is the array sorted again for the first time?
 * 
 * [中文描述]
 * 有一个排好序的数组 [1,2,...,n] 和一个排列 p_1,p_2,...,p_n。
 * 在每一轮中，所有元素根据排列进行移动：位置 i 上的元素移动到位置 p_i。
 * 问最少经过多少轮后，数组会首次再次变回有序状态？
 * 
 * [Input / 输入]
 * The first line has an integer n.
 * The next line contains n integers p_1,p_2,...,p_n.
 * 第一行包含一个整数 n。
 * 第二行包含 n 个整数 p_1,p_2,...,p_n。
 * 
 * [Output / 输出]
 * Print the number of rounds modulo 10^9+7.
 * 打印所需轮数对 10^9+7 取模的结果。
 * 
 * [Constraints / 限制]
 * 1 <= n <= 2 * 10^5
 * 
 * [Example / 案例]
 * Input / 输入:
 * 8
 * 5 3 2 6 4 1 8 7
 * 
 * Output / 输出:
 * 4
 * ==============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Modulo constant / 取模常量
const int MOD = 1e9 + 7;

int main() {
    // Optimize standard I/O operations for competitive programming
    // 优化标准输入输出速度，防止大输入输出时超时
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    // Read the permutation array / 读取排列数组 (1-indexed / 从1开始索引)
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    
    // visited array to keep track of processed elements
    // visited 数组用于记录已经处理过（属于某个已发现环）的元素
    vector<bool> visited(n + 1, false);
    
    // Array to store the maximum power for each prime factor to compute LCM
    // 数组用于存储所有环长度分解质因数后，每个质因子所需的最大次幂，以便计算 LCM
    vector<int> max_power(n + 1, 0);
    
    // Step 1: Find all cycles and their lengths
    // 步骤 1：找出所有的环以及它们的长度
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            int curr = i;
            int length = 0;
            
            // Traverse the cycle until we return to the starting point
            // 沿着环遍历，直到回到起点，计算环的长度
            while (!visited[curr]) {
                visited[curr] = true;
                curr = p[curr];
                length++;
            }
            
            // Step 2: Prime factorization of the cycle length
            // 步骤 2：对当前环的长度进行质因数分解
            int temp = length;
            for (int j = 2; j * j <= temp; ++j) {
                if (temp % j == 0) {
                    int count = 0;
                    // Count the power of prime factor 'j'
                    // 计算质因子 j 的次幂
                    while (temp % j == 0) {
                        count++;
                        temp /= j;
                    }
                    // Update the global maximum power for prime factor 'j'
                    // 更新全局最大次幂表中质因子 j 的次幂
                    max_power[j] = max(max_power[j], count);
                }
            }
            // If the remaining temp is a prime number itself
            // 如果剩下的 temp 自身也是一个大于1的质数
            if (temp > 1) {
                max_power[temp] = max(max_power[temp], 1);
            }
        }
    }
    
    // Step 3: Compute the LCM using the maximum prime powers, with modulo arithmetic
    // 步骤 3：利用收集到的质数最大次幂计算最小公倍数 (LCM)，并随时取模
    long long ans = 1;
    for (int i = 2; i <= n; ++i) {
        if (max_power[i] > 0) {
            // Multiply prime 'i' for 'max_power[i]' times
            // 将质数 i 连乘 max_power[i] 次
            for (int j = 0; j < max_power[i]; ++j) {
                ans = (ans * i) % MOD;
            }
        }
    }
    
    // Output the final result / 输出最终结果
    cout << ans << "\n";
    
    return 0;
}