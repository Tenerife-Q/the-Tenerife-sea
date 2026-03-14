#include <iostream>
#include <unordered_map>
using namespace std;
typedef long long ll;

long long get_divisors_count(int n) {
    if(n == 1) return 1;
    unordered_map<int, int> primes;
    for(int i = 2; i <= n / i; i++) {
        while(n % i == 0) {
            n /= i;
            primes[i]++;
        }
    }
    if(n > 1) primes[n]++;

    long long res = 1;
    for (auto p : primes) {
        res = res * (p.second + 1);
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    while(n--) {
        int x;
        cin >> x;
        cout << get_divisors_count(x) << "\n";
    }
    return 0;
}