
#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

void update(vector<lli> & bit, int index, int value) {
    index += 1;
    while (index < bit.size()) {
        bit[index] += value;
        index += (index&-index);
    }
}

lli comp(vector<lli> & bit, int index) {
    index += 1;
    lli res = 0;
    while (index) {
        res += bit[index];
        index -= (index&-index);
    }
    return res;
}

int main() {
    int n, q;
    cin >> n;
    assert(n >= 1 && n <= 500000);
    vector<lli> vs(n+1);
    for (int i = 0; i < n; i++) {
        // Read in the value
        lli tmp;
        cin >> tmp;
        assert(tmp >= 1 && tmp <= 1000000000);

        // Convert to BIT in linear time
        vs[i + 1] += tmp;
        int ii = i+(i&-i);
        if (ii <= n)
            vs[ii] += vs[i];
    }

    cin >> q;
    assert(q >= 1 && q <= 100000);
    while (q--) {
        char type;
        int first;
        lli second;
        cin >> type >> first >> second;
        if (type == 'R') {
            assert(second <= n && second >= first && first >= 1);
            cout << comp(vs, (int)(second - 1)) - comp(vs, first - 2) << endl;
        } else {
            assert(first <= n && first >= 1);
            assert(second >= 1 && second <= 1000000000);
            update(vs, first-1, second);
        }
    }

    return 0;
}
