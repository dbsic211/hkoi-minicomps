#include "bits/stdc++.h"
using namespace std;
const int MAXN = 2e5 + 10;
const int MOD = 1e9 + 7;
#define int long long
mt19937_64 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());
int rnd(int x, int y) {
  int u = uniform_int_distribution<int>(x, y)(rng); return u;
}

void solve(int tc) {
  int n;
  cin >> n;
  char a[3][n+1];
  for(int i=1; i<=2; i++) {
    for(int j=1; j<=n; j++) {
      cin >> a[i][j];
    }
  }
  int ea, eb, u;
  cin >> ea >> eb >> u;
  int dp[3][n+1];
  for(int i=0; i<3; i++) {
    for(int j=0; j<=n; j++) {
      dp[i][j] = 1e18;
    }
  }
  dp[2][1] = (a[1][1] == 'p' ? u : 0);
  dp[1][1] = (a[1][1] == 'x' ? 1e18 : u);
  for(int i=2; i<=n; i++) {
    for(int j=0; j<10; j++) {
      //dp[1][i]
      if(a[1][i] != 'x') {
        if(a[1][i-1] != 'x') {
          dp[1][i] = min(dp[1][i], dp[1][i-1] + eb + (a[2][i] == 'p' ? u : 0));
        }
        if(a[2][i-1] != 'x' && a[2][i] != 'x') {
          dp[1][i] = min(dp[1][i], dp[2][i-1] + ea + u);
        }
      }
      //dp[2][i]
      if(a[2][i] != 'x') {
        if(a[1][i-1] != 'x' && a[1][i] != 'x') {
          dp[2][i] = min(dp[2][i], dp[1][i-1] + eb);
        }
        if(a[2][i-1] != 'x') {
          dp[2][i] = min(dp[2][i], dp[2][i-1] + ea + (a[1][i] == 'p' ? u : 0));
        }
      }
    }
  }
  cout << (dp[2][n] == 1e18 ? -1 : dp[2][n]) << '\n';
  /*
  for(int i=1; i<=2; i++ ){
    for(int j=1; j<=n; j++) {
      cout << (dp[i][j] == 1e18 ? "INF" : to_string(dp[i][j])) << ' ';
    }
    cout << '\n';
  }
  */
}
int32_t main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1; //cin >> t;
  for(int i=1; i<=t; i++) solve(i);
} 
//祝大家 人品爆棚
