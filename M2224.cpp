//O(d^3)


//YEAH!!!!!!!!!!!!!!
#include "bits/stdc++.h"
using namespace std;
const int MAXN = 2e5 + 10;
const int MOD = 1e9 + 7;
#define int long long
mt19937_64 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());
int rnd(int x, int y) {
  int u = uniform_int_distribution<int>(x, y)(rng); return u;
}


char a[412][412];
int d, n;

int subproblem(int r1, int r2, int c1, int c2) {
  if(r1 > r2 || c1 > c2) return 0;
  int mir = 1e9, mar = 0;
  int mic = 1e9, mac = 0;
  for(int i=r1; i<=r2; i++) {
    for(int j=c1; j<=c2; j++) {
      if(a[i][j] == 'X') {
        mir = min(mir, i);
        mar = max(mar, i);
        mic = min(mic, j);
        mac = max(mac, j);
      }
    }
  }
  if(mar == 0) {
    return 0;
  }
  return (mar - mir + 1) * (mac - mic + 1);
}

int process() {
  int ans = 1e18;
  for(int i=1; i<d; i++) {
    ans = min(ans, subproblem(1, i, 1, d) + subproblem(i + 1, d, 1, d));
    ans = min(ans, subproblem(1, d, 1, i) + subproblem(1, d, i + 1, d));
  }
  // approach 1
  int mi[d + 1], ma[d + 1]; // for each column, min and max row id
  for(int i=1; i<=d; i++) mi[i] = 1e18, ma[i] = 0;
  for(int i=1; i<=d; i++) {
    for(int j=1; j<=d; j++ ){
      if(a[i][j] == 'X') {
        mi[j] = min(mi[j], i);
        ma[j] = max(ma[j], i);
      }
    }
  }
  int L = 1e18, R = 0; // L ≤ l ≤ r ≤ R, min and max columns with X
  for(int i=1; i<=d; i++) {
    for(int j=1; j<=d; j++) {
      if(a[i][j] == 'X') {
        L = min(L, j);
        R = max(R, j);
      }
    }
  }
  for(int l=L + 1; l < R; l++) {
    for(int r=l; r < R; r++) {
      // allow O(d) operations
      int mi1 = 1e18, ma1 = 0; // mi1, ma1: min and max row id for [L, R] except [l, r]
      for(int i=L; i<=R; i++) {
        if(!(l <= i && i <= r)) {
          mi1 = min(mi1, mi[i]);
          ma1 = max(ma1, ma[i]);
        }
      }
      int mi2 = 1e18, ma2 = 0;
      for(int i=l; i<=r; i++) {
        mi2 = min(mi2, mi[i]);
        ma2 = max(ma2, ma[i]);
      }
      if(ma1 == 0 || ma2 == 0) continue;
      ans = min(ans, (r-l + 1) * (ma2-mi2 + 1) + (R-L + 1) * (ma1-mi1 + 1));
    }
  }
  // approach 2a
  int U = 1e18, D = 0; // upmost and downmost rows with X
  for(int i=1; i<=d; i++) {
    for(int j=1; j<=d; j++) {
      if(a[i][j] == 'X') {
        U = min(U, i);
        D = max(D, i);
      }
    }
  }
  int mi3[d + 1], ma3[d + 1]; // dealing with rows: for row i, what is the min/max column that has X?
  for(int i=1; i<=d; i++) mi3[i] = 1e18, ma3[i] = 0;
  for(int i=1; i<=d; i++) {
    for(int j=1; j<=d; j++) {
      if(a[i][j] == 'X') {
        mi3[i] = min(mi3[i], j);
        ma3[i] = max(ma3[i], j);
      }
    }
  }
  for(int i=U; i<D; i++) {
    for(int j=L; j<R; j++) { // O(d^2)
      int mir = 1e18, mic = 1e18;
      for(int k=i+1; k<=D; k++) {
        mic = min(mic, mi3[k]);
        if(mi3[k] != 1e18) mir = min(mir, k);
      }
      for(int k=j+1; k<=R; k++) {
        mir = min(mir, mi[k]);
        if(mi[k] != 1e18) mic = min(mic, k);
      }
      ans = min(ans, (i-U + 1) * (j-L + 1) + (D-mir + 1) * (R-mic + 1));
    }
  }
  return ans;
}
void solve(int tc) {
  cin >> d >> n;
  for(int i=1; i<=d; i++) {
    for(int j=1; j<=d; j++) {
      cin >> a[i][j];
    }
  }
  if(n == 1) {
    int mir = 1e9, mar = 0;
    int mic = 1e9, mac = 0;
    for(int i=1; i<=d; i++) {
      for(int j=1; j<=d; j++) {
        if(a[i][j] == 'X') {
          mir = min(mir, i);
          mar = max(mar, i);
          mic = min(mic, j);
          mac = max(mac, j);
        }
      }
    }
    cout << (mar - mir + 1) * (mac - mic + 1) << '\n';
    return;
  }
  
  int global = process();
  for(int i=1; i<=d/2; i++) {
    for(int j=1; j<=d; j++) {
      swap(a[i][j], a[d+1-i][j]);
    }
  }
  global = min(global, process());
  cout << global << '\n';
}
int32_t main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1; //cin >> t;
  for(int i=1; i<=t; i++) solve(i);
} 
//祝大家 人品爆棚
/*

4 2
XXX.
X...
X.XX
..XX

..XX
X.XX
X...
XXX.

*/
