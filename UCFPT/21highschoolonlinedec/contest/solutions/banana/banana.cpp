#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// Hold the current minimum distance.
double minDist = DBL_MAX;

// Array of starting and ending points.
vector<pii> currentLocs, desiredLocs;

// Retrieve an array of points from standard in.
vector<pii> getPoints(int n) {
    vector<pii> vec;
    rep(i, 0, n) {
        int x, y; cin >> x >> y;
        vec.emplace_back(x, y);
    }
    return vec;
}

// Calculate the distance between two points.
double pointDist(pii a, pii b) {
    ll dx = a.first - b.first;
    ll dy = a.second - b.second;
    return sqrt(dx*dx+dy*dy);
}

// Calculte the sum of movements resulting from a permutation.
double sumOfDist(vector<int> &perm) {
    double dist = 0;
    rep(i, 0, perm.size())
        dist += pointDist(currentLocs[i], desiredLocs[perm[i]]);
    return dist;
}

// Test all permutations of points. O(n!) = 7! worst case
void permute(vector<int> &perm, vector<bool> &used, int p) {
    // We have constructed a complete case, test it.
    if (p == perm.size()) {
        minDist = min(minDist, sumOfDist(perm));
        return;
    }

    // Generate permutations.
    rep(i, 0, perm.size()) {
        if (!used[i]) {
            used[i] = true;
            perm[p] = i;
            permute(perm, used, p+1);
            used[i] = false;
        }
    }
}

void solve() {
    // Get n (< 8)
    int n; cin >> n;

    minDist = DBL_MAX;
    currentLocs = getPoints(n);
    desiredLocs = getPoints(n);
    vi perm(n); rep(i, 0, n) perm[i] = i;
    vector<bool> used(n, false);

    permute(perm, used, 0);
    
    cout << minDist << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cout << fixed;
    cout << setprecision(10);

    // Get the number of test cases and solve them.
    int p; cin >> p;
    rep(i, 0, p)
        solve();

    return 0;    
}
