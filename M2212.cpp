#include <vector>
#include <bits/stdc++.h>
using namespace std;

void not_swap(int i, int j);
void shift(int i, int j, int k);
void answer(int N, std::vector<int> A);

// TODO: global variables can be declared here


void answer(int N, std::vector<int> A) {
	// TODO: implementation
  set<int> S;
  for(int i=0; i<N; i++) S.insert(A[i]);
  int nxt = 0;
  unordered_map<int, int> no;
  for(int x: S) {
    no[x] = nxt++;
  }
  for(int i=0; i<N; i++) A[i] = no[A[i]];
  queue<int> P;
  for(int i=0; i<N; i++) {
    if(A[i] != i) P.push(i);
  }
  bool in[N];
  for(int i=0; i<N; i++) {
    if(A[i] != i) in[i] = 1;
    else in[i] = 0;
  }
  while(P.size()) {
    int i = P.front();
    P.pop();
    in[i] = 0;
    if(A[i] == i) continue;
    int j = A[i];
    int k = A[j];
    if(i == j || j == k || i == k) continue;
    shift(i, j, k);
    int save = A[k];
    A[k] = A[j];
    A[j] = A[i];
    A[i] = save;
    if(A[i] != i && !in[i]) P.push(i);
    if(A[j] != j && !in[j]) P.push(j);
    if(A[k] != k && !in[k]) P.push(k);
  }
  queue<int> Q;
  for(int i=0; i<N; i++) {
    if(A[i] < i) {
      Q.push(i);
    }
  }
  while(Q.size() > 1) {
    int i = Q.front();
    Q.pop();
    int j = Q.front();
    Q.pop();
    int k = A[j];
    int l = A[i];
    shift(i, j, k);
    int save = A[k];
    A[k] = A[j];
    A[j] = A[i];
    A[i] = save;
    shift(j, l, i);
    save = A[i];
    A[i] = A[l];
    A[l] = A[j];
    A[j] = save;
  }
  for(int i=0; i<N; i++) {
    if(A[i] != i) {
      not_swap(i, A[i]);
      swap(A[i], A[A[i]]);
    }
  }
}
