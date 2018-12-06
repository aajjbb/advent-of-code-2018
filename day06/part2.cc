#include <bits/stdc++.h>

using namespace std;

const int MAXN = 60;
const int MAX_MAP = 400;
const int MAX_DIST_SUM = 10000;


int X[MAXN];
int Y[MAXN];

int dst[MAX_MAP][MAX_MAP];
bool visited[MAX_MAP][MAX_MAP];

const int dx[4] = {0, 0, -1, +1};
const int dy[4] = {-1, +1, 0, 0};

bool inside(int arg_x, int arg_y) {
  return arg_x >= 0
    && arg_y >= 0
    && arg_x < MAX_MAP
    && arg_y < MAX_MAP;
}

void bfs(int init_x, int init_y) {
  queue<tuple<int, int> > q;
  q.push(make_tuple(init_x, init_y));

  visited[init_x][init_y] = true;

  while (!q.empty()) {
    int curr_x, curr_y;
    tie(curr_x, curr_y) = q.front();
    q.pop();

    for (int i = 0; i < 4; i++) {
      int next_x = curr_x + dx[i];
      int next_y = curr_y + dy[i];
      int curr_dist = abs(init_x - next_x) + abs(init_y - next_y);

      if (!inside(next_x, next_y)
          || visited[next_x][next_y]) {
        continue;
      }

      visited[next_x][next_y] = true;
      dst[next_x][next_y] += curr_dist;
      q.push(make_tuple(next_x, next_y));
    }
  }
}

int main() {
  int N = 1;

  memset(dst, 0, sizeof(dst));

  while (scanf("%d, %d", &Y[N], &X[N]) == 2) {
    memset(visited, false, sizeof(visited));
    bfs(X[N], Y[N]);
    N += 1;
  }

  int goal_area = 0;

  for (int i = 0; i < MAX_MAP; i++) {
    for (int j = 0; j < MAX_MAP; j++) {
      if (dst[i][j] < MAX_DIST_SUM) {
        goal_area += 1;
      }
    }
  }

  cout << goal_area << "\n";

  return 0;
}
