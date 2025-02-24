#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 998244353;

// 设置最大预处理范围
const int MAX = 2000000;  // 这个值可以根据实际情况调整，确保涵盖所有可能的输入

vector<long long> fact(MAX + 1, 1), inv_fact(MAX + 1, 1);

// 使用费马小定理计算模逆元
long long mod_inv(long long x, long long mod) {
    long long res = 1;
    long long exp = mod - 2;  // 根据费马小定理，x^(mod-2) ≡ x^(-1) (mod)
    while (exp) {
        if (exp % 2) res = res * x % mod;
        x = x * x % mod;
        exp /= 2;
    }
    return res;
}

// 预处理阶乘和逆阶乘
void precompute() {
    for (int i = 2; i <= MAX; i++) {
        fact[i] = fact[i - 1] * i % MOD;  // 计算阶乘 fact[i] = i!
    }
    inv_fact[MAX] = mod_inv(fact[MAX], MOD);  // 计算最大阶乘的逆元
    for (int i = MAX - 1; i >= 1; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;  // 计算逆阶乘 inv_fact[i] = (i!)^(-1)
    }
}

// 计算组合数 C(n, k) = n! / (k! * (n-k)!)
long long C(long long n, long long k) {
    if (k > n || k < 0) return 0;  // 如果k > n，则C(n, k)为0
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

// 定义 f(i, j) = C(i + j, i) - 1
long long f(long long i, long long j) {
    return (C(i + j, i) - 1 + MOD) % MOD;
}

int main() {
    int t;
    cin >> t;  // 输入数据组数

    precompute();  // 预处理阶乘和逆阶乘

    while (t--) {
        int n;
        cin >> n;

        vector<long long> a(n + 1), dp(n + 1);
        
        // 输入数组并排序
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        sort(a.begin() + 1, a.end()); // 按升序排序数组
        
        // 初始化 dp 数组
        dp[1] = a[1];

        // 使用递推关系填充 dp 数组
        for (int i = 2; i <= n; i++) {
            if(a[i]) dp[i] = (dp[i - 1] + 1 + f(i, a[i] - 1)) % MOD;
            else dp[i] = dp[i-1];
        }

        // 输出最终答案
        cout << dp[n] << endl;
    }

    return 0;
}
