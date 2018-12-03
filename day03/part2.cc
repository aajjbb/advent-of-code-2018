#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5010;
const int CLAIM_COUNT = 1373;

int id[MAXN];
int BI[MAXN], BJ[MAXN];
int X[MAXN], Y[MAXN];
int canvas[MAXN][MAXN];


int main() {
  string line;
  int N = 0;

  set<int> non_overlaping_claims;

  for (int i = 1; i <= CLAIM_COUNT; i++) {
    non_overlaping_claims.insert(i);
  }

  while (getline(cin, line)) {
    sscanf(line.c_str(), "#%d @ %d,%d: %dx%d", &id[N], &BI[N], &BJ[N], &X[N], &Y[N]);

    for (int i = 0; i < X[N]; i++) {
      for (int j = 0; j < Y[N]; j++) {
        if (canvas[BI[N] + i][BJ[N] + j] > 0) {
          non_overlaping_claims.erase(canvas[BI[N] + i][BJ[N] + j]);
          non_overlaping_claims.erase(id[N]);
        }
        canvas[BI[N] + i][BJ[N] + j] = id[N];
      }
    }
    N += 1;
  }

  assert(non_overlaping_claims.size() == 1);

  cout << *non_overlaping_claims.begin() << endl;

  return 0;
}
