#include <bits/stdc++.h>
using namespace std;using l=long long;using v=vector<l>;using m=vector<v>;
#define s(v)(int)(v).size()
#define r(i,a,b)for(int i=a;i<(b);++i)
const l M=1e9+7;m operator*(m&a,m&b){m x(s(a),v(s(b[0])));r(i,0,s(x))r(j,0,s(x[i]))r(k,0,s(a[i]))x[i][j]=(a[i][k]*b[k][j]+x[i][j])%M;return x;}m operator^(m&b,l p){if(p==1)return b;m x=b^(p/2);x=x*x;if(p&1)x=x*b;return x;}int main(){int n,k; cin>>n>>k;string o; cin>>o;vector<m>t(2,m(1<<n,v(1<<n)));r(b,0,2)r(p,0,s(t[b]))r(z,0,s(t[b]))if(!__builtin_parity(z)){int w=z|(b<<n);int e=(~p)&w&(~(w>>1))&((1<<n)-1);int q=p|((~w)&(w>>1));if(!e)t[b][p][q]++;}m p(t[o[0]-'0']);r(i,1,s(o))p=p*t[o[i]-'0'];m x=p^k;cout<<x[0].back()<<"\n";}
