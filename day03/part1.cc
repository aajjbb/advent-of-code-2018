#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5010;

int id[MAXN];
int BI[MAXN], BJ[MAXN];
int X[MAXN], Y[MAXN];
int canvas[MAXN][MAXN];


int main() {
  string line;
  int N = 0;

  while (getline(cin, line)) {
    sscanf(line.c_str(), "#%d @ %d,%d: %dx%d", &id[N], &BI[N], &BJ[N], &X[N], &Y[N]);

    for (int i = 0; i < X[N]; i++) {
      for (int j = 0; j < Y[N]; j++) {
        canvas[BI[N] + i][BJ[N] + j] += 1;
      }
    }
    N += 1;
  }

  int cnt = 0;

  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      if (canvas[i][j] > 1) {
        cnt += 1;
      }
    }
  }

  cout << cnt << endl;

  return 0;
}
