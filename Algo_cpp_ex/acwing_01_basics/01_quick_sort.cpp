/**
 * ============================================================
 * 第一讲：基础算法 - 快速排序 (Quick Sort)
 * ============================================================
 * 
 * 核心思想：分治 (Divide and Conquer)
 * 1. 确定分界点：x = q[(l + r) / 2] (或者取两端、随机)
 * 2. 调整区间：使得左边的数都 <= x，右边的数都 >= x
 * 3. 递归处理：递归处理左右两段
 * 
 * 常见应用：
 * - 排序 (O(N log N))
 * - 求第 K 小的数 (Quick Select, O(N))
 * 
 * 模板来源：AcWing 算法基础课
 */

#include <iostream>
#include <vector>
#include <algorithm> // swap

using namespace std;

const int N = 100010;// const代表常量 所以不能修改
int q[N]; // 建议开在全局，避免栈溢出

// ⚡ 核心模板代码
void quick_sort(int q[], int l, int r) {
    if (l >= r) return; // 边界条件：区间只有一个数或没有数

    // 1. 确定分界点 x
    // 这里取中间值，不容易被卡成 O(N^2)
    // 注意：用由边界 i, j 先移动一次的写法，x 最好取中间
    int x = q[l + r >> 1]; // 位运算等同于 (l + r) / 2 这里怎么理解？
    int i = l - 1, j = r + 1; // 两个指针从区间两侧外开始 因为要先移动一次 
    /**
     * ❓ 为什么是用 do-while 而不是 while？
     * 1. 避免死循环：如果数组中有两个元素都等于 x (比如 [2, 2], x=2)，
     *    使用 while(q[i] < x) i++ 会导致指针在 q[i]==x 处停下。
     *    交换后 q[i] 依然是 x，如果不强制移动，下一轮会在原地死循环。
     *    do-while 保证了每次无论如何指针都会先动一下，打破僵局。
     * 
     * ❓ 为什么初始位置是 l-1 和 r+1？
     *    因为 do-while 是"先移动后判断"，如果初始 i=l，上来一动就变 l+1 了，
     *    会漏掉第一个元素 q[l]。所以要先退一格，第一步走完刚好对应有效区间。
     */


    // 2. 调整区间 (Partition)
    while (i < j) {
        do i++; while (q[i] < x); // 找左边 >= x 的数
        do j--; while (q[j] > x); // 找右边 <= x 的数
        if (i < j) swap(q[i], q[j]);
    }

    // 3. 递归处理
    // 注意边界：如果用 j，递归范围是 (l, j) 和 (j+1, r)
    // 如果用 x = q[r] 或 q[...], 边界处理会不同，建议背熟一种写法
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

int main() {
    // 提速
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    /* 
       练习输入：
       5
       3 1 2 4 5
    */
    cout << "Please input n (e.g. 5): " << endl; // 提示用户输入
    if (cin >> n) {// cin>>n 返回cin对象本身，可以转换为bool类型，表示输入是否成功
        // 连续输入数据 如果遇见空格、换行符会自动跳过
        cout << "Please input " << n << " numbers: " << endl;
        for (int i = 0; i < n; i++) cin >> q[i];

        quick_sort(q, 0, n - 1);

        for (int i = 0; i < n; i++) cout << q[i] << " ";
        cout << endl;
    }
    
    return 0;
}


// int n, a[100005];  // 全局变量：n是数组长度，a[]存数据

// void quicksort(int l, int r) {  // [l, r] 是当前要排序的区间
//     if (l == r) return;  // 递归终止：区间只有1个元素，已有序
    
//     // 1. 初始化指针、选基准
//     int i = l - 1, j = r + 1;  // 指针初始在区间外，方便后续自增/自减后进入区间
//     int x = a[(l + r) / 2];    // 选中间位置的数当基准（也可用随机、首/尾元素）
    
//     // 2. 分区：把数组分成“≤x”和“≥x”两部分
//     while (i < j) {
//         // i 向右找 ≥x 的数：遇到 <x 的就跳过，直到找到 ≥x 的停下
//         do i++; while (a[i] < x);  
//         // j 向左找 ≤x 的数：遇到 >x 的就跳过，直到找到 ≤x 的停下
//         do j--; while (a[j] > x);  
        
//         if (i < j) {  // 如果 i、j 没交叉，交换两者位置
//             swap(a[i], a[j]);  
//         }
//     }
    
//     // 3. 递归处理左右子区间
//     quicksort(l, j);    // 左子区间：[l, j]
//     quicksort(j + 1, r); // 右子区间：[j+1, r]
// }

