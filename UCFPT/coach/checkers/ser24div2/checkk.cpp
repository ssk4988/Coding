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

    int n, m, k; judgein >> n >> m >> k;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) judgein >> a[i];
    k--;
    ll x = a[k];
    vector<pair<char, ll>> ops(m);
    for(int i = 0; i < m; i++) {
        judgein >> ops[i].first >> ops[i].second;
    }
    int minops; judgeout >> minops;
    int prog_minops; progout >> prog_minops;
    if(progout.fail() || minops != prog_minops) WA("invalid number of operations");
    if(minops == -1) {
        string tmp;
        if(progout >> tmp) WA("extraneous output");
        return 0;
    }
    int read_ops = 0;
    for(int idx; progout >> idx; read_ops++) {
        if(idx < 1 || idx > m) {
            WA("invalid operation index");
        }
        idx--;
        auto [op, v] = ops[idx];
        if(op == '+') x += v;
        if(op == '-') x -= v;
        if(op == '*') x *= v;
        if(op == '/') x /= v;
        if(x < 0) WA("currency not allowed to become negative");
    }
    if(progout.fail() && !progout.eof()) {
        WA("invalid token");
    }
    if(read_ops != minops) {
        WA("number of operations printed is not the same as the minimum required");
    }
    bool duplicate = false;
    for(int i = 0; i < n; i++) {
        if(i == k) continue;
        if(a[i] == x) duplicate = true;
    }
    if(duplicate) WA("final currency is not unique");

    return 0;
}
