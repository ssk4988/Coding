#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vvi = vector<vi>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;

    while (t--)
    {
        int p, q;
        cin >> p >> q;
        p = abs(p), q = abs(q);
        // cout << p << " " << q << "\n";
        bool prime = true;
        for (int m = 0; m < 142; ++m)
        {
            for (int n = 0; n < 142; ++n)
            {
                if (m == 1 && n == 0 || m == 0 && n == 1)
                    continue;
                if (m == p && n == q || m == q && n == p)
                    continue;
                int div = m * m + n * n;
                if (div == 0)
                    continue;
                if ((m * p + n * q) % div == 0 && (m * q - n * p) % div == 0)
                {
                    // cout << p << " " << q << " is divided by " << m << " " << n << "\n";
                    prime = false;
                }
            }
        }
        if (prime)
            cout << "P\n";
        else
            cout << "C\n";
    }

    return 0;
}