/**
 * ============================================================
 * 竞赛基础 5：STL 排序与自定义比较
 * ============================================================
 * 学习目标：
 * 1. sort() 函数的使用 (O(N log N) 复杂度)
 * 2. 从大到小排序
 * 3. 自定义结构体排序 (竞赛核心技能)
 */

#include <iostream>
#include <vector>
#include <algorithm> // 必须包含：sort 在这里
using namespace std;

// 📌 定义一个简单的结构体 (例如：学生)
struct Student {
    string name;
    int score;
    int id;
};

// 📌 自定义比较函数 (Comparator)
// 规则：只要 a 应该排在 b 前面，就返回 true
bool cmp(Student a, Student b) {
    if (a.score != b.score) {
        return a.score > b.score; // 分数高的排前面 (降序)
    }
    return a.id < b.id; // 分数一样时，学号小的排前面 (升序)
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // ---------------------------------------------------------
    // 🔢 1. 数组/Vector 简单排序
    // ---------------------------------------------------------
    vector<int> nums = {5, 1, 9, 3, 7};
    
    // 默认升序 (从小到大)
    sort(nums.begin(), nums.end());
    
    cout << "Sorted nums: ";
    for(int x : nums) cout << x << " ";
    cout << "\n";
    
    // 降序 (从大到小) - 使用 greater<int>()
    sort(nums.begin(), nums.end(), greater<int>());
    cout << "Desc sorted: ";
    for(int x : nums) cout << x << " ";
    cout << "\n";

    // ---------------------------------------------------------
    // 🎓 2. 结构体排序 (实战常用)
    // ---------------------------------------------------------
    vector<Student> class1;
    class1.push_back({"Alice", 85, 101});
    class1.push_back({"Bob", 95, 102});
    class1.push_back({"Charlie", 85, 100}); // 分数和 Alice 一样，但 ID 小

    // 使用刚才定义的 cmp 函数排序
    sort(class1.begin(), class1.end(), cmp);

    cout << "\n--- Student Rank ---\n";
    for(const auto& s : class1) {
        cout << s.name << " (Score: " << s.score << ", ID: " << s.id << ")\n";
    }
    // 预期：Bob(95) -> Charlie(85, id100) -> Alice(85, id101)

    return 0;
}
