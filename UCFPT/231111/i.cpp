#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

#define double long double

vector<double> xInit = {0.0, 3.715, 2.894};
vector<double> yInit = {0.0, 1.761, -2.115};

double a[3], cl[3];

const double pi = acos(-1);

double cross(double x1, double y1, double x2, double y2) {
    return x1 * y2 - y1 * x2;
}

double dot(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}

double calc(double x, double y) {
    double res = 0;
    rep(i, 0, 3) {
        double dx = cos(a[i]), dy = sin(a[i]);

        double dist = cross(x - xInit[i], y - yInit[i], dx, dy);
        dist *= dist;
        res += dist * cl[i];
    }

    return res;
}

double ternY(double x) {
    double lo = -100000, hi = 100000;
    rep(i, 0, 50) {
        double dif = (hi - lo) / 3.0;
        double y1 = lo + dif;
        double y2 = hi - dif;
        if(calc(x, y1) < calc(x, y2))
            hi = y2;
        else
            lo = y1;
    }
    return lo;
}

pair<double, double> ternX() {
    double lo = -100000, hi = 100000;
    rep(i, 0, 50) {
        double dif = (hi - lo) / 3.0;
        double x1 = lo + dif;
        double x2 = hi - dif;
        double y1 = ternY(x1);
        double y2 = ternY(x2);
        if(calc(x1, y1) < calc(x2, y2))
            hi = x2;
        else
            lo = x1;
    }

    return {lo, ternY(lo)};
}

double scanDouble() {
    string s; cin >> s;
    return stod(s);
}

void solve() {
    rep(i, 0, 3) {
        a[i] = scanDouble();
        cl[i] = scanDouble();
    }

    rep(i, 0, 3) {
        a[i] = (90 - a[i]) * pi / 180.0;
        cl[i] += 0.2;
    }


    auto[x, y] = ternX();

    cout << x << ' ' << y << endl;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(3) << fixed;

    int t; cin >> t;
    while(t--) {
        int k; cin >> k;
        cout << k << ' ';
        solve();
    }

    return 0;
}