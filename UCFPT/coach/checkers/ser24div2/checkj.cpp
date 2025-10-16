#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void WA(string err) {
    cout << "wrong answer " << err << endl;
    exit(0);
}

int main(int argc, char ** argv) {
    string judgeinpf = argv[1];
    string progoutf = argv[2];
    string judgeoutf = argv[3];

    ifstream judgein(judgeinpf);
    ifstream progout(progoutf);
    ifstream judgeout(judgeoutf);

    vector<ll> progints;
    for(ll a; progout >> a;) {
        progints.push_back(a);
    }
    if(progout.fail() && !progout.eof()) {
        WA("invalid token");
    }

    // check -1 case
    int judgefirst; judgeout >> judgefirst;
    if(judgefirst == -1) {
        if (progints.size() != 1 || progints[0] != -1) WA("should output -1 only");
        return 0;
    }
    
    if (progints.size() != 3) {
        WA("wrong number of integers printed");
    }
    ll n; judgein >> n;
    ll sum = 0;
    const int maxint = 1000000;
    for(auto x : progints) {
        if(x > maxint || x < 0 || x * x > n) {
            WA("integer not in range [0, sqrt(n)]");
        }
        sum += x * x;
    }
    if(sum != n) {
        WA("squares do not sum to n");
    }


    return 0;
}
