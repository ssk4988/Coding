#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

using cd = complex<ld>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    int n = str.length();
    vi a(n), b(n);
    rep(i, 0, n){
        a[i] = str[i] == 'B';
        b[i] = str[i] == 'A';
    }
    reverse(all(b));
    int p2 = 1;
    while(p2 < n){
        p2 <<= 1;
    }
    p2 <<= 1;
    a.resize(p2);b.resize(p2);
    vector<cd> a1(all(a)), b1(all(b));
    fft(a1, false);
    fft(b1, false);
    rep(i, 0, p2){
        a1[i] *= b1[i];
    }
    fft(a1, true);
    reverse(a1.begin(), a1.begin() + n);
    rep(i, 1, n){
        cout << int(round(real(a1[i]))+0.1) << nL;
    }
    
    return 0;
}
