#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main(int argc, char **argv) {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    if (argc != 3) {
        cerr << "Supply exactly two .out files to check" << "\n";
        return 1;
    }

    string fs1 = string(argv[1]);
    string fs2 = string(argv[2]);

    ifstream f1(fs1);
    ifstream f2(fs2);

    double f1v, f2v;
    while (f1 >> f1v && f2 >> f2v) {
        double difference = abs(f1v - f2v);
        if (difference > 0.0001) {
            cout << "Difference detected" << "\n";
            return 1;
        }
    }

    cout << "Same" << "\n";

    return 0;    
}
