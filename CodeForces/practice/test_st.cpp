#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

vector<int> mono_st(const auto& a, auto cmp) {
  vector<int> l(ssize(a));
  for (int i = 0; i < ssize(a); i++)
    for (l[i] = i - 1; l[i] >= 0 && !cmp(a[l[i]], a[i]);)
      l[i] = l[l[i]];
  return l;
}
vector<int> mono_range(const vector<int>& l) {
  vector<int> r(ssize(l), ssize(l));
  for (int i = 0; i < ssize(l); i++)
    for (int j = i - 1; j != l[i]; j = l[j]) r[j] = i;
  return r;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vi a = {3, 5, 5, 3, 2, 3, 4, 5, 6, 1};
    vi l = mono_st(a, less());
    vi r = mono_range(l);
    rep(i, 0, sz(a)) {
        cout << a[i] << " ";
    }
    cout << endl;
    rep(i, 0, sz(l)) {
        cout << l[i] << " ";
    }
    cout << endl;
    rep(i, 0, sz(r)) {
        cout << r[i] << " ";
    }
    cout << endl;
    
    return 0;
}
