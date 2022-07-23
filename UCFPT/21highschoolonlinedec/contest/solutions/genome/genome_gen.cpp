// This solution used to generate data
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int oo = -1^1<<31;

ll mod = (ll)(7+1e9);

ll add(ll a, ll b){return a+b%mod;}
ll mult(ll a, ll b){return ((a%mod)*(b%mod))%mod;}

struct matrix {
    vector<vector<ll>> mat;
    matrix() {}
    matrix(const int& n, const int &m) : mat(n, vector<ll>(m)) {}
    vector<ll>& operator[](int row) { return mat[row]; }
    matrix operator*(matrix& t) {
        matrix r(t.rows(), cols());
        for(int i = 0 ; i < rows() ; i++)
            for(int j = 0 ; j < t.cols() ; j++)
                for(int k = 0 ; k < cols() ; k++)
                    r[i][j] = add(r[i][j], mult(mat[i][k], t[k][j]));
        return r;
    }
    int rows() const { return mat.size(); }
    int cols() const { return mat[0].size(); }
};

vector<vector<ll>> mult(vector<vector<ll>> mat1, vector<vector<ll>> mat2) {
    vector<vector<ll>> res((int) mat1.size(), vector<ll>((int) mat2[0].size()));
    for(int i = 0; i < (int) res.size(); ++i) {
        for(int j = 0; j < (int) res[i].size(); ++j) {
            for(int k = 0; k < (int) mat2.size(); ++k) {
                res[i][j] = add(res[i][j], mult(mat1[i][k], mat2[k][j]));
            }
        }
    }
    return res;
}

vector<vector<ll>> identity(int size) {
    vector<vector<ll>> mat(size, vector<ll>(size));
    for(int i = 0; i < size; ++i) {
        mat[i][i] = 1;
    }
    return mat;
}

vector<vector<ll>> expo(vector<vector<ll>> mat, ll e) {
    if (e == 0) return identity((int) mat.size());
    if (e == 1) return mat;
    vector<vector<ll>> ret = expo(mat, e / 2);
    ret = mult(ret, ret);
    if (e % 2 == 1) ret = mult(ret, mat);
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int NUM_TESTS;
    cin >> NUM_TESTS;
    int tnum = 1;
    while(NUM_TESTS--){
        cout << "Genome #" << tnum++ << ": ";
        string at, ct, tt, gt;
        cin >> at >> ct >> tt >> gt;
        string sstart;
        cin >> sstart;
        ll pow;
        cin >> pow;
        
        vector<vector<ll>> matt(4, vector<ll>(4, 0));
        
        matt[0][0] = count(at.begin(), at.end(), 'A');
        matt[0][1] = count(ct.begin(), ct.end(), 'A');
        matt[0][2] = count(tt.begin(), tt.end(), 'A');
        matt[0][3] = count(gt.begin(), gt.end(), 'A');

        matt[1][0] = count(at.begin(), at.end(), 'C');
        matt[1][1] = count(ct.begin(), ct.end(), 'C');
        matt[1][2] = count(tt.begin(), tt.end(), 'C');
        matt[1][3] = count(gt.begin(), gt.end(), 'C');

        matt[2][0] = count(at.begin(), at.end(), 'T');
        matt[2][1] = count(ct.begin(), ct.end(), 'T');
        matt[2][2] = count(tt.begin(), tt.end(), 'T');
        matt[2][3] = count(gt.begin(), gt.end(), 'T');

        matt[3][0] = count(at.begin(), at.end(), 'G');
        matt[3][1] = count(ct.begin(), ct.end(), 'G');
        matt[3][2] = count(tt.begin(), tt.end(), 'G');
        matt[3][3] = count(gt.begin(), gt.end(), 'G');

        vector<ll> vstart(4, 0);

        vstart[0] = count(sstart.begin(), sstart.end(), 'A');
        vstart[1] = count(sstart.begin(), sstart.end(), 'C');
        vstart[2] = count(sstart.begin(), sstart.end(), 'T');
        vstart[3] = count(sstart.begin(), sstart.end(), 'G');

        auto expod = expo(matt, pow);
        for(int i = 0; i < 4; i++){
            ll sum = 0;
            for(int j = 0; j < 4; j++){
                sum += expod[i][j] * vstart[j];
            }
            sum %= mod;
            cout << sum << " ";
        }
        cout << "\n";
    }
}