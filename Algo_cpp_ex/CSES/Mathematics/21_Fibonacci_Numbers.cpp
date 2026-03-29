/*
Fibonacci Numbers

Task
Your task is to calculate the value of F_n for a given n.

Time limit: 1.00 s
Memory limit: 512 MB

The Fibonacci numbers can be defined as follows:

F_0 = 0
F_1 = 1
F_n = F_{n-2} + F_{n-1}

Input
The only input line has an integer n.

Output
Print the value of F_n modulo 10^9+7.

Constraints
0 <= n <= 10^18

Example
Input:
10

Output:
55

(Problem statement and page scripting snippets originally provided
were converted into this top-of-file comment for reference.)
*/

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ll = long long;
const ll MOD = 1000000007LL;

// fast doubling method
// returns pair (F(n), F(n+1)) modulo MOD
pair<ll,ll> fib(ull n) {
    if (n == 0) return {0, 1};
    auto p = fib(n >> 1);
    ll a = p.first;  // F(k)
    ll b = p.second; // F(k+1)
    ll two_b_minus_a = ( (2*b) % MOD - a + MOD ) % MOD;
    ll c = (a * two_b_minus_a) % MOD; // F(2k)
    ll d = ( (a*a) % MOD + (b*b) % MOD ) % MOD; // F(2k+1)
    if (n & 1) return {d, (c + d) % MOD};
    else return {c, d};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ull n;
    if (!(cin >> n)) return 0;
    cout << fib(n).first << '\n';
    return 0;
}


// solution using matrix exponentiation
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

template <int N>
struct Matrix {
    ll m[N][N];

    static Matrix<N> ident() {
        Matrix<N> r{};
        for (int i = 0; i < N; i++) r.m[i][i] = 1;
        return r;
    }

    Matrix<N> operator*(Matrix<N> b) {
        Matrix<N> r{};
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    r.m[i][j] += m[i][k] * b.m[k][j];
                    r.m[i][j] %= M;
                }
            }
        }
        return r;
    }

    Matrix<N> power(ll b) {
        if (b == 0) return ident();
        auto a = *this;
        return b & 1 ? a.power(b - 1) * a : (a * a).power(b / 2);
    }
};

int main() {
    ll n;
    cin >> n;

    Matrix<2> m{{{0, 1}, {1, 1}}};
    auto p = m.power(n);
    cout << p.m[0][1] << "\n";
}




// solution using fast doubling method with memoization
#include <iostream>
#include <map>
using namespace std;
using ll = long long;
const int M = 1000000007;

map<ll, ll> dp;

ll f(ll n) {
    if (n <= 2) return n >= 1;
    if (dp.count(n)) return dp[n];
    auto a = f(n / 2);
    auto b = f(n / 2 + 1);
    if (n % 2 == 0) {
        dp[n] = (2 * b - a) * a;
    } else {
        dp[n] = a * a + b * b;
    }
    dp[n] = (dp[n] % M + M) % M;
    return dp[n];
}

int main() {
    ll n;
    cin >> n;
    cout << f(n) << "\n";
}