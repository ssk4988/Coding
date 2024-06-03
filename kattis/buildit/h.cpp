#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
const int N = 40, K = 2500;
const int C2 = N * N / 4;
const int S = (N+1) * (N+1) * (C2+1) * (K+1);
bitset<S> seen;
int n, k;
string s;
inline int getidx(int i, int c1, int c2, int c3) {
    return i * (N+1) * (C2+1) * (K+1) + c1 * (C2+1) * (K+1) + c2 * (K+1) + c3;
}
bool go(int i, int c1, int c2, int c3)
{
    if(c3 > k || seen[getidx(i, c1, c2, c3)]) return false;
    seen[getidx(i, c1, c2, c3)] = 1;
    if (i == n) return c3 == k;
    if(i == 20 || i == 30) {
        rep(d1, 0, n - i + 1)
            rep(d2, 0, n - i - d1 + 1)
                if(c3 + (n - i - d1 - d2) * (c2 + d2 * (c1 + d1)) >= k)
                    goto cando;
        return false;
    }
    cando:
    if (s[i] == '?' || s[i] == 'N')
        if(go(i+1, c1+1, c2, c3))
            return s[i] = 'N';
    if (s[i] == '?' || s[i] == 'A')
        if(go(i+1, c1, c2+c1, c3))
            return s[i] = 'A';
    if (s[i] == '?' || s[i] == 'C')
        if(go(i+1, c1, c2, c3+c2))
            return s[i] = 'C';
    if (s[i] == '?' || (s[i] != 'N' && s[i] != 'A' && s[i] != 'C'))
        if(go(i+1, c1, c2, c3)) {
            if(s[i] == '?') s[i] = 'X';
            return true;
        }
    return false;
}

int main()
{
    cin >> n >> k >> s;
    if(!go(0, 0, 0, 0)) cout << "-1\n";
    else cout << s << "\n";
    return 0;
}
